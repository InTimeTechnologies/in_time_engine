setlocal
@echo off

echo running build_dependencies.bat

REM arguments
set "SOLUTION_DIR=%~1"
set "CONFIGURATION=%~2"
set "PLATFORM=%~3"
echo solution directory:         "%SOLUTION_DIR%"
echo configuration:              "%CONFIGURATION%"
echo platform:                   "%PLATFORM%"

REM dependency directories
set "DEPENDENCY_DIR=%SOLUTION_DIR%dependencies"
set "DEPENDENCY_DIR_BOX2D=%DEPENDENCY_DIR%\box2d"
set "DEPENDENCY_DIR_GLFW=%DEPENDENCY_DIR%\glfw"
set "DEPENDENCY_DIR_GLEW=%DEPENDENCY_DIR%\glew"
echo dependencies directory:     "%DEPENDENCY_DIR%"
echo box2d dependency directory: "%DEPENDENCY_DIR_BOX2D%"
echo glew dependency directory:  "%DEPENDENCY_DIR_GLFW%"
echo glfw dependency directory:  "%DEPENDENCY_DIR_GLEW%"

REM dependency build scripts
set "SCRIPT_DIR=%~dp0"
set "BUILD_BOX2D_SCRIPT=%SCRIPT_DIR%build_box2d_dependency.bat"
set "BUILD_GLFW_SCRIPT=%SCRIPT_DIR%build_glfw_dependency.bat"
set "BUILD_GLEW_SCRIPT=%SCRIPT_DIR%build_glew_dependency.bat"
echo script directory:           "%SCRIPT_DIR%"
echo box2d build script:         "%BUILD_BOX2D_SCRIPT%"
echo glfw build script:          "%BUILD_GLFW_SCRIPT%"
echo glew build script:          "%BUILD_GLEW_SCRIPT%"

REM build submodules and dependencies
call "%BUILD_BOX2D_SCRIPT%" "%DEPENDENCY_DIR_BOX2D%" "%CONFIGURATION%" "%PLATFORM%"
call "%BUILD_GLFW_SCRIPT%" "%DEPENDENCY_DIR_GLFW%" "%CONFIGURATION%" "%PLATFORM%"
call "%BUILD_GLEW_SCRIPT%" "%DEPENDENCY_DIR_GLEW%" "%CONFIGURATION%" "%PLATFORM%"

endlocal
