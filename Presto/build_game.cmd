@echo off
cls
color 07

set "ourpath=%~dp0"
set "clangpath="C:\Program Files\LLVM\bin\clang.exe""
set "unitybuild=%ourpath%/engine/engine/src/UnityBuild.c"
set "unitybuildlauncher=%ourpath%/engine/launcher/src/UnityBuild.c"
set "includedir=%ourpath%/engine/engine/include"
set "warnings=-Wno-invalid-token-paste -Wno-int-conversion -Wno-microsoft-include"
set "definitions=-D_CRT_SECURE_NO_WARNINGS -DUNICODE"
set "tempdir=%ourpath%/temp"
set "outdir=%ourpath%/game/build"

if exist %clangpath% (
  echo Found Clang...
  echo Building Engine...
  %clangpath% %unitybuild% -Wl,-map -I%includedir% %warnings% %definitions% -g -DQUEST -shared -o %outdir%/bin64/engine.dll
  echo Building Launcher...
  %clangpath% %unitybuildlauncher% -I%includedir% %warnings% %definitions% -DLAUNCHER -g -o %outdir%/quest64.exe
) else (
  echo Clang is not installed on your system!
  echo http://llvm.org/releases/download.html
)