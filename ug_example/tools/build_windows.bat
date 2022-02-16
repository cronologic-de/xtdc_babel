@echo off

echo _______________________________________________________________________________
echo Overview:
echo .
echo This file is used on development environment to save time writing down all 
echo commands to build Windows project using MSVC MSBuild.
echo All steps and values should be aligned with the build instructions 
echo mentioned in the readme file 
echo `https://github.com/cronologic-de/xtdc_babel/blob/main/README.md`.
echo .
echo Output is found on `../build/bfvs` for x86, and `../build/bfvs32` for x86. 
echo The batch cleans up the folders and rebuilds the code with every run.
echo .
echo Please review values under `Custom Values` section before you start.
echo _______________________________________________________________________________

setlocal
:PROMPT
SET /P CONAN_UPLOAD=Upload to conan cache ([Y]/N)?
IF /I "%CONAN_UPLOAD%" NEQ "N" SET CONAN_UPLOAD=Y

REM Settings
set TOOLS_WIN_DIR=%CD%
set ROOT_DRIVE=%CD:~0,2%
set X64_BUILD_DIR=%TOOLS_WIN_DIR%\..\build\bfvs
set WIN32_BUILD_DIR=%TOOLS_WIN_DIR%\..\build\bfvs32

REM Custom Values
REM Update the following values based on your environment
set MSVS_MSBUILD_DRIVE=C:
set MSVS_MSBUILD_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64
set DUMPBIN_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\SDK\ScopeCppSDK\vc15\VC\bin
set MSVS_CMAKE_GENERATOR="Visual Studio 16 2019"
REM set MSVS_CMAKE_GENERATOR="Visual Studio 14 2015"

echo _______________________________________________________________________________
echo crono: Building x64 Project Buildsystem ...
echo -------------------------------------------------------------------------------
REM Create x64 build directory, and clean it up if already there
if exist %X64_BUILD_DIR%\ (
    echo "Crono: build directory <%X64_BUILD_DIR%\> found, and will be removed"
    rmdir /s /q %X64_BUILD_DIR%\
)

REM Generate the build system files for x64 using CMake
cmake -B %X64_BUILD_DIR% -G %MSVS_CMAKE_GENERATOR%  -A x64

echo _______________________________________________________________________________
echo crono: Building x64 Projects ...
echo -------------------------------------------------------------------------------
%MSVS_MSBUILD_DRIVE%
cd %MSVS_MSBUILD_PATH%
msbuild %X64_BUILD_DIR%\ALL_BUILD.vcxproj /property:Configuration=Release -t:Rebuild
msbuild %X64_BUILD_DIR%\ALL_BUILD.vcxproj /property:Configuration=Debug -t:Rebuild

REM Back to tools
%ROOT_DRIVE%
cd %TOOLS_WIN_DIR%
if "%CONAN_UPLOAD%" == "Y" (
    echo _______________________________________________________________________________
    echo crono: Uploading x64 output to conan cache ...
    echo -------------------------------------------------------------------------------
    conan create . -s arch=x86_64 -s build_type=Release
    conan create . -s arch=x86_64 -s build_type=Debug
)

echo _______________________________________________________________________________
echo crono: Building Win32 Project Buildsystem ...
echo -------------------------------------------------------------------------------
REM Create x86 build directory, and clean it up if already there
if exist %WIN32_BUILD_DIR%\ (
    echo "Crono: build directory <%WIN32_BUILD_DIR%\> found, and will be removed"
    rmdir /s /q %WIN32_BUILD_DIR%\
)

REM Generate the build system files for x86 using CMake
cmake -B %WIN32_BUILD_DIR% -G %MSVS_CMAKE_GENERATOR% -A Win32

echo _______________________________________________________________________________
echo crono: Building Win32 Projects ...
echo -------------------------------------------------------------------------------
%MSVS_MSBUILD_DRIVE%
cd %MSVS_MSBUILD_PATH%
msbuild %WIN32_BUILD_DIR%\ALL_BUILD.vcxproj /property:Configuration=Release -t:Rebuild
msbuild %WIN32_BUILD_DIR%\ALL_BUILD.vcxproj /property:Configuration=Debug -t:Rebuild

REM Back to tools
%ROOT_DRIVE%
cd %TOOLS_WIN_DIR%
if "%CONAN_UPLOAD%" == "Y" (
    echo _______________________________________________________________________________
    echo crono: Uploading Win32 output to conan cache ...
    echo -------------------------------------------------------------------------------
    conan create . -s arch=x86 -s build_type=Release
    conan create . -s arch=x86 -s build_type=Debug
)

echo _______________________________________________________________________________
echo crono: Displaying architecture of libraries built using MSBuild ...
echo -------------------------------------------------------------------------------
%MSVS_MSBUILD_DRIVE%
cd %DUMPBIN_PATH%
echo Crono: x86_64 Debug Library ...
dumpbin /headers %X64_BUILD_DIR%\build\windows\x86_64\debug\lib\*.lib | findstr machine
echo Crono: x86_64 Release Library ...
dumpbin /headers %X64_BUILD_DIR%\build\windows\x86_64\release\lib\*.lib | findstr machine
echo Crono: x86 Debug Library ...
dumpbin /headers %WIN32_BUILD_DIR%\build\windows\x86\debug\lib\*.lib | findstr machine
echo Crono: x86 Release Library ...
dumpbin /headers %WIN32_BUILD_DIR%\build\windows\x86\release\lib\*.lib | findstr machine
