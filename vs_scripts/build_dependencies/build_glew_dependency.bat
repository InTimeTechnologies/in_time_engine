setlocal
@echo off

echo running build_glew_dependency.bat

REM arguments
set "DEPENDENCY_DIR=%~1"
set "CONFIGURATION=%~2"
set "PLATFORM=%~3"
echo dependency directory:    "%DEPENDENCY_DIR%"
echo configuration:           "%CONFIGURATION%"
echo platform:                "%PLATFORM%"

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

cd "%BUILD_DIR%"
msbuild glew.sln /p:Configuration="%CONFIGURATION%" /p:Platform="%PLATFORM%" /p:PlatformToolset=v143 /p:WindowsTargetPlatformVersion=10.0.22621.0

pause
endlocal