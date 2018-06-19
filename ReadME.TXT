 .-._                          .-._          ,--.--------.   ,--.-,,-,--,     _,.---._      .-._         
/==/ \  .-._   ,--.-.  .-,--. /==/ \  .-._  /==/,  -   , -\ /==/  /|=|  |   ,-.' , -  `.   /==/ \  .-._  
|==|, \/ /, / /==/- / /=/_ /  |==|, \/ /, / \==\.-.  - ,-./ |==|_ ||=|, |  /==/_,  ,  - \  |==|, \/ /, / 
|==|-  \|  |  \==\, \/=/. /   |==|-  \|  |   `--`\==\- \    |==| ,|/=| _| |==|   .=.     | |==|-  \|  |  
|==| ,  | -|   \==\  \/ -/    |==| ,  | -|        \==\_ \   |==|- `-' _ | |==|_ : ;=:  - | |==| ,  | -|  
|==| -   _ |    |==|  ,_/     |==| -   _ |        |==|- |   |==|  _     | |==| , '='     | |==| -   _ |  
|==|  /\ , |    \==\-, /      |==|  /\ , |        |==|, |   |==|   .-. ,\  \==\ -    ,_ /  |==|  /\ , |  
/==/, | |- |    /==/._/       /==/, | |- |        /==/ -/   /==/, //=/  |   '.='. -   .'   /==/, | |- |  
`--`./  `--`    `--`-`        `--`./  `--`        `--`--`   `--`-' `-`--`     `--`--''     `--`./  `--`  


								MythOS Rebirth/Nynthon Engine
					Copyright (C) 2018 Arves100. All Rights Reserved.

								 Refreshed Windows Version
							   *** Development Version: 0.1 ***

									   31, May 2018

 ---------------------------------------------------------------------------
 This software is based from MythOS 98 MIT Release. 
 See https://github.com/walbourn/mythosengine for the original source.
 
 
 ---------------------------------------------------------------------------
 INSTALLATION

 Select Start/Run... and select 'setup.exe'.  Follow the instructions
 given in the setup program.

 To build the code, you will need Windows 98 Platform SDK (1998) or,
 at your option, any later SDK that supports DirectX 6 or later.

 ---------------------------------------------------------------------------
 SETUP
 
 Define any _WIN32_WINNT version major or greater than Windows 98 to enable
 extensive support for that platform. (Source officially uses Windows XP
 (0x501) target)
 
 You can enable deprectad support for DirectX 6 by editing the macro
 DIRECTX_TARGET_VERSION in "Platform.h" header

 ---------------------------------------------------------------------------
 DIRECTORIES

 The following structure will be placed onto the destination drive:

 \
 +--Inc                             Includes
 |
 +--Bin                             Utility programs
 |
 +--Lib                             Production Libraries (multi-threaded static)
 |  |
 |  +--Assert                       Assert version of libraries (multi-threaded static)
 |  |
 |  +--ML                           Production Libraries (single-threaded)
 |  |
 |  +--Assert.ML                    Assert version libraries (single-threaded)
 |  |
 |  +--Assert.MD                    Assert version libraries (multi-threaded DLL)
 |  |
 |  +--MD                           Production Libraries (multi-threaded DLL)
 |
 +--Source
    +--Bach                         Bach (Sound library)
    |  +--Inc
    |  |
    |  +--Obj
    |  |
    |  +--Test
    |     +--Obj
    |   
    +--Bozo                         Bozo (Task switcher)
    |  +--Inc
    |  |
    |  +--Obj
    |  |
    |  +--Test
    |     +--Obj
    |   
    +--Chronos                      Chronos (Timer services)
    |  +--Inc
    |  |
    |  +--Obj
    |  |
    |  +--Test
    |     +--Obj
    |
    +--Escher                       Escher (3D Graphics System)
    |  +--Inc
    |  |
    |  +--Build
    |  |
    |  +--Draw
    |  |
    |  +--Element
    |  |
    |  +--Light
    |  |
    |  +--Math
    |  |
    |  +--Motion
    |  |
    |  +--Particle
    |  |
    |  +--Partn
    |  |
    |  +--Terrain
    |  |
    |  +--Texture
    |  |
    |  +--Obj
    |  |
    |  +--Edit                             Terrain Editor
    |  |
    |  +--Tool                             Object Viewer Tool
    |  |
    |  +--Test
    |  |  +--Data
    |  |  |
    |  |  +--Obj
    |  | 
    |  +--Util                             Directory, Converters, and Texture Librarian
    |  |  +--Obj
    |  | 
    |  +--Export                           3D Studio for DOS R4 Exporter
    |     +--Inc
    |     |
    |     +--Lib
    |     |
    |     +--Obj
    |
    +--Examples                     Example Code
    |  |
    |  +--Viewer
    |  |  +--Obj
    |  | 
    |  +--LLander
    |  |  +--Data
    |  |  |
    |  |  +--Obj
    |  | 
    |  +--Script
    |     +--Data
    |     |
    |     +--Obj
    |
    +--Felix                        Felix (Fixed-point support)
    |  +--Inc
    |  |
    |  +--Obj
    |  |
    |  +--Test
    |     +--Obj
    |
    +--Gutenbrg                     Gutenberg (Font and string support)
    |  +--Inc 
    |  |
    |  +--Obj
    |  |
    |  +--Test
    |  |  +--Obj
    |  | 
    |  +--Util
    |     +--Obj
    |
    +--Help                         Help Master and Project Files
    |
    |
    +--Ivory                        Ivory (Memory-manager)
    |  +--Inc
    |  |
    |  +--Obj
    |  |
    |  +--Test
    |     +--Obj
    |
    +--Max                          Max (Event-system)
    |  +--Inc
    |  |
    |  +--Obj
    |  |
    |  +--Test
    |  |  +--Obj
    |  | 
    |  +--Util
    |     +--Obj
    |
    +--Newton                       Newton (Physics system)
    |  +--Inc
    |  |
    |  +--Obj
    |  |
    |  +--Test
    |     +--Obj
    |
    +--Pane                         Pane (GUI Helper Library)
    |  +--Inc
    |  |
    |  +--Obj
    |
    +--SimGine                      SimGine Framework (Simulation framework)
    |  +--Inc
    |  |
    |  +--Obj
    |  |
    |  +--Test
    |     +--Res
    |     |
    |     +--Obj
    |
    +--Spielberg                    Spielberg (Animation/movie player)
    |  +--Inc
    |  |
    |  +--Obj
    |  |
    |  +--Test
    |     +--Obj
    |
    +--System                       NynthonEngine System
    |  +--Inc
    |  |
    |  +--Obj
    |  |
    |  +--Test
    |     +--Obj
    |
    +--Turner                       Turner (Network system)
    |  +--Inc
    |  |
    |  +--Obj
    |
    +--Util                         NynthonEngine General Utilities
    |  +--Obj
    |
    +--VanGogh                      Van Gogh (2D Graphics System)
    |  +--Inc
    |  |
    |  +--8BPP 
    |  |
    |  +--16BPP
    |  |
    |  +--Boards
    |  |
    |  +--Screen
    |  |
    |  +--Obj
    |  |
    |  +--PalTool
    |  |
    |  +--Test
    |     +--Obj
    |
    +--XFile                        XFile (File system)
       +--Inc
       |
       +--IFF
       |
       +--INI 
       |
       +--IO
       |
       +--Bitmap
       |
       +--Obj
       |
       +--Test
       |  +--Obj
       | 
       +--Util
          +--Obj

    A master solution (MythOSRebirth.sln) for Visual Studio 2008 is provided
	for building the engine.
    

 
 ---------------------------------------------------------------------------
 RELEASE NOTES

    See the WHATSNEW.TXT for a list of major changes since the last
    release.

    README.TXT's are in each of the library component directories with
    current status and work notes.

    This version of NynthonEngine was built with Microsoft Visual C++ v9.0.
	 (Microsoft Visual Studio 2008) with DirectX 7 SDK

    The engine allows building with dynamic/static linking of MSVC at your
	option (/MT or /MD). See configurations for more information.

    MFC Version 6.x support DLLs are installed as part of the NynthonEngine
    installation procedure since they are required by the MFC-based tools.

    Several of the utilities require a PD utility, Flex, which must be 
    located in C:\FLEX in order to build the executable.  Unzip the FLEX.ZIP
    contained in the root directory of the installed tree structure into
    C:\FLEX (must be this directory!) and put C:\FLEX in your path.

    A 3D Studio MAX exporter was planned, but has not been completed.
    If time permits, Chuck will try to complete at least a basic
    exporter for 3DS MAX.

      
    
 ---------------------------------------------------------------------------
 EXAMPLES

    This release includes some example code to get you started.  The
    ReadME files for the examples give details on thier function.

    The Viewer example is a simple object viewer with interactive controls
    simliar to the Microsoft Direct3D Viewer sample.  This is a great
    place to see how to handle all of the initialization issues for MythOS
    and how to respond to various error conditions.

    The second example, Lunar Lander, was previously the GameFrame
    example and has been converted over to use the SimGine framework.  It
    makes use of more of the 2D and support functionality of MythOS.

    Script, our third example, is a simple scripting system for creating,
    modifying, and animating cameras, lights, meshes, and particle
    generators.  This could be extended in many directions, but the system
    does allow you to play with various parameters and try out some simple
    physics stuff with Newton.
    


 ---------------------------------------------------------------------------
 VIEWING CODE

    The commenting style uses extended IBM characters.  To properly view
    them, set your editor to use the 'Terminal' font--most editors default
    to Courier.



 ---------------------------------------------------------------------------
 BUILDING CODE

    The majority of the code has been setup to build and run from the
    Visual Studio program.
	
	Platforms:
		WIN32			Windows NT platforms with a x86 compatible processor.
			
	Configurations:
		MTDEBUG			Debug configuration with no optimization, used for developing and
						debugging the engine. Multithread variant (MT).

		MTRELEASE		Retail version of the enigne with debug symbols and optimization,
						used for testing the product before shipping. Multithread variant (MT).
		
		MTDISTRIBUTE	Retail version with no debug symbols, shipped to the end-user.
						Multithread variant (MT).

		MDDEBUG			Debug configuration with no optimization, used for developing and
						debugging the engine. Multithreaded DLL variant (MD).

		MDRELEASE		Retail version of the enigne with debug symbols and optimization,
						used for testing the product before shipping. Multithreaded DLL variant (MD).
		
		MDDISTRIBUTE	Retail version with no debug symbols, shipped to the end-user.
						Multithreaded DLL variant (MD).
						
 ---------------------------------------------------------------------------
 BUILDING HELP

    The HLP file is constructed from RTF files in the Source\Help directory
    along with RTF files in each libraries' source directory.  To rebuild
    the help, run the 'make.bat' batch in the Source\Help directory after
    editing it to point to the Help Compiler on your system.



 ---------------------------------------------------------------------------
 PROBLEMS/BUGS

    This library is provided on an "as-is" basis and no supported is
    provided.  Any future releases or bug-fixes will be posted to the
    MythOS Home Page (http://www.mythos-engine.org/).

    Send comments and suggestions to mythos@mythos-engine.org.  Bug
    reports should be sent to mythos_bugs@mythos-engine.org.


 ---------------------------------------------------------------------------
 FUTURE RELEASES

    The MythOS 95 library set represents a technology base started in 1994
    for use in Charybdis' first title.  We had plans for the development
    of a new 2.0 version of the library to provide a major rewrite of the
    graphics libraries (Van Gogh and Escher) to update for the shift
    to 3D graphics consumer hardware from software-based rendering
    on 486 class computers.  This version was to be called "MythOS 98".

    We are not making any commitments for a future version, but there are
    a number of plans which may or may not materialize.  Any such work
    will take place on a part-time basis and would hopefully be released
    using the same Open Source license.  The new version would be a major
    rewrite and would not be compatable with MythOS 95.

END OF DOCUMENT
