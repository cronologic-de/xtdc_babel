@echo off
setlocal

echo _______________________________________________________________________________
echo Overview:
echo .
echo This file is used on development environment to save time writing down all 
echo commands to build Windows project using MSVC MSBuild.
echo All steps and values should be aligned with the build instructions 
echo mentioned in the readme file 
echo `https://github.com/cronologic-de/xtdc_babel/blob/main/README.md`.
echo .
echo Output is found on `../build/bfvs` for x86_64, and `../build/bfvs32` for x86. 
echo The batch cleans up the folders and rebuilds the code with every run.
echo .
echo flags:
echo ======
echo    -c  Build Conan packages and upload them to local cache.
echo        Values: `N` for No, otherwise it is assumed as Yes.
echo .
echo Please review values under `Custom Values` section before you start.
echo _______________________________________________________________________________

REM Process batch parameters
set PUBLISH_LOCAL_PKG=Y
if "%1" == "-c" (
    set PUBLISH_LOCAL_PKG=%2
)

REM All paths should be set relative to base directory in case the batch is called
REM from another directory
set BASEDIR=%~dp0

REM Settings
set TOOLS_WIN_DIR=%BASEDIR%
set ROOT_DRIVE=%BASEDIR:~0,2%
set X64_BUILD_DIR=%TOOLS_WIN_DIR%..\build\bfvs
set WIN32_BUILD_DIR=%TOOLS_WIN_DIR%..\build\bfvs32

REM Custom Values
REM Update the following values based on your environment
set MSVS_MSBUILD_DRIVE=C:
set MSVS_MSBUILD_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64"
set DUMPBIN_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\SDK\ScopeCppSDK\vc15\VC\bin"
set MSVS_CMAKE_GENERATOR="Visual Studio 16 2019"
REM set MSVS_CMAKE_GENERATOR="Visual Studio 14 2015"

echo _______________________________________________________________________________
echo crono: Building x64 Project Buildsystem ...
echo -------------------------------------------------------------------------------
REM Create x64 build directory, and clean it up if already there
if exist %X64_BUILD_DIR% (
    echo Crono: build directory ^<%X64_BUILD_DIR%^> found, and will be cleaned.
    rmdir /s /q %X64_BUILD_DIR%\
) else (
    echo Crono: build directory is ^<%X64_BUILD_DIR%^>
)

REM Generate the build system files for x64 using CMake
cmake -B %X64_BUILD_DIR% -S %BASEDIR% -G %MSVS_CMAKE_GENERATOR% -A x64          ^
    -DCRONO_PUBLISH_LOCAL_PKG=%PUBLISH_LOCAL_PKG%

echo _______________________________________________________________________________
echo crono: Building x64 Projects ...
echo -------------------------------------------------------------------------------
%MSVS_MSBUILD_DRIVE%
cd %MSVS_MSBUILD_PATH%
msbuild %X64_BUILD_DIR%\ALL_BUILD.vcxproj /property:Configuration=Release -t:Rebuild
msbuild %X64_BUILD_DIR%\ALL_BUILD.vcxproj /property:Configuration=Debug -t:Rebuild

echo _______________________________________________________________________________
echo crono: Building Win32 Project Buildsystem ...
echo -------------------------------------------------------------------------------
REM Create x86 build directory, and clean it up if already there
if exist %WIN32_BUILD_DIR%\ (
    echo Crono: build directory ^<%WIN32_BUILD_DIR%^> found, and will be cleaned.
    rmdir /s /q %WIN32_BUILD_DIR%\
) else (
    echo Crono: build directory ^<%WIN32_BUILD_DIR%^>
)

REM Generate the build system files for x86 using CMake
cmake -B %WIN32_BUILD_DIR% -S %BASEDIR% -G %MSVS_CMAKE_GENERATOR% -A Win32      ^
    -DCRONO_PUBLISH_LOCAL_PKG=%PUBLISH_LOCAL_PKG%

echo _______________________________________________________________________________
echo Crono: Building Win32 Projects ...
echo -------------------------------------------------------------------------------
%MSVS_MSBUILD_DRIVE%
cd %MSVS_MSBUILD_PATH%
msbuild %WIN32_BUILD_DIR%\ALL_BUILD.vcxproj /property:Configuration=Release -t:Rebuild
msbuild %WIN32_BUILD_DIR%\ALL_BUILD.vcxproj /property:Configuration=Debug -t:Rebuild

echo _______________________________________________________________________________
echo Crono: Displaying architecture of libraries built using MSBuild ...
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
