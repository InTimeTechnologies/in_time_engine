![logo_animated](/doc/images/in_time_engine_400x400.gif)

# In Time Engine
In Time Engine is a fully custom C/C++ 3D / 2D  game engine. It delivers ease of use, fast performance and full customizability. It is structured to follow a strict flow of events. You can interface to this events to build the applications and games you like through event and component classes.

In TimeEngine does not have a license to the public yet but might transition to MIT license in the future.

This is the only place where you can get a copy of In Time Engine.

Documentation will be released as the engine matures given some features rapidly change in early development In the meantime, documentation is provided through .text files with the word doc on them or through comments.

In Time Engine is the work of a single developer (the author), but will be opened to the open source community for input, contributions, requests and collaboration.

# Submodules
- GLM
- Box2D
- GLFW
- Dear ImGui
- JSON by Nlohmann
- STB
- Termcolor

# Other Dependencies
- GLEW (GitHub repo is broken / missing 3 .c files as of December 13, 2025. It is downloaded as a .zip and extracted through s batch script on build.)

# Building Submodules and Dependencies
in_time_engine.vcxproj is configured through property_sheets\build_event_properties.props to call vs_scripts\build_dependencies.bat to build the dependencies using the specified configuration. It uses build stamps to avoid rebuilding dependencies.

Alternatively, you can call vs_scripts\build_dependencies\build_all.bat without any arguments. It will build all Debug and Release versions of all dependencies. It will also skip rebuilding dependencies when you are building in_time_engine through build stamp files in vs_scripts\build_dependencies\build_stamps.

Shall there be any issues, you can call vs_scripts\build_dependencies\clean_all.bat to remove build stamps and install folders for all depdencies.

There are other individual scripts you can use. Refer to their respective documentation inside [vs_scripts\build_dependencies](vs_scripts\build_dependencies) directory on how to use them.

# Building
```
git clone https://github.com/InTimeTechnologies/in_time_engine.git
cd in_time_engine
git submodule update --init --recursive
```
Open in_time_engine.sln and build solution in Debug or Release, x64.

# Funding
There are multiple avenues you can support In Time Engine development. Refer to the [funding](funding) page for different options.

