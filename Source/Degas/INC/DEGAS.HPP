//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//                                         . .
//                                       , h $ F
//                                       ?,$,$,F
//                                       `$$$$$P  ,
//                                        ?$$$$L,c'
//                                         $$$$$"'
//                                        c$$P"                              
//;;,                                  .z$$$F                                
//!'',ccc                            ,c$$$P"                                 
// ,$$$$$".                        zJ$$$$"                        .z..       
//> $".,,c,.                     c$$$$$P'                        ,$$$$$c,.   
// z$$,.,$$$F                   $$$$$$P                          J$$$$PP$$$hc
//z$$$$$$$$$=                  "??$$$"                           <$$$$$ $$P".
//$$$$$$$$$,ccc             zJ$$$$$P'                            `?$$$$c " ??
//$$$$$$$$$$??"         .zJ$$$$$P"                        .,;;;!!; <$$$$.  =$
//`$$$$$$$P"     ,ccd$$$$$$$$$"'                         <!!!!!'!! `"?$$h <c$
// $$$$$$$F  .zc???$??""'..`"         zcccc,,,.,..,..   `!!!!'  ' ;!; "$$.`$$
//J$$$$$$$L $P" ,;;,;;!!!''          <$$$$$$$$$$$$P",;,-``!(.-' .<!!!! `$L  "
//$$$$$$$$$ ? ;!!!!!!'``,;;;;;;,      $$$$$"""???" <!'  ' !' ;!!!!!!!!> $$h. 
//$$$$$$$$'  <!!!'  ,;<!!!!!!!!!!>    ?$$$$$c     `!! ,;;!!;<`<!!!!!'`. $$$$.
//$$$$$$$$ ;!!!!'!!!!!!!!!!!!!!!       $$$$$$c     !! !!!!!' ;'`!'' ,$F."???$
//$$$$$$$' `(!!> !!!!!! ..`!!!' ,$     ?$$$$$$.      ;!!!' ;! ., z$$F zJh=y,?
//$$$$$P  ;!!!!> !!!!' <F" `' ,J$$      $$$$$$h     c, `..<'' `,J$$P  " $r`F`
//$$$P" <; ``!!! !!!' .`?chcc$$$L       `$$$$$$c    $$$c,.,ccc$$$$F cc  ".,c$
//.",;<!!!!>; ;! `' z$$L ",$$$$$$c       $$$$$$$c, J$$$$$$??????" z$$$$ ! ?$$
//!!!!!!!!!!! `' c$$$$$$cd$$$$$$$""      $$$$$$$$h $$$$$$$c,.,,zc$$$$$$.`! $$
//!!!!!!!!!!!!!`<$$$$$$$$$$$$$$??        ?$$$$$$$',$$$$$$$$$$$$$$$$$$$$F !><$
//!!!!!!!!!!!!! J$$$$$$$"$$$$$$F         `??$???',$$$$$$$$$$$$$$$$$$$$$ <!> "
//!!!!!!!!!!!' z$$$$$$$$ """??",$$F ,c$,c c  .- ,$$$$$$$$$$$$$$$$$$$$$" !!>  
//!!!!!!!!!',c$$$$$$$$$",$$$$cd$P  J$$$$$$$c=". $$$$$$$$$$$$$$$$$$$$$" !!!>';
//!!!!!!'`,c$$$$$$$$$$$ $$$$$$$F J $$$$$$$"  "F<$$$$$$$$$$$$$$$$$$$$" <!!! <!
//!!!'.,c$$$$$$$$$$$$$$$$$$$$$P J z$$$$P".z$$cc,,.""?$$$$$$$$$$$$$$P >'!!  ``
//! ,J$$$$"".,... "$$$$$$$$$$P / z$$$$P c$$$$$$$$$$$c,."???$$$$$$$" <'`!!! !;
//! ?$$$F ;!!!!!!!  `"??$$$$F `,J$$$$$   `"?$$$$$$$$$$$$hcc ?$$$$" !! `!!! !!
//! <$$" <!!!!!!'.zc,`'-.,..- z$$$$$$'        ""???$$$$$$$$F`??" ;!!! <!!! !!
//!> $" !!!',,,zc$$$$$cc,_' ,J$$$$$$F        <!>;;;;,  $$$$$  ;!!!!!! !!!';!!
//!! ' !!! J$$$$$$$$$$$$$$$$$$$$$$$".         !!!!!!!!;`$$$$h `!!!!!  <!! <!!
//`' .<!! .""???$$$$$$$$$$$$$$$$$$F !          `!!!!!!!;`$$$$$ <!!!! ;,.,;!!!
//Mx`<!'! !!!;;;,."""?$$$$$$$$$$P";!!           <!!!!!!!; $$$$c`!!! , `````.,
//MMn ',`!!!!!!!!!!!>;,,,."""??" <!!             !!!!!!!!; ?$$$.`!>4MMMMMM MM
//MMMb.`,`!!!!!!!!!!!!!!!!!!! ;!!!!              `!!!!!!!!; ?$$$ ' ,_""4MMMMM
//MMMMMx`,`!!!!!!!!!!!!!!!!!' !!!                 !!!!!!!!!> ?$$F MMMMM,  ..`
//
//                                D E G A S
//                       2D/3D Graphics Device Manager
//
//                      Microsoft Windows 95/NT Version
//
//               Copyright (c) 1998 by Charybdis Enterprises, Inc.
//                           All Rights Reserved.
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
//           *** Charybdis Enterprises, Inc. Company Confidential ***
//
//  This file and all associated files are the company proprietary property
//        of Charybdis Enterprises, Inc.  Unauthorized use prohibited.
//
// CHARYBDIS ENTERPRISES, INC. MAKES NO WARRANTIES, EXPRESS OR IMPLIED, AS
// TO THE CORRECTNESS OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE
// IT.  CHARYBDIS ENTERPRISES, INC. PROVIDES THE CODE ON AN "AS-IS" BASIS
// AND EXPLICITLY DISCLAIMS ANY LIABILITY, INCLUDING CONSEQUENTIAL AND
// INCIDENTAL DAMAGES FOR ERRORS, OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
//
// Created by Chuck Walbourn
//
// degas.hpp
//
// Primary include header for the Degas graphics device manager.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�

#ifndef __DEGAS_HPP
#define __DEGAS_HPP 1

#ifdef __WATCOMC__
#pragma pack(1);
#endif

#ifdef _MSC_VER
#pragma pack(push,1)
#endif

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//             
//                                Includes
//                                
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#include <windows.h>

//陳� Charybdis global headers
#include <assert.h>
#include <debug.h>
#include <portable.h>

#include <xfile.hpp>

//陳� Degas headers 
#include "dgdefs.h"
#include "dgbase.hpp"

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Classes
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#ifdef __WATCOMC__
#pragma pack();
#endif

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif

//葦� End of header - degas.hpp 憶�

