setlocal
@echo off

echo running validate_vulkan_sdk_installed.bat

if defined VULKAN_SDK (
    echo VULKAN_SDK = %VULKAN_SDK%
) else (
    echo Error: VULKAN_SDK environment variable not found
    echo Vulkan SDK installer sets the environment variable automatically
    echo download Vulkan SDK from https://vulkan.lunarg.com/sdk/home
    exit /b 1
)
