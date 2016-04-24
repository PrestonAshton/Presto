@echo off
:Start
IF "%1"=="" GOTO NoArgs
GOTO Build
:Build
echo Generating projects for %1.
pushd %~dp0
set THIS_DIR=%CD%
popd
"bin/premake5.exe" --file="%THIS_DIR%\scripts\%1.lua" clean
"bin/premake5.exe" --file="%THIS_DIR%\scripts\%1.lua" %2
GOTO End
:NoArgs
echo You must select the name of a game to build!
:End