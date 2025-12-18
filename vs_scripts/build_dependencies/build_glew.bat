setlocal
@echo off

echo running build_glew_dependency.bat

REM arguments
set "DEPENDENCY_DIR=%~1"
set "CONFIGURATION=%~2"
set "PLATFORM=%~3"
echo dependency directory: "%DEPENDENCY_DIR%"
echo configuration:        "%CONFIGURATION%"
echo platform:             "%PLATFORM%"
if "%DEPENDENCY_DIR%"=="" (
    echo DEPENDENCY_DIR not passed to script (directory to glew root^)
    echo aborting build_glew.bat
    exit /b 1
)
if "%CONFIGURATION%"=="" (
    echo CONFIGURATION not passed to script (Debug or Release^)
    echo aborting build_glew.bat
    exit /b 1
)
if "%PLATFORM%"=="" (
    echo PLATFORM not passed to script (x64^) (x32 not supported^)
    echo aborting build_glew.bat
    exit /b 1
)

REM check if glew build stamp exist
set "BUILD_STAMP_DIR=%~dp0build_stamps"
set "BUILD_STAMP_PATH=%BUILD_STAMP_DIR%\glew_%CONFIGURATION%_lib_built.stamp"
echo BUILD_STAMP_DIR:   "%BUILD_STAMP_DIR%"
echo BUILD_STAMP_PATH: "%BUILD_STAMP_PATH%"
if exist "%BUILD_STAMP_PATH%" (
	echo skipping glew build reason: detected build stamp: %BUILD_STAMP_PATH%
	exit /b 0
)
if not exist "%BUILD_STAMP_DIR%" md "%BUILD_STAMP_DIR%"

REM directories and files
set "BUILD_DIR=%DEPENDENCY_DIR%\build\vc15"
set "GLEW_URL=https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip"
set "ZIP_FILE_NAME=glew.zip"
set "EXTRACTED_FILE_NAME=glew-2.2.0"
set "EXTRACTED_FILE_NEW_NAME=glew"
for %%I in ("%DEPENDENCY_DIR%\..") do set "PARENT_DIR=%%~fI"
echo build directory:         "%BUILD_DIR%"
echo glew url:                "%GLEW_URL%"
echo zip file name:           "%ZIP_FILE_NAME%"
echo extracted file name:     "%EXTRACTED_FILE_NAME%"
echo extracted file new name: "%EXTRACTED_FILE_NEW_NAME%"
echo parent directory:        "%PARENT_DIR%"

REM parent dir of dependency dir to download glew
if not exist "%PARENT_DIR%" mkdir "%PARENT_DIR%"
cd "%PARENT_DIR%"
echo Current working directory: %CD%

REM Only download and extraxt glew if glew dir (EXTRACTED_FILE_NEW_NAME) does not exist
echo checking if glew exists
if exist "%DEPENDENCY_DIR%" (
    echo found glew dependency in "%DEPENDENCY_DIR%"
    echo aborting download
) else (
    echo downloading GLEW to "%PARENT_DIR%\%ZIP_FILE_NAME%"
    curl -L -o "%PARENT_DIR%\%ZIP_FILE_NAME%" "%GLEW_URL%"
    echo extracting GLEW
    powershell -Command "Expand-Archive -Force '%PARENT_DIR%\%ZIP_FILE_NAME%' '%PARENT_DIR%'"
    if exist "%EXTRACTED_FILE_NAME%" rename "%EXTRACTED_FILE_NAME%" "%EXTRACTED_FILE_NEW_NAME%"
    echo removing "%ZIP_FILE_NAME%"
    del "%PARENT_DIR%\%ZIP_FILE_NAME%"
    echo delettion completed
)

REM build glew using msbuild
cd "%BUILD_DIR%"
if not defined VSINSTALLDIR (
    echo initializing Visual Studio build environment...
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
)
msbuild glew.sln /p:Configuration="%CONFIGURATION%" /p:Platform="%PLATFORM%" /p:PlatformToolset=v143 /p:WindowsTargetPlatformVersion=10.0.22621.0
if ERRORLEVEL 1 (
    echo failed to initialize Visual Studio build tools / environment. Failed to compile glew.
    echo aborting build_glew.bat
    exit /b 1
)

REM create glew build stamp for passed configuration
type nul > "%BUILD_STAMP_PATH%"

endlocal