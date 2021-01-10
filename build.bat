@ECHO OFF

SET project=%cd%
SET code=%project%\code

IF NOT EXIST build mkdir build

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
	-ferror-limit=50^
	-Wno-unused-parameter^
	-Wno-unused-variable^
	-Wno-unused-function^
	-Wno-nonportable-system-include-path^
	-Wno-missing-prototypes^
	-Wno-old-style-cast^
	-Wno-language-extension-token^
	-Wno-cast-align^
	-Wno-string-conversion^
	-Wno-zero-as-null-pointer-constant^
	-Wno-extra-semi-stmt^
	-Wno-microsoft-include^
	-Wno-shift-sign-overflow

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

REM Precompiled Header
clang-cl^
	%debug_flags%^
	%defines%^
	%include_directories%^
	%common_compiler_flags%^
	-c^
	-Yc"pch.h"^
	%code%\pch.cpp

REM Platform Layer
clang-cl^
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