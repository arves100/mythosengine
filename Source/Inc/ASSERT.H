//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�
//
//                                Assert Header
//
//              Copyright (c) 1994-1998 by Charybdis Enterprises, Inc.
//                            All Rights Reserved.
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
// Windows assert replacement.
//
//様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�


#ifndef __CHARYBDIS_ASSERT
#define __CHARYBDIS_ASSERT 1

//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�
//
//                                Equates
//
//旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭�

#undef	assert
#undef	assertMyth

#ifdef NDEBUG
#define assert(exp)	((void)0)
#define assertMyth(msg,exp)	((void)0)
#else

#ifdef __cplusplus
extern "C"
#endif
void _charybdis_assert(char *txt, char *exp, char *f, unsigned ln);

#define assert(exp) (void)( (exp) || (_charybdis_assert(0, #exp, __FILE__, __LINE__), 0)  )
#define assertMyth(msg,exp) (void)( (exp) || (_charybdis_assert(msg, #exp, __FILE__, __LINE__), 0)  )

#endif

#endif

//葦� End of header - assert.h 憶�
