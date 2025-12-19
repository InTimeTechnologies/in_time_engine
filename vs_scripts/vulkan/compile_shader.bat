REM TODO: Test this script (you have not done so)
REM TODO: glslc does not create intermidiary paths. You need to add this functionality to this script, just like the one in compile_shaders.bat

setlocal enabledelayedexpansion
@echo off

echo running compile_shader.bat

REM arguments
set "IN_PATH=%~1"
set "OUT_PATH=%~2"
echo IN_PATH:    "%IN_PATH%"
echo OUT_PATH:   "%OUT_PATH%"
if "%IN_PATH%"=="" (
    echo IN_PATH argument not passed to script
    echo aborting compilation
    exit /b 1
)
if "%OUT_PATH%"=="" (
    echo OUT_PATH argument not passed to script
    echo aborting compilation
    exit /b 1
)

REM validate IN_PATH exists
if not exist "%IN_PATH%" (
    echo IN_PATH "%IN_PATH%" does not exist
    echo aborting compilation
    exit /b 1
)

REM glslc
set "GLSLC_PATH=%VULKAN_SDK%\bin\glslc.exe"
echo GLSLC_PATH: "%GLSLC_PATH%"

REM validate glslc is present in GLSLC_PATH
if not exist "%GLSLC_PATH%" (
    echo glslc not found in %GLSLC_PATH%
    echo aborting compilation
    exit /b 1
)

REM compile
"%GLSLC_PATH%" "%IN_PATH%" -o "%OUT_PATH%"

endlocal
exit /b 0