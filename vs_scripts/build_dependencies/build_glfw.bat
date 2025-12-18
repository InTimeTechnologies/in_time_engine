setlocal
@echo off

echo running build_glfw_dependency.bat

REM arguments
set "DEPENDENCY_DIR=%~1"
set "CONFIGURATION=%~2"
set "PLATFORM=%~3"
echo dependency directory: "%DEPENDENCY_DIR%"
echo configuration:        "%CONFIGURATION%"
echo platform:             "%PLATFORM%"
if "%DEPENDENCY_DIR%"=="" (
    echo DEPENDENCY_DIR not passed to script (directory to glfw root^)
    echo aborting glfw build
    exit /b 1
)
if "%CONFIGURATION%"=="" (
    echo CONFIGURATION not passed to script (Debug or Release^)
    echo aborting glfw build
    exit /b 1
)
if "%PLATFORM%"=="" (
    echo PLATFORM not passed to script (x64^) (x32 not supported^)
    echo aborting glfw build
    exit /b 1
)

REM check if glfw library has been built in the passed configuration
set "BUILD_STAMP_DIR=%~dp0build_stamps"
set "BUILD_STAMP_PATH=%BUILD_STAMP_DIR%\glfw_%CONFIGURATION%_lib_built.stamp"
echo BUILD_STAMP_DIR:   "%BUILD_STAMP_DIR%"
echo BUILD_STAMP_PATH: "%BUILD_STAMP_PATH%"
if exist "%BUILD_STAMP_PATH%" (
	echo aborting glfw build reason: detected build stamp at: %BUILD_STAMP_PATH%
	exit /b 0
)
if not exist "%BUILD_STAMP_DIR%" md "%BUILD_STAMP_DIR%"

REM directories
set "BUILD_DIR=%DEPENDENCY_DIR%\build\%CONFIGURATION%"
set "INSTALL_DIR=%DEPENDENCY_DIR%\install\%CONFIGURATION%"
echo build directory:   "%BUILD_DIR%"
echo install directory: "%INSTALL_DIR%"

REM cd into build directory
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"
echo Current working directory: %CD%

REM configure cmake
cmake ../.. -G "Visual Studio 17 2022" -A %PLATFORM% -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX="%INSTALL_DIR%"
if ERRORLEVEL 1 (
    echo cmake failed to configure
    exit /b 1
)
REM cmake install include and lib files
cmake --build . --config %CONFIGURATION% --target install -- /m
if ERRORLEVEL 1 (
    echo cmake failed to install glfw
    exit /b 1
)

REM create glfw build stamp for passed configuration
type nul > "%BUILD_STAMP_PATH%"

set EXIT_CODE=%ERRORLEVEL%
endlocal & exit /b %EXIT_CODE%