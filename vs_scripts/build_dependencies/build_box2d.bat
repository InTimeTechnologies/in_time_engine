setlocal
@echo off

echo running build_box2d_dependency.bat

REM arguments
set "DEPENDENCY_DIR=%~1"
set "CONFIGURATION=%~2"
set "PLATFORM=%~3"
echo dependency directory: "%DEPENDENCY_DIR%"
echo configuration:        "%CONFIGURATION%"
echo platform:             "%PLATFORM%"
if "%DEPENDENCY_DIR%"=="" (
    echo DEPENDENCY_DIR not passed to script (directory to box2d root^)
    echo aborting build_box2d.bat
    exit /b 1
)
if "%CONFIGURATION%"=="" (
    echo CONFIGURATION not passed to script (Debug or Release^)
    echo aborting build_box2d.bat
    exit /b 1
)
if "%PLATFORM%"=="" (
    echo PLATFORM not passed to script (x64^) (x32 not supported^)
    echo aborting build_box2d.bat
    exit /b 1
)

REM check if box2d build stamp exist
set "BUILD_STAMP_DIR=%~dp0build_stamps"
set "BUILD_STAMP_PATH=%~dp0build_stamps\box2d_%CONFIGURATION%_lib_built.stamp"
echo BUILD_STAMP_DIR:      "%BUILD_STAMP_DIR%"
echo BUILD_STAMP_PATH:     "%BUILD_STAMP_PATH%"
if exist "%BUILD_STAMP_PATH%" (
	echo skipping box2d build reason: detected build stamp: %BUILD_STAMP_PATH%
	exit /b 0
)
if not exist "%BUILD_STAMP_DIR%" md "%BUILD_STAMP_DIR%"

REM directories
set "BUILD_DIR=%DEPENDENCY_DIR%\build\%CONFIGURATION%"
set "INSTALL_DIR=%DEPENDENCY_DIR%\install\%CONFIGURATION%"
echo BUILD_DIR:            "%BUILD_DIR%"
echo INSTALL_DIR:          "%INSTALL_DIR%"

REM assert .git exists in DEPENDENCY_DIR
set "CMAKE_LISTS=%DEPENDENCY_DIR%\CMakeLists.txt"
echo CMAKE_LISTS:           "%CMAKE_LISTS%"
if exist "%CMAKE_LISTS%" (
    echo CMakeLists.txt found in: "%CMAKE_LISTS%"
) else (
    echo CMakeLists.txt not found in: "%CMAKE_LISTS%"
    echo aborting build_box2d.bat
    exit /b 1
)

REM cd into build directory
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"
echo Current working directory: %CD%

REM configure cmake
cmake ../.. -G "Visual Studio 17 2022" -A %PLATFORM% -DCMAKE_INSTALL_PREFIX="%INSTALL_DIR%"
if ERRORLEVEL 1 (
    echo cmake failed to configure
    echo aborting build_box2d.bat
    exit /b 1
)
REM cmake install include and lib files
cmake --build . --config "%CONFIGURATION%" --target install -- /m
if ERRORLEVEL 1 (
    echo cmake failed to install box2d
    echo aborting build_box2d.bat
    exit /b 1
)

REM create box2d build stamp for passed configuration
type nul > "%BUILD_STAMP_PATH%"

set EXIT_CODE=%ERRORLEVEL%
endlocal & exit /b %EXIT_CODE%