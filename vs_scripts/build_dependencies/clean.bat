setlocal
@echo off

echo running clean.bat

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

REM dependency directories
set "DEPENDENCY_DIR=%SOLUTION_DIR%dependencies"
set "DEPENDENCY_DIR_BOX2D=%DEPENDENCY_DIR%\box2d"
set "DEPENDENCY_DIR_GLFW=%DEPENDENCY_DIR%\glfw"
set "DEPENDENCY_DIR_GLEW=%DEPENDENCY_DIR%\glew"
echo dependencies directory:     "%DEPENDENCY_DIR%"
echo box2d dependency directory: "%DEPENDENCY_DIR_BOX2D%"
echo glew dependency directory:  "%DEPENDENCY_DIR_GLFW%"
echo glfw dependency directory:  "%DEPENDENCY_DIR_GLEW%"

REM dependency clean scripts
set "SCRIPT_DIR=%~dp0"
set "CLEAN_BOX2D_SCRIPT=%SCRIPT_DIR%clean_box2d.bat"
set "CLEAN_GLFW_SCRIPT=%SCRIPT_DIR%clean_glfw.bat"
set "CLEAN_GLEW_SCRIPT=%SCRIPT_DIR%clean_glew.bat"
echo script directory:           "%SCRIPT_DIR%"
echo box2d clean script:         "%CLEAN_BOX2D_SCRIPT%"
echo glfw clean script:          "%CLEAN_GLFW_SCRIPT%"
echo glew clean script:          "%CLEAN_GLEW_SCRIPT%"

REM clean submodules and dependencies
call "%CLEAN_BOX2D_SCRIPT%" "%DEPENDENCY_DIR_BOX2D%" "%CONFIGURATION%" "%PLATFORM%"
call "%CLEAN_GLFW_SCRIPT%" "%DEPENDENCY_DIR_GLFW%" "%CONFIGURATION%" "%PLATFORM%"
call "%CLEAN_GLEW_SCRIPT%" "%DEPENDENCY_DIR_GLEW%" "%CONFIGURATION%" "%PLATFORM%"
