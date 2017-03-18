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
// pane.hpp
//
//���������������������������������������������������������������������������

#ifndef __PANE_HPP
#define __PANE_HPP    1

//���������������������������������������������������������������������������
//
//                               Includes
//
//���������������������������������������������������������������������������

#include <vangogh.hpp>
#include <max.hpp>
#include <gutenbrg.hpp>
#include <chronos.hpp>

//���������������������������������������������������������������������������
//
//                                Defines
//
//���������������������������������������������������������������������������

#define IMAGE_SCROLL_LEFT    1
#define IMAGE_SCROLL_RIGHT   2
#define IMAGE_SCROLL_UP      3
#define IMAGE_SCROLL_DOWN    4

#define KEY_LEFT_ARROW      0x14B
#define KEY_RIGHT_ARROW     0x14D
#define KEY_BACKSPACE       0x008
#define KEY_ESCAPE          0x01B
#define KEY_ENTER           0x00D
#define KEY_DELETE          0x153
#define KEY_DOUBLEQUOTE     0x022
#define KEY_ASTERISK        0x02A
#define KEY_QUESTIONMARK    0x03F
#define KEY_FWDSLASH        0x02F
#define KEY_BACKSLASH       0x05C
#define KEY_PIPE            0x07C

//���������������������������������������������������������������������������
//
//                                Template
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// PaneDieT template
//
// A random roller class template
//���������������������������������������������������������������������������
template<int sides>
class PaneDieT
{

public:
    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    PaneDieT()
    {
        clock_t time = chronos_time_now();

        srand(time);
    }

    PaneDieT(int dummy) {}

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    int roll()
    {
        int random (rand());
        int res = random % sides;

        if (res < 0)
            res = abs(res);

        return res + 1;
    }

    operator int () { return roll(); }
};

//���������������������������������������������������������������������������
//
//                                Classes
//
//���������������������������������������������������������������������������

//���������������������������������������������������������������������������
// PaneImageScroll class
//
// A scrolling image viewer
//���������������������������������������������������������������������������
class PaneImageScroll
{
    //���������������������������������������������������������������������Ŀ
    // Data                                                                 �
    //�����������������������������������������������������������������������
    int         scroll_delta;      // scroll increment/decrement

    int         img_x;             // The x,y in the image to be drawn
    int         img_y;             // to the viewport

public:
    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    PaneImageScroll(VngoVport *gvp, VngoTexture *img,
                    int vp_x, int vp_y, int delta);
    ~PaneImageScroll() { }

    //���������������������������������������������������������������������Ŀ
    // Public Data                                                          �
    //�����������������������������������������������������������������������
    VngoVport   *gvport;
    VngoTexture *image;

    int         map_x;            // The last selected coords
    int         map_y;            // in map coords

    int         vp_anchor_x;
    int         vp_anchor_y;      // upper left of list box in screen coords

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������

    //��� Display
    void        render();
    void        scroll(int direction);
    void        scroll_up()     { scroll(IMAGE_SCROLL_UP);      }
    void        scroll_down()   { scroll(IMAGE_SCROLL_DOWN);    }
    void        scroll_left()   { scroll(IMAGE_SCROLL_LEFT);    }
    void        scroll_right()  { scroll(IMAGE_SCROLL_RIGHT);   }

    //��� General operations
    void        center_image(int x = -1, int y = -1);
    void        drag_image(int ax, int ay, int x, int y);
    int         get_scroll_x() { return img_x; }
    int         get_scroll_y() { return img_y; }
    void        reset_image() { img_x = img_y = 0; render(); }
    void        set_scroll_delta(int delta) { scroll_delta = delta; }
    void        set_image_pos(int newx,int newy) { img_x = -newx; img_y = -newy; }
    void        screen_to_image(short &x, short &y);
};

//���������������������������������������������������������������������������
// PaneInputText class
//
// An edit field control
//���������������������������������������������������������������������������
class PaneInputText
{
    //���������������������������������������������������������������������Ŀ
    // Data                                                                 �
    //�����������������������������������������������������������������������
    VngoVport           *gvport;
    MaxKbBuffer         *kbbuf;

    MaxKeyboard         *kbd;

    VngoRect            input_rect;

    char                *str;

    int                 str_len;
    int                 maxsize;
    int                 curs_pos;               // relative to string to str index
    int                 ibx;
    int                 iby;

    int                 mode;
    int                 cursor_type;

    dword               flags;

    dword               fg;                     // font colors
    dword               bg;

    char                font_type[GBERG_MAX_NAME];

    Chronometer         timer;

public:
    //���������������������������������������������������������������������Ŀ
    // Data                                                                 �
    //�����������������������������������������������������������������������
    enum
    {
        INPUT           =0,
        RENDER          =1,
        INACTIVE        =2,
    };

    enum
    {
        INPUT_DRAW_OUTLINE          = 0x1,
        INPUT_SPEC_CHARS            = 0x2,
        INPUT_CLEAR_VPORT           = 0x4,
    };

    enum
    {
        CURSOR_UNDERLINE       =0,
        CURSOR_VERTICAL        =1,
        CURSOR_BLOCK           =2,
    };

    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    PaneInputText(VngoVport *gvp, VngoRect *rct, char *fname);
    ~PaneInputText();

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    BOOL        init(int sz, char *def_str, MaxKeyboard *kbd);
    BOOL        process_events();
    void        set_colors(dword _f, dword _b) { fg=_f; bg=_b; }
    void        set_cursor(int c) { cursor_type = c; }
    void        set_mode(int m);

    //��� Display
    void        draw_cursor();
    void        draw_outline_box();
    void        render();
    void        clear_input();

    //��� Input String operations
    char        back_space();
    int         ins_char(char c);
    char        del_char();

    //��� Accessor functions
    char        *get_str(char *buff);
    void        put_str(char *new_str);
    int         query_mode() { return mode; }
    void        set_flags(dword _f) { flags = _f; }
    void        set_vport(VngoVport *vp) { gvport = vp; }
};

//���������������������������������������������������������������������������
// PaneListBox class
//
// A listbox control
//���������������������������������������������������������������������������
class PaneListBox
{
public:
    //���������������������������������������������������������������������Ŀ
    // Equates                                                              �
    //�����������������������������������������������������������������������
    enum direction_t
    {
        UP      =1,
        DOWN    =2,
    };

private:
    //���������������������������������������������������������������������Ŀ
    // Data                                                                 �
    //�����������������������������������������������������������������������
    char        *strings;
    ushort      font_width;

    ushort      row_height;

    VngoRect    vrc;

    ushort      max_string_len;
    ushort      max_string_entries;
    ushort      num_visible;
    ushort      first_visible;
    ushort      last_visible;
    ushort      cur_sel;

    ushort      spacing;          // number of spaces above and below each
                                  // character

    ushort      count;            // Number of strings in the list box

    ulong       screen_x;         // upper left of list box in screen coords
    ulong       screen_y;

    dword       fg;               // Foreground color for the list box
    dword       bg;               // Background color for the list box

    BOOL        hilite_cur_sel;

    ulong delete_data(ulong index);
    ulong insert_data(ulong index, void *extra);

public:
    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    PaneListBox(VngoVport *gvp, const char *f_type);
    ~PaneListBox();

    //���������������������������������������������������������������������Ŀ
    // Public Data                                                          �
    //�����������������������������������������������������������������������
    VngoVport   *gvport;

    void        *edata_ptr;
    ulong       sizeof_edata;

    char        font_type[GBERG_MAX_NAME];

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������

    //��� Initialize
    BOOL        init(short sx, short sy,
                     ushort maxlen, ushort maxentries,
                     ulong sedata=0, ushort _spc = 0);

    //��� Release data
    void        release();

    //��� Display
    void        render();
    void        scroll(direction_t);
    void        scroll_up() { scroll(UP); }
    void        scroll_down() { scroll(DOWN); }
    void        set_colors(dword _f, dword _b) { fg=_f; bg=_b; }

    //��� General operations
//    ulong       find_insertion_index(ulong ind);
    int         get_pick_index(int x, int y);
    void       *get_item_data(ulong index);
    void        get_selected_item(ulong index, char *dest);

    ushort      set_cur_sel(ulong index);
    ushort      set_font(const char *f_type);
    void        set_hilite(BOOL f) { hilite_cur_sel = f; }
    ulong       set_top_index(ulong index);

    //��� String operations
    ushort      add_string(const char *new_str, void *extra = 0);
//    ushort      add_string(ulong id, void *extra = 0);
    ushort      delete_string(ulong index);
    ushort      insert_string(ulong index, const char *ins_str, void *extra=0);
    void        reset_content();
    void        set_selected_item(ulong index, char *src);

    //���������������������������������������������������������������������Ŀ
    // Accessor functions                                                   �
    //�����������������������������������������������������������������������
    ushort      get_bottom_index()
    {
        if (count)
            return count-1;
        else
            return 0;
    }
    ushort      get_count() { return count; }
    ushort      get_cur_sel() { return cur_sel; }
    ushort      get_num_visible() { return num_visible; }
    ushort      get_top_index() { return first_visible; }
};

//���������������������������������������������������������������������������
// PaneDie
//
// A random roll class
//���������������������������������������������������������������������������
class PaneDie
{
    int sides;

public:
    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    PaneDie(int _sides=2):
        sides(_sides)
    {
        clock_t time = chronos_time_now();

        srand(time);
    }

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������
    int roll()
    {
        int random (rand());
        int res = random % sides;

        if (res < 0)
            res = abs(res);

        return res + 1;
    }

    int roll(int _sides)
    {
        int random (rand());
        int res = random % _sides;

        if (res < 0)
            res = abs(res);

        return res + 1;
    }

    operator int () { return roll(); }
};

//���������������������������������������������������������������������������
// PaneTextScroll class
//
// A text scrolling class
//���������������������������������������������������������������������������
class PaneTextScroll
{
public:
    //���������������������������������������������������������������������Ŀ
    // Equates                                                              �
    //�����������������������������������������������������������������������
    enum direction_t
    {
        UP      =1,
        DOWN    =2,
        PAGEUP  =3,
        PAGEDN  =4,
    };

private:
    //���������������������������������������������������������������������Ŀ
    // Data                                                                 �
    //�����������������������������������������������������������������������
    char        *text;
    ulong       font_height;
    ulong       font_width;
    VngoRect    vrc;

    ulong       string_len;
    ulong       max_chars_per_line;
    ulong       cur_line;
    ulong       num_lines;
    ulong       visible_lines;

    dword       fg;               // Foreground color for the list box
    dword       bg;               // Background color for the list box

    ulong       count_lines(char *sp);
    BOOL        parse_string(char *sp);

public:
    //���������������������������������������������������������������������Ŀ
    // Constructor/Destructors                                              �
    //�����������������������������������������������������������������������
    PaneTextScroll(VngoVport *gvp, const char *f_type);
    ~PaneTextScroll();

    //���������������������������������������������������������������������Ŀ
    // Public Data                                                          �
    //�����������������������������������������������������������������������
    VngoVport   *gvport;
    char        font_type[GBERG_MAX_NAME];

    //���������������������������������������������������������������������Ŀ
    // Operations                                                           �
    //�����������������������������������������������������������������������

    //��� Initialize (1 on success, 0 otherwise)
    BOOL        init(char *txt);

    //��� Release data
    void        release();

    //��� Display
    void        render();
    void        set_colors(dword _f, dword _b) { fg=_f; bg=_b; }

    //��� General operations
    void        scroll(direction_t);
    void        scroll_up() { scroll(UP); }
    void        scroll_down() { scroll(DOWN); }
    void        page_up() { scroll(PAGEUP); }
    void        page_down() { scroll(PAGEDN); }

    //���������������������������������������������������������������������Ŀ
    // Accessor functions                                                   �
    //�����������������������������������������������������������������������
};

#endif

//��� end of header - pane.hpp ���
