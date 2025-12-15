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

REM directories
set "BUILD_DIR=%DEPENDENCY_DIR%\build\%CONFIGURATION%"
set "INSTALL_DIR=%DEPENDENCY_DIR%\install\%CONFIGURATION%"
echo build directory:      "%BUILD_DIR%"
echo install directory:    "%INSTALL_DIR%"

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"
echo Current working directory: %CD%

cmake ../.. -G "Visual Studio 17 2022" -A %PLATFORM% -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX="%INSTALL_DIR%"
cmake --build . --config %CONFIGURATION% --target install -- /m

set EXIT_CODE=%ERRORLEVEL%
endlocal & exit /b %EXIT_CODE%