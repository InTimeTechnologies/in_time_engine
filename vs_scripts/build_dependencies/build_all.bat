setlocal
@echo off

echo running build_all.bat

REM arguments
set "SOLUTION_DIR=%~1"
if "%SOLUTION_DIR%"=="" for %%I in ("%~dp0..\..") do set "SOLUTION_DIR=%%~fI\"
echo SOLUTION_DIR:          "%SOLUTION_DIR%"

REM script names
set "SCRIPT_DIR=%~dp0"
set "BOX2D_SCRIPT=%SCRIPT_DIR%build_box2d.bat"
set "GLFW_SCRIPT=%SCRIPT_DIR%build_glfw.bat"
set "GLEW_SCRIPT=%SCRIPT_DIR%build_glew.bat"
echo SCRIPT_DIR:            "%SCRIPT_DIR%"
echo BOX2D_SCRIPT:          "%BOX2D_SCRIPT%"
echo GLFW_SCRIPT:           "%GLFW_SCRIPT%"
echo GLEW_SCRIPT:           "%GLEW_SCRIPT%"

REM arguments to forward to scripts
set "DEPENDENCY_DIR_BOX2D=%SOLUTION_DIR%dependencies\box2d"
set "DEPENDENCY_DIR_GLFW=%SOLUTION_DIR%dependencies\GLFW"
set "DEPENDENCY_DIR_GLEW=%SOLUTION_DIR%dependencies\GLEW"
set CONFIGURATION_DEBUG=Debug
set CONFIGURATION_RELEASE=Release
set PLATFORM=x64
echo DEPENDENCY_DIR_BOX2D:  "%DEPENDENCY_DIR_BOX2D%"
echo DEPENDENCY_DIR_GLFW:   "%DEPENDENCY_DIR_GLFW%"
echo DEPENDENCY_DIR_GLEW:   "%DEPENDENCY_DIR_GLEW%"
echo CONFIGURATION_DEBUG:   %CONFIGURATION_DEBUG%
echo CONFIGURATION_RELEASE: %CONFIGURATION_RELEASE%
echo PLATFORM:              %PLATFORM%

call "%BOX2D_SCRIPT%" "%DEPENDENCY_DIR_BOX2D%" %CONFIGURATION_DEBUG% %PLATFORM%
if ERRORLEVEL 1 (
	echo Failed to build box2d Debug x64
	echo terminating build_all.bat
	exit /b 1
)
call "%BOX2D_SCRIPT%" "%DEPENDENCY_DIR_BOX2D%" %CONFIGURATION_RELEASE% %PLATFORM%
if ERRORLEVEL 1 (
	echo Failed to build box2d Release x64
	echo terminating build_all.bat
	exit /b 1
)
call "%GLFW_SCRIPT%" "%DEPENDENCY_DIR_GLFW%" %CONFIGURATION_DEBUG% %PLATFORM%
if ERRORLEVEL 1 (
	echo Failed to build glfw Debug x64
	echo terminating build_all.bat
	exit /b 1
)
call "%GLFW_SCRIPT%" "%DEPENDENCY_DIR_GLFW%" %CONFIGURATION_RELEASE% %PLATFORM%
if ERRORLEVEL 1 (
	echo Failed to build glfw Release x64
	echo terminating build_all.bat
	exit /b 1
)
call "%GLEW_SCRIPT%" "%DEPENDENCY_DIR_GLEW%" %CONFIGURATION_DEBUG% %PLATFORM%
if ERRORLEVEL 1 (
	echo Failed to build glew Debug x64
	echo terminating build_all.bat
	exit /b 1
)
call "%GLEW_SCRIPT%" "%DEPENDENCY_DIR_GLEW%" %CONFIGURATION_RELEASE% %PLATFORM%
if ERRORLEVEL 1 (
	echo Failed to build glew Release x64
	echo terminating build_all.bat
	exit /b 1
)
