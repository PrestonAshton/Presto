@echo off
cls
color 07

set "ourpath=%~dp0"
set "clangpath="C:\Program Files\LLVM\bin\clang.exe""
set "unitybuild=engine/engine/src/UnityBuild.c"
set "unitybuildlauncher=engine/launcher/src/UnityBuild.c"
set "includedir=engine/engine/include"
set "warnings=-Wno-invalid-token-paste -Wno-int-conversion -Wno-microsoft-include"
set "definitions=-D_CRT_SECURE_NO_WARNINGS -DUNICODE -DLAUNCHER"
set "tempdir=temp"
set "outdir=game/build"

if exist %clangpath% (
  echo Found Clang...
  echo Building Launcher...
  %clangpath% %unitybuildlauncher% -I%includedir% %warnings% %definitions% -g -o %outdir%/quest64.exe
) else (
  echo Clang is not installed on your system!
  echo http://llvm.org/releases/download.html
)

pause
