;様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
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
;陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
;
; THE AUTHORS MAKE NO WARRANTIES, EXPRESS OR IMPLIED, AS TO THE CORRECTNESS
; OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE IT.  THE AUTHORS
; PROVIDE THE CODE ON AN "AS-IS" BASIS AND EXPLICITLY DISCLAIMS ANY
; LIABILITY, INCLUDING CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
; OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
;
;陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
;
;                        http://www.mythos-engine.org/
;
;陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
;
; Created by Tim Little
;
; vngdefs.inc
;
;様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

ifndef __VNGDEFS_INC
__VNGDEFS_INC EQU 1

;旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
;
;                                Equates
;
;旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

VNGO_PERSP_PRECISION    EQU     128

VNGO_PHYSICAL_DEV       EQU     01h
VNGO_PAL_MAPPED_DEV     EQU     02h
VNGO_ZBUFFER_DEV        EQU     04h
VNGO_ZBUFFER_ACTIVE     EQU     08h
VNGO_INIT_NO_RESET      EQU     010h
VNGO_NOCLEAR_VBUFFER    EQU     020h
VNGO_BACKBUFFER         EQU     040h


VNGO_MAX_FACE_PTCT      EQU     4
VNGO_MAX_POLYG_PTCT     EQU     VNGO_MAX_FACE_PTCT * 2 +1

;; Image transfer flags.
VNGO_TRANSPARENT        EQU     0ff000000h
VNGO_TRANSPARENT_COLOR  EQU     0ffh

; VngoTexture flags.
VNGO_TEXTURE_MONO       EQU     01h
VNGO_TEXTURE_1BIT       EQU     01h
VNGO_TEXTURE_2BIT       EQU     02h
VNGO_TEXTURE_4BIT       EQU     04h
VNGO_TEXTURE_8BIT       EQU     08h
VNGO_TEXTURE_15BIT      EQU     010h
VNGO_TEXTURE_16BIT      EQU     020h
VNGO_TEXTURE_24BIT      EQU     040h
VNGO_TEXTURE_32BIT      EQU     080h
; Just in case....:)
VNGO_TEXTURE_SHADOWS    EQU     0100h
VNGO_TEXTURE_ALPHA      EQU     0200h
VNGO_TEXTURE_ZMAP       EQU     0400h
VNGO_TEXTURE_SHADE      EQU 0800h

;旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
;
;                                Macros
;
;旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

endif          ; __VNGDEFS_INC

;葦� End of module - vngdefs.inc 憶�
