setlocal

set "PLATFORM=%~1"
set "SOLUTION_DIR=%~2"
set "CONFIGURATION=%~3"
set "BOX2D_DEPENDENCY_DIR=%SOLUTION_DIR%dependencies\box2d\"
set "BOX2D_BUILD_DIR=%BOX2D_DEPENDENCY_DIR%build\%CONFIGURATION%"
set "INSTALL_PREFIX=%BOX2D_DEPENDENCY_DIR%install\%CONFIGURATION%"

echo Platform: %PLATFORM%
echo SolutionDir: %SOLUTION_DIR%
echo Configuration: %CONFIGURATION%
echo box2d solution dir: %BOX2D_DEPENDENCY_DIR%
echo box2d build dir: %BOX2D_BUILD_DIR%
echo install prefix %INSTALL_PREFIX%

if not exist "%BOX2D_BUILD_DIR%" mkdir "%BOX2D_BUILD_DIR%"
cd "%BOX2D_BUILD_DIR%"
echo Current working directory: %CD%

cmake ../.. -G "Visual Studio 17 2022" -A %PLATFORM% -DCMAKE_INSTALL_PREFIX="%INSTALL_PREFIX%"
cmake --build . --config %CONFIGURATION% --target install -- /m

set EXIT_CODE=%ERRORLEVEL%
endlocal & exit /b %EXIT_CODE%