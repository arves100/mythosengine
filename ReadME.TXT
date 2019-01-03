Last effort I made for update and build with very old game engine. (This changes were made months ago in a private GitLab repository)
The updated version was going to be named Nynthon Engine and was originaly supposed to work with SEGA Dreamcast hardware using Windows CE Toolkit.

MythOS game engine is using a lot of exclusive DirectX 6.1A SDK functionality.
The license of this project will be Apache 2.0 (Hoping it won't break MIT license)

The last commit was made around 2018.

There isn't much done, the project was converted into Visual Studio 2018 and DirectX SDK 6.1A.
All the executables could be builded correctly, but there are some issues.

-----------------------------------------------------------------------------------------------------------------------
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

 To build the code, you will need Windows 2000 Platform SDK (2001) or,
 at your option, any later SDK that supports DirectX 6.1A or later.

 ---------------------------------------------------------------------------
 SETUP
 
 Define any _WIN32_WINNT version equal or greater than Windows 2000 to enable
 extensive support for that platform.
  
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
	
	See UpdatingFromMythos95.txt for a quick guide on upgrading your game
	from MythOS95 to NynthonEngine.

    This version of NynthonEngine was built with Microsoft Visual C++ v9.0/Visual Studio 2008
	with DirectX 7 SDK and Multithreaded DLL support (MD).

    A 3D Studio MAX exporter was planned, but has not been completed.
    If time permits, Chuck will try to complete at least a basic
    exporter for 3DS MAX.
      
    
 ---------------------------------------------------------------------------
 EXAMPLES

    This release includes some example code to get you started.  The
    ReadME files for the examples give details on thier function.

    The Viewer example is a simple object viewer with interactive controls
    simliar to the Microsoft Direct3D Viewer sample.  This is a great
    place to see how to handle all of the initialization issues for NynthonEngine
    and how to respond to various error conditions.

    The second example, Lunar Lander, was previously the GameFrame
    example and has been converted over to use the SimGine framework.  It
    makes use of more of the 2D and support functionality of NynthonEngine.

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
		DEBUG			Debug configuration with no optimization, used for developing and
						debugging the engine.

		RELEASE		Retail version of the enigne with debug symbols and optimization,
						used for testing the product before shipping.
		
		DISTRIBUTE	Retail version with no debug symbols, shipped to the end-user.

 ---------------------------------------------------------------------------
 BUILDING HELP

    The HLP file is constructed from RTF files in the Source\Help directory
    along with RTF files in each libraries' source directory.  To rebuild
    the help, run the 'make.bat' batch in the Source\Help directory after
    editing it to point to the Help Compiler on your system.



 ---------------------------------------------------------------------------
 PROBLEMS/BUGS

    Send comments, suggestions and bugs using GitLab's Issue page.
	
	Current workaround (as of git: )
		BUG: IvoryTest multiple arena allocation fails
		BUG: XFileTest fails multiple IO tests.
		ISSUE: XFileTest contains about 7 memory leaks
		ISSUE: TurnerTest not tested
		BUG: EscherTest input isn't workings
		BUG: MaxTest dosen't work
		BUG: Escher render in MFC applications seems not working
		BUG: BozoTest fails. Queue not passed correctly.
		ISSUE: LLander example isn't tested with DirectPlay functionality.

 ---------------------------------------------------------------------------
 FUTURE RELEASES

    Nynthon Engine is currently work in progress, there are several features planned
	that will break the old compatibility with MythOS95.
	
	Planned features:
		[ ] Passing all tests on modern computers
		[ ] Fixing all memory leaks and runtime problems
		[ ] Upgrade to DirectX 7
		[ ] Add multiple devices support
		[ ] Fully upgrade to Windows 2000
		
END OF DOCUMENT
