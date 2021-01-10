@ECHO OFF

SET project=%cd%
SET code=%project%\code

IF NOT EXIST build MKDIR build

IF NOT DEFINED DevEnvDir (
	call "J:\Program Files (x86)\Microsoft Visual Studio\2019\Preview\VC\Auxiliary\Build\vcvarsall.bat" amd64 >nul
)

SET debug_flags=^
	-Zi^
	-Od^
	-MTd^
	-DEBUG

SET common_compiler_flags=^
	%debug_flags%^
	-nologo^
	-FC^
	-fp:fast^
	-GR-^
	-EHa-^
	-Oi^
	-MTd^
	-TP^
	-Wall^
	-WX^
	-wd4201^
	-wd4100^
	-wd4189^
	-wd4101^
	-wd4068^
	-wd4820^
	-wd4505

SET defines=^
	-DJED_SLOW=1

SET libs=^
	User32.lib^
	Gdi32.lib^
	Winmm.lib^
	Kernel32.lib

SET linker_flags=^
	-link^
	-incremental:no^
	-opt:ref^
	-SUBSYSTEM:WINDOWS^
	%libs%


SET include_directories=^
	-I %project%\include

PUSHD build

REM Precomipiled Header
cl^
	%debug_flags%^
	%defines%^
	%include_directories%^
	%common_compiler_flags%^
	-c^
	-Yc"pch.h"^
	%code%\pch.cpp

REM Platform Layer
cl^
	%defines%^
	%include_directories%^
	%common_compiler_flags%^
	-Yu"pch.h"^
	%code%\win32_main.cpp^
	-Fejed^
	%linker_flags%^
	pch.obj

POPD

IF %ERRORLEVEL% NEQ 0  (
	ECHO 	   ===============
	ECHO Error:	%ERRORLEVEL%
	ECHO 	   ================
)