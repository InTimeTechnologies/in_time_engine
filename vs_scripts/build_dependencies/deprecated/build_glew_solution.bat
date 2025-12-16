@echo off
setlocal

set "SOLUTION_DIR=%~1"
set "CONFIGURATION=%~2"
set "PLATFORM=%~3"

SET "DEPENDENCY_DIR=%SOLUTION_DIR%dependencies"
set "GLEW_DEPENDENCY_DIR=%DEPENDENCY_DIR%\glew"
set "BUILD_DIR=%GLEW_DEPENDENCY_DIR%\build\vc15"
set "GLEW_URL=https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip"
set "ZIP_FILE_NAME=glew.zip"
set "EXTRACTED_FILE_NAME=glew-2.2.0"
set "EXTRACTED_FILE_NEW_NAME=glew"

if not exist "%DEPENDENCY_DIR%" mkdir "%DEPENDENCY_DIR%"
cd "%DEPENDENCY_DIR%"

REM Only download and extraxt glew if glew dir (EXTRACTED_FILE_NEW_NAME) does not exist
echo checking if glew exists
if exist "%DEPENDENCY_DIR%"\glew (
    echo Found glew dependency dir. Aborting download.
) else (
    echo Downloading GLEW to "%DEPENDENCY_DIR%\%ZIP_FILE_NAME%"
    curl -L -o "%DEPENDENCY_DIR%\%ZIP_FILE_NAME%" "%GLEW_URL%"
    echo Extracting GLEW
    powershell -Command "Expand-Archive -Force '%DEPENDENCY_DIR%\%ZIP_FILE_NAME%' '%DEPENDENCY_DIR%'"
    if exist "%EXTRACTED_FILE_NAME%" rename "%EXTRACTED_FILE_NAME%" "%EXTRACTED_FILE_NEW_NAME%"
    echo Removing "%ZIP_FILE_NAME%"
    del "%DEPENDENCY_DIR%\%ZIP_FILE_NAME%"
)

echo "%BUILD_DIR%"
cd "%BUILD_DIR%"

msbuild glew.sln /p:Configuration="%CONFIGURATION%" /p:Platform="%PLATFORM%" /p:PlatformToolset=v143 /p:WindowsTargetPlatformVersion=10.0.22621.0

pause
endlocal