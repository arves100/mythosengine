;���������������������������������������������������������������������������
;
;                                                           %__________%
;                                                          %/ . .  .   \%
;           Van Gogh 2D-Display Library                     |  . .  o. |
;                                                           |. _  .   .|
;        Microsoft Windows 95/98/NT Version                 | / \   .  |
;                                                           |_|_|_._._.|
;                                                           |.-.-.-.-..|
;                                                          %\__________/%
;                                                           %          %
;
;  Copyright (c) 1994-1999 by Dan Higdon, Tim Little, and Chuck Walbourn
;
;���������������������������������������������������������������������������
;
; THE AUTHORS MAKE NO WARRANTIES, EXPRESS OR IMPLIED, AS TO THE CORRECTNESS
; OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE IT.  THE AUTHORS
; PROVIDE THE CODE ON AN "AS-IS" BASIS AND EXPLICITLY DISCLAIMS ANY
; LIABILITY, INCLUDING CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
; OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
;
;���������������������������������������������������������������������������
;
;                        http://www.mythos-engine.org/
;
;���������������������������������������������������������������������������
;
; Created by Tim Little
;
; vngRECT8.ASM 
;
;      This module draws filled rectangles in all of their permutations.
;
;���������������������������������������������������������������������������


.486p

        OPTION SCOPED                   ; Enable local labels.


;���������������������������������������������������������������������������
;
;                                Includes
;                                
;���������������������������������������������������������������������������

include macros.inc
include vngdefs.inc
include vngstrct.inc

;���������������������������������������������������������������������������
;
;                                Equates
;
;���������������������������������������������������������������������������


;���������������������������������������������������������������������������
;
;                               Structures
;
;���������������������������������������������������������������������������


;���������������������������������������������������������������������������
;
;                                 Data
;
;���������������������������������������������������������������������������
        ASSUME  ds:_DATA
_DATA   SEGMENT PARA PUBLIC USE32 'DATA'
_DATA   ENDS

;���������������������������������������������������������������������������
;
;                                 Code
;
;���������������������������������������������������������������������������

_TEXT  SEGMENT PARA PUBLIC USE32 'CODE'

;��������������������������������������������������������������������������
;  vngo_rect8 (rectangle *,dword color);                                   
;      Expects color to be an 8bit color to fill the screen with.                                            
;��������������������������������������������������������������������������
START_PROC     vngo_rect8, C CurScreen:DWORD, rectptr:DWORD, color:DWORD
        LOCAL   LX1             ; Top left x of the rect to fill.
        LOCAL   LDX             ; width of the rect to fill.
        LOCAL   LY1             ; Top left y of the rect to fill.
        LOCAL   LDY             ; height of the rect to fill.

        push    edi
        push    esi
        push    ebx

        mov     esi,CurScreen

        mov     edi,(VNGO_VBUFFER PTR [esi]).vb_scrn_ptr
        mov     ebx,(VNGO_VBUFFER PTR [esi]).vb_pitch
        mov     ecx,rectptr
        mov     eax,(VNGO_RECT PTR [ecx]).rect_x
        mov     LX1,eax
        mov     eax,(VNGO_RECT PTR [ecx]).rect_dx
        mov     LDX,eax
        mov     eax,(VNGO_RECT PTR [ecx]).rect_dy
        mov     LDY,eax
        mov     eax,(VNGO_RECT PTR [ecx]).rect_y
        mov     LY1,eax
        mov     ecx,(VNGO_VBUFFER PTR [esi]).vb_ytable
        lea     eax,[ecx+eax*4]
        mov     eax,[eax]
        add     eax,LX1
        add     edi,eax

        mov     eax,color
        mov     ah,al
        mov     edx,eax
        shl     eax,16
        and     edx,0ffffh
        or      eax,edx
        mov     edx,LDY
        mov     esi,LDX
        sub     ebx,esi

y_loop:
        mov     ecx,esi
        shr     ecx,2
    rep stosd
        mov     ecx,esi
        and     ecx,03h
    rep stosb
        add     edi,ebx         ; go to the next scan line.
        dec     edx
        jg      y_loop

        pop     ebx
        pop     esi
        pop     edi
        ret
END_PROC       vngo_rect8     


_text   ends
        end
;��� End of module - vngRECT8.asm ���
