setlocal
@echo off

echo running clean_all.bat

REM arguments
set "SOLUTION_DIR=%~1"
if "%SOLUTION_DIR%"=="" for %%I in ("%~dp0..\..") do set "SOLUTION_DIR=%%~fI\"
echo SOLUTION_DIR:         "%SOLUTION_DIR%"

REM script names
set "SCRIPT_DIR=%~dp0"
set "SCRIPT_CLEAN=%SCRIPT_DIR%clean.bat"
set CONFIGURATION_DEBUG=Debug
set CONFIGURATION_RELEASE=Release
set PLATFORM=x64
echo SCRIPT_DIR:   "%SCRIPT_DIR%"
echo SCRIPT_CLEAN: "%SCRIPT_CLEAN%"
echo CONFIGURATION_DEBUG:   Debug
echo CONFIGURATION_RELEASE: Release

REM clean all
call "%SCRIPT_CLEAN%" "%SOLUTION_DIR%" %CONFIGURATION_DEBUG% %PLATFORM%
call "%SCRIPT_CLEAN%" "%SOLUTION_DIR%" %CONFIGURATION_RELEASE% %PLATFORM%
