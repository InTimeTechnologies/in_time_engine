setlocal
@echo off

echo running clean_glew.bat

REM arguments
set "SOLUTION_DIR=%~1"
set "CONFIGURATION=%~2"
set "PLATFORM=%~3"
echo solution directory: "%SOLUTION_DIR%"
echo configuration:       "%CONFIGURATION%"
echo platform:            "%PLATFORM%"
if "%SOLUTION_DIR%"=="" (
    echo SOLUTION_DIR not passed to script (directory to glfw root^)
    echo aborting clean
    exit /b 1
)
if "%CONFIGURATION%"=="" (
    echo CONFIGURATION not passed to script (Debug or Release^)
    echo aborting clean
    exit /b 1
)
if "%PLATFORM%"=="" (
    echo PLATFORM not passed to script (x64^) (x32 not supported^)
    echo aborting clean
    exit /b 1
)

REM directories
set "BUILD_DIR=%DEPENDENCY_DIR%\build\vc15"
set "INSTALL_DIR=%DEPENDENCY_DIR%\lib\%CONFIGURATION"
set "BUILD_STAMP=%~dp0build_stamps\glew_%CONFIGURATION%_lib_built.stamp"
echo build directory:   "%BUILD_DIR%"
echo install directory: "%INSTALL_DIR%"
echo build stamp:       "%BUILD_STAMP%"

REM delete configuration build and install directories and build stamp
echo cleaning directories and build stamp
if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
if exist "%INSTALL_DIR%" rmdir /s /q "%INSTALL_DIR%"
if exist "%BUILD_STAMP%" del /f /q "%BUILD_STAMP%"
