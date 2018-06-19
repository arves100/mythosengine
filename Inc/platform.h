//ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ
//
//  .-._                          .-._          ,--.--------.   ,--.-,,-,--,     _,.---._      .-._         
// /==/ \  .-._   ,--.-.  .-,--. /==/ \  .-._  /==/,  -   , -\ /==/  /|=|  |   ,-.' , -  `.   /==/ \  .-._  
// |==|, \/ /, / /==/- / /=/_ /  |==|, \/ /, / \==\.-.  - ,-./ |==|_ ||=|, |  /==/_,  ,  - \  |==|, \/ /, / 
// |==|-  \|  |  \==\, \/=/. /   |==|-  \|  |   `--`\==\- \    |==| ,|/=| _| |==|   .=.     | |==|-  \|  |  
// |==| ,  | -|   \==\  \/ -/    |==| ,  | -|        \==\_ \   |==|- `-' _ | |==|_ : ;=:  - | |==| ,  | -|  
// |==| -   _ |    |==|  ,_/     |==| -   _ |        |==|- |   |==|  _     | |==| , '='     | |==| -   _ |  
// |==|  /\ , |    \==\-, /      |==|  /\ , |        |==|, |   |==|   .-. ,\  \==\ -    ,_ /  |==|  /\ , |  
// /==/, | |- |    /==/._/       /==/, | |- |        /==/ -/   /==/, //=/  |   '.='. -   .'   /==/, | |- |  
// `--`./  `--`    `--`-`        `--`./  `--`        `--`--`   `--`-' `-`--`     `--`--''     `--`./  `--`  
//
//
//							Nynthon Game Engine
//							Copyright (C) 2018 Arves100.
//
//ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
//
// Created by Arves100
//
// platform.h
//
// This file contains information about the specific platform switch used to configurate Nynthon build
// environment
//
//ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ
#ifndef _NY_PLATFORM_H_
#define _NY_PLATFORM_H_

#ifdef NYNTHON_VERSION
#undef NYNTHON_VERSION
#endif

#define NYNTHON_VERSION "0.1 Development"

#if defined(_WINDOWS) || defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(WINDOWS)

#if defined(WIN64) || defined(_WIN64)
#error "Nynthon does not support 64-bit builds"
#endif /* !WIN64 */
#if defined(WIN16) || defined(_WIN16)
#error "Nynthon does not support 16-bit builds"
#endif /* !WIn16 */

// Windows Target Version
#ifndef _WIN32_WINNT
//Target: Windows Vista
#define _WIN32_WINNT 0x600
#else
#if _WIN32_WINNT < 0x0500
#error "Nynthon is supported only on Windows 2000 and greater platforms"
#endif /* _WIN32_WINNT < */
#if _WIN32_WINNT > 0x601
#error "Nynthon is not supported on Windows 8 or greater platforms"
#endif /* _WIN32_WINNT > */
#endif /* !_WIN32_WINNT */

#ifndef _WIN32_IE
//Target: Internet Explorer 7 (Windows Vista)
#define _WIN32_IE 0x700
#else
#if _WIN32_IE < 0x501
#error "Nynthon is supported only on Windows 2000 and greater platforms"
#endif /* _WIN32_IE < */
#if _WIN32_IE > 0x800
#error "Nynthon is not supported on Windows 8 or greater platforms"
#endif
#endif /* !_WIN32_IE */

#ifndef DIRECTX_TARGET_VERSION
#define DIRECTX_TARGET_VERSION 6
#endif /* !DIRECTX_TARGET_VERSION */

#if DIRECTX_TARGET_VERSION < 6
#error "Nynthon is not supported on DirectX 5 or lesser"
#endif /* DIRECTX_TARGET_VERSION < */

// TODO: DirectX 7
#if DIRECTX_TARGET_VERSION > 6
#error "Nynthon does not support DirectX 7 or later"
#endif /* DIRECTX_TARGET_VERSION > */

#if DIRECTX_TARGET_VERSION == 6
#ifdef DIRECTINPUT_VERSION
#undef DIRECTINPUT_VERSION
#endif /* DIRECTINPUT_VERSION */
#define DIRECTINPUT_VERSION 0x600
#endif /* DIRECTX_TARGET_VERSION == 6 */

#else

#error "Nynthon is only supported on Windows platform"	

#endif /* _WIN32 */

#ifndef _MSC_VER
#error "Nynthon only supports Microsoft Visual C Compiler"
#else
#if _MSC_VER != 1500
#error "Nynthon is only supported on Microsoft Visual C 9.1 Compiler"
#endif /* _MSC_VER != */
#endif /* !_MSC_VER */

#endif /* _NY_PLATFORM_H_ */
