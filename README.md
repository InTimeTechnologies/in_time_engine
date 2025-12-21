![logo_animated](/doc/images/in_time_engine_400x400.gif)

# In Time Engine
In Time Engine is a fully custom C/C++ 3D / 2D  game engine. It delivers ease of use, fast performance and full customizability. It is structured to follow a strict flow of events. You can interface with these events to build the applications and games you like through event and component classes. Currently it uses MSVC as its build system, but will support Make in the future. Transitioning among operating systems should be simple since it does not use operating system specific code... yet. OS level code will be used in the future, but will use conditional compilation then.

# Submodules
- GLM
- Box2D
- GLFW
- Dear ImGui
- JSON by Nlohmann
- STB
- Termcolor

# Other Dependencies
- GLEW (deprecated: migrating to Vulkan) (GitHub repo is broken / missing 3 .c files as of December 13, 2025. It is downloaded as a .zip and extracted through s batch script on build.)
- Vulkan SDK: install Vulkan SDK to the location of your preference. The project automatically finds it through the VULKAN_SDK environment variable.

# Building Submodules and Dependencies
[In Time Engine project](in_time_engine/in_time_engine.vcxproj) is configured through property sheet [build_event_properties.props](property_sheets/build_event_properties.props) to call [build_dependencies.bat](vs_scripts/build_dependencies/build.bat) to build the dependencies using the specified solution directory, configuration and platform. It uses build stamps to avoid rebuilding dependencies.

Alternatively, you can run [build_all](vs_scripts/build_dependencies/build_all.bat) without any arguments. It will build all Debug and Release versions of all dependencies.

All batch, build scripts used to build dependencies create build stamp files. Shall this file exist in the [build_stamps directory](vs_scripts/build_dependencies/build_stamps/), it will skip rebuilding the dependency to speed up build times. Shall there be any issues, you can call [clean_all.bat](vs_scripts/build_dependencies/clean_all.bat) to remove build stamps and build and install files. There are "clean" scripts per dependency shall you need it.

There are other individual scripts you can use. Refer to their respective documentation inside [vs_scripts\build_dependencies](vs_scripts/build_dependencies) directory on how to use them.

Vulkan SDK must be installed prior to building the [In Time Engine project](in_time_engine/in_time_engine.vcxproj). Refer to the requirement sections for more details. Visual Studio will prompt you to install Vulkan through their official website shall VULKAN_SDK variable is not found through a [batch script](vs_scripts/vulkan/validate_vulkan_sdk_installed.bat) when you build it.

# Requirements
- Visual Studio 2026 installed: available at [Visual Studio 2026](https://visualstudio.microsoft.com/downloads/)
- Git installed:                available at [Git download](https://git-scm.com/install/)
- CMake installed:              available at [CMake download](https://cmake.org/download/)
- Vulkan SDK installed:         available at [Vulkan SDK](https://vulkan.lunarg.com/sdk/home)

# Building
```
git clone https://github.com/InTimeTechnologies/in_time_engine.git
cd in_time_engine
git submodule update --init --recursive
```
Open in_time_engine.sln and build solution in Debug, Release | x64. The platform x86 is deprecated on [in_time_engine.vcxproj](in_time_engine/in_time_engine.vcxproj) , but the build scripts are written as if x86 was still supported.

# Engine Order of Events

![order_of_events_transparent_background](/doc/order_of_events/order_of_events_transparent_background.svg)

# Funding
There are multiple avenues you can support In Time Engine development. Refer to the [funding](funding) page for different options.
