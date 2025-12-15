setlocal

set "PLATFORM=%~1"
set "SOLUTION_DIR=%~2"
set "CONFIGURATION=%~3"
set "GLFW_DEPENDENCY_DIR=%SOLUTION_DIR%dependencies\glfw\"
set "GLFW_BUILD_DIR=%GLFW_DEPENDENCY_DIR%build\%CONFIGURATION%"
set "INSTALL_PREFIX=%GLFW_DEPENDENCY_DIR%install\%CONFIGURATION%"

echo Platform: %PLATFORM%
echo SolutionDir: %SOLUTION_DIR%
echo Configuration: %CONFIGURATION%
echo glw solution dir: %GLFW_DEPENDENCY_DIR%
echo glfw build dir: %GLFW_BUILD_DIR%
echo install prefix %INSTALL_PREFIX%

if not exist "%GLFW_BUILD_DIR%" mkdir "%GLFW_BUILD_DIR%"
cd "%GLFW_BUILD_DIR%"
echo Current working directory: %CD%

cmake ../.. -G "Visual Studio 17 2022" -A %PLATFORM% -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX="%INSTALL_PREFIX%"
cmake --build . --config %CONFIGURATION% --target install -- /m

set EXIT_CODE=%ERRORLEVEL%
endlocal & exit /b %EXIT_CODE%