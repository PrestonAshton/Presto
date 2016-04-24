@echo off
if not defined DevEnvDir (
    call "%VS140COMNTOOLS%vsvars32.bat"
)
set /p buildId=<build.txt
set /a nextBuildId=buildId+1
echo Building Presto - Build %nextBuildId%
msbuild Template.sln /property:Platform=x64 /property:Configuration=Debug /p:BuildNumber=%nextBuildId%
echo %nextBuildId%>build.txt
