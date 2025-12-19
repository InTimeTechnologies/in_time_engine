setlocal enabledelayedexpansion
@echo off

echo running compile_shaders.bat

REM arguments
set "SRC_DIR=%~1"
set "OUT_DIR=%~2"
echo SRC_DIR:    "%SRC_DIR%"
echo OUT_DIR:    "%OUT_DIR%"
if "%SRC_DIR%"=="" (
    echo SRC_DIR argument not passed to script
    echo aborting compilation
    exit /b 1
)
if "%OUT_DIR%"=="" (
    echo OUT_DIR argument not passed to script
    echo aborting compilation
    exit /b 1
)

REM validate SRC_DIR exist
if not exist "%SRC_DIR%" (
    echo SRC_DIR does not exist %SRC_DIR%
    echo aborting compilation
    exit /b 1
)
REM create OUT_DIR of not present
if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

REM glslc
set "GLSLC_PATH=%VULKAN_SDK%\bin\glslc.exe"
echo GLSLC_PATH: "%GLSLC_PATH%"

REM validate glslc is present in GLSLC_PATH
if not exist "%GLSLC_PATH%" (
    echo glslc not found in %GLSLC_PATH%
    echo aborting compilation
    exit /b 1
)

REM compile shaders in SRC_DIR and place them in OUT_DIR
for /R "%SRC_DIR%" %%F in (*.vert *.frag *.comp) do (
    REM Extract relative path
    set "CURRENT_DIR=%%~dpF"
    set "FILE_NAME=%%~nxF"
    set "CURRENT_PATH=!CURRENT_DIR!!FILE_NAME!
    set "RELATIVE_PATH=!CURRENT_PATH:%SRC_DIR%=!"
    set "OUT_PATH=!OUT_DIR!!RELATIVE_PATH!.spv
    echo CURRENT_DIR:           !CURRENT_DIR!
    echo FILE_NAME:             !FILE_NAME!
    echo CURRENT_PATH:          !CURRENT_PATH!
    echo RELATIVE_PATH:         !RELATIVE_PATH!
    echo OUT_PATH:              !OUT_PATH!

    REM create intermidiary directories (glslc does not create intermidiary directories)
    for %%D in ("!OUT_PATH!") do set "DIRECTORIES_TO_CREATE=%%~dpD"
    echo DIRECTORIES_TO_CREATE: !DIRECTORIES_TO_CREATE!
    if not exist "!DIRECTORIES_TO_CREATE!" mkdir "!DIRECTORIES_TO_CREATE!"


    REM Replace backslashes with underscores for output filename
    set "OUT_FILE=!OUT_DIR!\%%~nxF.spv"

    echo Compiling %%F to !OUT_PATH!
    "%GLSLC_PATH%" "%%F" -o "!OUT_PATH!"
    
    if ERRORLEVEL 1 (
        echo ERROR: Failed to compile %%F
        REM exit /b 1
    )
)

endlocal
exit /b 0
