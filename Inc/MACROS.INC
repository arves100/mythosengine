;様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
;
;                                Macros
;
;   Copyright (c) 1994-1999 by Dan Higdon, Tim Little, and Chuck Walbourn
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
; Standard Macro File
;
;      Contains standard macros used by Charybdis software.
;
;       START_PROC procedure_name
;       END_PROC procedure_name
;       -- Ensure compatibility with various 'C' style symbols for
;          various compilers.
;
;様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

;旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
;
;                                Macros
;
;旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

;陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
; Macros for compatibility with various 'C'-style symbols used by various  �
; compilers, including: Borland, Microsoft, Watcom, Metaware, and Zortech. �
;陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�

START_PROC      MACRO proc_name, proc_args:VARARG
        ALIGN 4
        public _&proc_name&
_&proc_name&:
        public &proc_name&_
&proc_name&_:
        public proc_name
proc_name:

dmy_&proc_name& proc    proc_args
endm


END_PROC        MACRO proc_name, proc_args:VARARG
dmy_&proc_name& endp    proc_args
endm



;陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
; ABS - makes the value in val, positive if it is negative and leaves it   �
; unchanged if it is already positive.  The results are left in val.       �
;陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
ABS     MACRO   val
        cmp     val,0          ; using cmp with 0 allows val to be a
                               ; non register.
        jge     @f
        neg     val
@@:
        ENDM



;葦� End of header - macros.inc 憶�

