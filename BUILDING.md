# Quick Start
```
git clone https://github.com/InTimeTechnologies/in_time_engine.git
cd in_time_engine
git submodule update --init --recursive
```
Open in_time_engine.sln and build solution.

For detailed instructions on dependencies, build scripts, and platform-specific notes, refer to the sections below.

# Submodules
- GLM
- Box2D
- GLFW
- Dear ImGui
- JSON by Nlohmann
- STB
- Termcolor

# Other Dependencies
- GLEW (deprecated: migrating to Vulkan)
  - Note: The GitHub repository is broken/missing three .c files as of December 13, 2025.
  - The engine downloads it as a .zip and extracts it automatically during the build via batch scripts.
- Vulkan SDK:
  - Install the Vulkan SDK at a location of your choice.
  - The project automatically finds it using the VULKAN_SDK environment variable.
  - If the variable is missing, Visual Studio will prompt you to install the Vulkan SDK.

# Building Submodules and Dependencies
[In Time Engine project](in_time_engine/in_time_engine.vcxproj) is configured through property sheet [build_event_properties.props](property_sheets/build_event_properties.props) to call [build_dependencies.bat](vs_scripts/build_dependencies/build.bat) to build each dependency. The scripts automatically create build stamp files to skip rebuilding unchanged dependencies, speeding up build times.

Alternatively, you can run [build_all](vs_scripts/build_dependencies/build_all.bat) without any arguments. It will build all Debug and Release versions of all dependencies.

All batch, build scripts used to build dependencies create build stamp files. If build stamp files in [build_stamps directory](vs_scripts/build_dependencies/build_stamps/) are used to skip rebuilding the dependency to speed up build times. You can call [clean_all.bat](vs_scripts/build_dependencies/clean_all.bat) to remove build stamps and build and install files. Each dependency has a batch script to clean build stamps and build and install files.

There are other individual scripts you can use. Refer to their respective documentation inside [vs_scripts\build_dependencies](vs_scripts/build_dependencies) directory on how to use them.

Vulkan SDK must be installed prior to building the [In Time Engine project](in_time_engine/in_time_engine.vcxproj). Refer to the requirement sections for more details. Visual Studio will prompt you to install Vulkan through their official website if the VULKAN_SDK variable is not set. It does this through [validate_vulkan_sdk_installed.bat](vs_scripts/vulkan/validate_vulkan_sdk_installed.bat) when you build it.

# Build Notes
- Build stamps: If a stamp file exists in build_stamps, the build for that dependency is skipped automatically.
- Vulkan SDK: Must be installed prior to building the solution. Visual Studio will prompt installation if the VULKAN_SDK environment variable is not set.
- MSVC / Make: Currently, MSVC is supported. Make support will be added in the future.

# Platform x86
The platform x86 is temporarily removed from [in_time_engine.vcxproj](in_time_engine/in_time_engine.vcxproj) , but the build scripts are written as if x86 was still supported. Reason: support most modern technology first.

# Tips
- Always update submodules after pulling changes:
- ```git submodule update --init --recursive```
- Use clean_all.bat if builds fail due to missing or corrupted dependencies.
- Follow the scripts’ documentation in vs_scripts/build_dependencies for dependency-specific instructions.