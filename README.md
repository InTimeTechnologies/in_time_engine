![logo_animated](/doc/images/in_time_engine_400x400.gif)

# In Time Engine
In Time Engine is a fully custom C/C++ 3D and 2D game engine designed for performance, flexibility, and ease of use. It follows a strict event-driven architecture, allowing developers to interface with events and components to build applications and games. Currently, the engine builds with MSVC, with future support for Make planned. It is designed to be platform-agnostic, with minimal OS-specific code; any future platform-specific functionality will use conditional compilation.

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
- Vulkan SDK

# Requirements
- Visual Studio 2026 installed: available at [Visual Studio 2026](https://visualstudio.microsoft.com/downloads/)
- Git installed:                available at [Git download](https://git-scm.com/install/)
- CMake installed:              available at [CMake download](https://cmake.org/download/)
- Vulkan SDK installed:         available at [Vulkan SDK](https://vulkan.lunarg.com/sdk/home)

# Quick Start
```
git clone https://github.com/InTimeTechnologies/in_time_engine.git
cd in_time_engine
git submodule update --init --recursive
```
Open in_time_engine.sln and build solution.

For more details on the build process, how dependencies are built and more, refer to the [build documentation](BUILDING.md).

# Engine Order of Events
![order_of_events_transparent_background](/doc/order_of_events/order_of_events_transparent_background.svg)

# Funding
There are multiple avenues you can support In Time Engine development. Refer to the [funding](funding) page for different options.
