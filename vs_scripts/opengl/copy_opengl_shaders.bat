setlocal
@echo off

echo running copy_opengl_shaders.bat

REM arguments
set "SOURCE=%~1"
set "TARGET=%~2"
echo source: "%SOURCE%"
echo target: "%TARGET%"

REM copy source into target
xcopy "%SOURCE%" "%TARGET%" /S /E /I /Y
REM /I — Assume destination is a directory
REM /S — Copy subdirectories (excluding empty)
REM /E — Include empty directories (important for shader trees)
REM /Y — Suppress overwrite confirmation

endlocal
