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
    echo aborting glew build
    exit /b 1
)
if "%CONFIGURATION%"=="" (
    echo CONFIGURATION not passed to script (Debug or Release^)
    echo aborting glew build
    exit /b 1
)
if "%PLATFORM%"=="" (
    echo PLATFORM not passed to script (x64^) (x32 not supported^)
    echo aborting glew build
    exit /b 1
)

REM check if glew library has been built in the passed configuration
set "BUILD_STAMP_PATH=%~dp0build_stamps\glew_%CONFIGURATION%_lib_built.stamp"
if exist "%BUILD_STAMP_PATH%" (
	echo aborting glew build reason: detected build stamp at: %BUILD_STAMP_PATH%
	exit /b 0
)

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

REM cd into build directory
if not exist "%PARENT_DIR%" mkdir "%PARENT_DIR%"
cd "%PARENT_DIR%"
echo Current working directory: %CD%

REM Only download and extraxt glew if glew dir (EXTRACTED_FILE_NEW_NAME) does not exist
echo checking if glew exists
if exist "%DEPENDENCY_DIR%" (
    echo Found glew dependency dir. Aborting download.
) else (
    echo Downloading GLEW to "%PARENT_DIR%\%ZIP_FILE_NAME%"
    curl -L -o "%PARENT_DIR%\%ZIP_FILE_NAME%" "%GLEW_URL%"
    echo Extracting GLEW
    powershell -Command "Expand-Archive -Force '%PARENT_DIR%\%ZIP_FILE_NAME%' '%PARENT_DIR%'"
    if exist "%EXTRACTED_FILE_NAME%" rename "%EXTRACTED_FILE_NAME%" "%EXTRACTED_FILE_NEW_NAME%"
    echo Removing "%ZIP_FILE_NAME%"
    del "%PARENT_DIR%\%ZIP_FILE_NAME%"
    echo delettion completed
)

REM build glew using msbuild
cd "%BUILD_DIR%"
msbuild glew.sln /p:Configuration="%CONFIGURATION%" /p:Platform="%PLATFORM%" /p:PlatformToolset=v143 /p:WindowsTargetPlatformVersion=10.0.22621.0
if ERRORLEVEL 1 (
    echo msbuild failed to build glew
    exit /b 1
)

REM create glew build stamp for passed configuration
type nul > "%BUILD_STAMP_PATH%"

pause
endlocal