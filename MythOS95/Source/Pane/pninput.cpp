//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//����������������� Microsoft Windows 95/98/NT Version ����������������������
//���������������������������������������������������������������������������
//���Copyright (c) 1996-1999 by Dan Higdon, Tim Little, and Chuck Walbourn���
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//���������������������������������������������������������������������������
//
// THE AUTHORS MAKE NO WARRANTIES, EXPRESS OR IMPLIED, AS TO THE CORRECTNESS
// OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE IT.  THE AUTHORS
// PROVIDE THE CODE ON AN "AS-IS" BASIS AND EXPLICITLY DISCLAIMS ANY
// LIABILITY, INCLUDING CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
// OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//���������������������������������������������������������������������������
//
//                        http://www.mythos-engine.org/
//
//���������������������������������������������������������������������������
//
// Created by Sean Gallagher
//
// pninput.cpp
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//
//                                Includes
//
//���������������������������������������������������������������������������

#define WIN32_LEAN_AND_MEAN
#include <stdlib.h>
#include <assert.h>

#include <pane.hpp>

//���������������������������������������������������������������������������
//
//                                 Code
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
//�����������������������  Constructors/Destructors  ������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// PaneInputText - Constructor
//���������������������������������������������������������������������������
PaneInputText::PaneInputText(VngoVport *gvp, VngoRect *rct, char *fname):
    gvport(gvp),
    kbbuf(0),
    kbd(0),
    str(0)
{
    assertMyth("PaneInputText requires a valid VngoVport",gvp);
    assertMyth("PaneInputText requires a valid VngoRect",rct);

    memcpy(&input_rect, rct, sizeof(VngoRect));

    strncpy(font_type, fname, GBERG_MAX_NAME-1);
}

//���������������������������������������������������������������������������
// PaneInputText - Destructor
//���������������������������������������������������������������������������
PaneInputText::~PaneInputText()
{
    if (kbbuf)
    {
        delete kbbuf;
        kbbuf = 0;
    }
    if (str)
    {
        delete [] str;
        str = 0;
    }
}


//���������������������������������������������������������������������������
//�����������������������������  Operations  ��������������������������������
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// PaneInputText - init
//���������������������������������������������������������������������������
BOOL PaneInputText::init(int sz, char *def_str, MaxKeyboard *kbd)
{
    kbbuf = new MaxKbBuffer(kbd);
    if (!kbbuf)
        return FALSE;

    flags = 0;

    ibx = iby = 1;

    str_len = 0;
    maxsize = sz;

    mode = RENDER;

    str = new char [maxsize+1];
    if (!str)
    {
        delete kbbuf;
        kbbuf = 0;
        return FALSE;
    }

    memset(str, 0, sizeof(char)*(maxsize+1));
    curs_pos = 0;

    strncpy(str, def_str, sz);
    str_len = curs_pos = strlen(str);

    // the timer is uses to blink the cursor
    timer.clear();

    return TRUE;
}


//���������������������������������������������������������������������������
// PaneInputText - process_events
//���������������������������������������������������������������������������
BOOL PaneInputText::process_events()
{
    if (kbbuf->kbhit())
    {
        int ch = kbbuf->getch();
        if ( (curs_pos < maxsize - 1)
             && ( ((ch < 127) && (ch > 31))
                  || (ch == 129)
                  || (ch == 132)
                  || (ch == 142)
                  || (ch == 148)
                  || (ch == 153)
                  || (ch == 154)
                  || (ch == 225) ) )
         {
            // don't allow wierd chars unless explicitly told...
            if ((flags & INPUT_SPEC_CHARS) ||
                 (ch != KEY_DOUBLEQUOTE &&
                  ch != KEY_ASTERISK &&
                  ch != KEY_QUESTIONMARK &&
                  ch != KEY_FWDSLASH &&
                  ch != KEY_BACKSLASH &&
                  ch != KEY_PIPE))
                ins_char(ch);

            return TRUE;
        }
        else
        {
            switch (ch)
            {
                case KEY_LEFT_ARROW:                    // left arrow
                    if (curs_pos != 0)
                        curs_pos--;
                    return TRUE;
                case KEY_RIGHT_ARROW:                   // right arrow
                    if (curs_pos != str_len)
                        curs_pos++;
                    return TRUE;
                case KEY_BACKSPACE:                         // backspace
                    if (curs_pos != 0)
                        back_space();
                    return TRUE;

                case KEY_ESCAPE:                            // escape
                    kbbuf->clear();
                    put_str("");
                    return TRUE;

                case KEY_DELETE:                            // delete key
                    if ((curs_pos < maxsize - 1) && (str_len != 0) &&
                        curs_pos < str_len)
                            del_char();
                    return TRUE;
            }
        }
    }

    return FALSE;
}


//���������������������������������������������������������������������������
// PaneInputText - clear_input
//���������������������������������������������������������������������������
void PaneInputText::clear_input()
{
    int was_locked = gvport->lock();

    if (was_locked != -1)
    {
        gvport->reset(bg);
        if (!was_locked)
            gvport->unlock();
    }

    put_str("");
}


//���������������������������������������������������������������������������
// PaneInputText - render
//���������������������������������������������������������������������������
void PaneInputText::render()
{
//    assertMyth ("InputBox::render needs Screen instance", Screen != 0);

    if (mode == INACTIVE)
        return;

    int was_locked = gvport->lock();

    if (was_locked != -1)
    {
        if (flags & INPUT_CLEAR_VPORT)
            gvport->reset(bg);

        GBergText gt (gvport);

        gberg_select_font (font_type);
        gberg_color(fg, bg);

        gt.out (ibx, iby, str);

        if (mode == INPUT)
        {
            if (flags & INPUT_DRAW_OUTLINE)
                draw_outline_box();

            // make the cursor flash!
            if (timer.check() > 750)
            {
                draw_cursor();

                if (timer.check() > 1500)
                    timer.clear();
            }
        }

        if (!was_locked)
            gvport->unlock();

//        Screen->invalidate(input_rect);
    }
}


//���������������������������������������������������������������������������
// PaneInputText - draw_outline_box
//���������������������������������������������������������������������������
void PaneInputText::draw_outline_box()
{
    VngoPoint p1, p2, p3, p4;

    p1.x = 0;
    p1.y = 0;
    p2.x = gvport->vbuff.width - 1;
    p2.y = 0;
    p3.x = gvport->vbuff.width - 1;
    p3.y = gvport->vbuff.height - 1;
    p4.x = 0;
    p4.y = gvport->vbuff.height - 1;

    VngoColor24bit clr(fg);

    gvport->clip_line(&p1, &p2, &clr);
    gvport->clip_line(&p2, &p3, &clr);
    gvport->clip_line(&p3, &p4, &clr);
    gvport->clip_line(&p4, &p1, &clr);
}


//���������������������������������������������������������������������������
// PaneInputText - draw_cursor
//���������������������������������������������������������������������������
void PaneInputText::draw_cursor()
{

//--- Get the font height and width
    GBergFontInfo fi;
    gberg_info_font(font_type, &fi);

    int fhgt = fi.height;
    int fwdt = fi.width;

    int cur_x = ibx + curs_pos*fwdt;
    int cur_y = iby + fhgt - 4;

    VngoPoint p1, p2, p3, p4;


    switch (cursor_type)
    {
        case CURSOR_UNDERLINE:
            {
                p1.x = cur_x;
                p1.y = cur_y;

                p2.x = cur_x + fwdt - 1;
                p2.y = cur_y;

                p3.x = p2.x;
                p3.y = p2.y + 1;

                p4.x = cur_x;
                p4.y = p3.y;

                VngoColor24bit clr(fg);

                if (p2.x <= gvport->vbuff.width)
                {
                    //--- Draw the cursor
                    gvport->clip_line(&p1, &p2, &clr);
                    gvport->clip_line(&p2, &p3, &clr);
                    gvport->clip_line(&p3, &p4, &clr);
                    gvport->clip_line(&p4, &p1, &clr);
                }
            }
            break;

        case CURSOR_VERTICAL:
            {
                cur_y = iby;

                p1.x = cur_x;
                p1.y = cur_y;

                p2.x = p1.x + 1;
                p2.y = cur_y;

                p3.x = p2.x;
                p3.y = p2.y + fhgt - 3;

                p4.x = p3.x - 1;
                p4.y = p3.y;

                VngoColor24bit clr(fg);

                if (p2.x <= gvport->vbuff.width)
                {
                    //--- Draw the cursor
                    gvport->clip_line(&p1, &p2, &clr);
                    gvport->clip_line(&p2, &p3, &clr);
                    gvport->clip_line(&p3, &p4, &clr);
                    gvport->clip_line(&p4, &p1, &clr);
                }
            }
            break;

        case CURSOR_BLOCK:
            {
                VngoRect rc;

                cur_y = iby + 1;

                rc.x = cur_x;
                rc.y = cur_y;

                rc.dx = fwdt - 1;
                rc.dy = fhgt - 3;

                VngoColor24bit clr(fg);

                if (rc.x + rc.dx <= gvport->vbuff.width)
                    gvport->frect(&rc, &clr);
            }
            break;
    }
}


//���������������������������������������������������������������������������
// PaneInputText - ins_char
//���������������������������������������������������������������������������
int PaneInputText::ins_char(char c)
{
    if (str_len < maxsize - 1)
    {
        memmove(str + curs_pos + 1, str + curs_pos, str_len - curs_pos);
        str[curs_pos] = c;
        str_len++;
        curs_pos++;

        return 0;                       // no overflow
    }
    else
    {
        memmove(str + curs_pos + 1, str + curs_pos, maxsize - curs_pos - 2);
        str[curs_pos] = c;
        str_len++;
        curs_pos++;

        return 1;                       // overflow
    }
}


//���������������������������������������������������������������������������
// PaneInputText - back_space
//���������������������������������������������������������������������������
char PaneInputText::back_space()
{
    char c = str[curs_pos - 1];

    if (maxsize == curs_pos)
    {
        str[curs_pos-1] = 0;
    }
    else
    {
        memmove(str + curs_pos - 1, str + curs_pos, maxsize - curs_pos);
    }
    curs_pos--;
    str_len--;

    return c;
}


//���������������������������������������������������������������������������
// PaneInputText - del_char
//���������������������������������������������������������������������������
char PaneInputText::del_char()
{
    char c = str[curs_pos];

    memmove(str + curs_pos, str + curs_pos + 1, maxsize - curs_pos - 1);
    str_len--;

    return c;
}


//���������������������������������������������������������������������������
// PaneInputText - get_str
//���������������������������������������������������������������������������
char *PaneInputText::get_str(char *buff)
{
    strncpy(buff, str, maxsize);

    return buff;
}


//���������������������������������������������������������������������������
// PaneInputText - put_str
//���������������������������������������������������������������������������
void PaneInputText::put_str(char *buff)
{
    strncpy(str, buff, maxsize);
    str_len = curs_pos = strlen(str);
}


//���������������������������������������������������������������������������
// PaneInputText - set_mode
//���������������������������������������������������������������������������
void PaneInputText::set_mode(int m)
{
    mode = m;
    kbbuf->clear();
}

//��� eof - pninput.cpp ���
