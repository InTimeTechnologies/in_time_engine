setlocal
@echo off

echo running clean_glew.bat

REM arguments
set "DEPENDENCY_DIR=%~1"
set "CONFIGURATION=%~2"
set "PLATFORM=%~3"
echo solution directory:              "%DEPENDENCY_DIR%"
echo configuration:                   "%CONFIGURATION%"
echo platform:                        "%PLATFORM%"
if "%DEPENDENCY_DIR%"=="" (
    echo DEPENDENCY_DIR not passed to script (directory to glfw root^)
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
set "BUILD_DIR=%DEPENDENCY_DIR%\build\vc15\tmp"
set "INSTALL_DIR=%DEPENDENCY_DIR%\lib\%CONFIGURATION%"
set "BUILD_STAMP=%~dp0build_stamps\glew_%CONFIGURATION%_lib_built.stamp"
echo BUILD_DIR:                       "%BUILD_DIR%"
echo INSTALL_DIR:                     "%INSTALL_DIR%"
echo BUILD_STAMP:                     "%BUILD_STAMP%"

set "GLEW_SHARED_BUILD=%BUILD_DIR%\glew_shared\%CONFIGURATION%\%PLATFORM%"
set "GLEW_STATIC_BUILD=%BUILD_DIR%\glew_static\%CONFIGURATION%\%PLATFORM%"
set "GLEW_INFO_BUILD=%BUILD_DIR%\glewinfo\%CONFIGURATION%\%PLATFORM%"
set "GLEW_VISUAL_INFO_BUILD=%BUILD_DIR%\visualinfo\%CONFIGURATION%\%PLATFORM%"
echo GLEW_SHARED_BUILD:               "%GLEW_SHARED_BUILD%"
echo GLEW_STATIC_BUILD:               "%GLEW_STATIC_BUILD%"
echo GLEW_INFO_BUILD:                 "%GLEW_INFO_BUILD%"
echo GLEW_VISUAL_INFO_BUILD:          "%GLEW_VISUAL_INFO_BUILD%"

REM delete configuration build and install directories and build stamp
echo cleaning GLEW_SHARED_BUILD:      "%GLEW_SHARED_BUILD%"
if exist "%GLEW_SHARED_BUILD%" rmdir /s /q "%GLEW_SHARED_BUILD%"
echo cleaning GLEW_STATIC_BUILD:      "%GLEW_STATIC_BUILD%"
if exist "%GLEW_STATIC_BUILD%" rmdir /s /q "%GLEW_STATIC_BUILD%"
echo cleaning GLEW_INFO_BUILD:        "%GLEW_INFO_BUILD%"
if exist "%GLEW_INFO_BUILD%" rmdir /s /q "%GLEW_INFO_BUILD%"
echo cleaning GLEW_VISUAL_INFO_BUILD: "%GLEW_VISUAL_INFO_BUILD%"
if exist "%GLEW_VISUAL_INFO_BUILD%" rmdir /s /q "%GLEW_VISUAL_INFO_BUILD%"
echo cleaning INSTALL_DIR:            "%INSTALL_DIR%"
if exist "%INSTALL_DIR%" rmdir /s /q "%INSTALL_DIR%"
echo deleting BUILD_STAMP:            "%BUILD_STAMP%"
if exist "%BUILD_STAMP%" del /f /q "%BUILD_STAMP%"
