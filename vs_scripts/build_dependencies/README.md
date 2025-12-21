# Building
In Time Engine uses these scripts to build all of its dependencies. You can call them manually if you need to. However, In Time Engine calls these scripts automatically when you build the project.

## Sample Commands for Building All Dependencies
```
.\build_all.bat
.\build_all.bat "D:\source\vs_repos\in_time_engine\"
```
You can optionally pass the solution directory to the script.

## Sample commands for Building (Debug | x64) Dependencies
```
.\build.bat "D:\source\vs_repos\in_time_engine\" "Debug" "x64"
.\build_box2d_dependency.bat "D:\source\vs_repos\in_time_engine\dependencies\box2d" "Debug" "x64"
.\build_glfw_dependency.bat "D:\source\vs_repos\in_time_engine\dependencies\glfw" "Debug" "x64"
.\build_glew_dependency.bat "D:\source\vs_repos\in_time_engine\dependencies\glew" "Debug" "x64"
```
The SOLUTION_DIR must have a '\' character at the end.

## Sample commands for Building (Release | x64) Dependencies
```
.\build.bat "D:\source\vs_repos\in_time_engine\" "Release" "x64"
.\build_box2d_dependency.bat "D:\source\vs_repos\in_time_engine\dependencies\box2d" "Release" "x64"
.\build_glfw_dependency.bat "D:\source\vs_repos\in_time_engine\dependencies\glfw" "Release" "x64"
.\build_glew_dependency.bat "D:\source\vs_repos\in_time_engine\dependencies\glew" "Release" "x64"
```
The SOLUTION_DIR must have a '\' character at the end.

## Notes:
- build_all.bat works when launched through cmd or double clicked.
- build.bat requires the solution directory path to have a trailing '\'

# Cleaning

## Sample commands for Cleaning All Dependencies
```
.\clean_all.bat
.\clean_all.bat "D:\source\vs_repos\in_time_engine\"
```

## Sample commands (Debug | x64):
```
.\clean.bat "D:\source\vs_repos\in_time_engine\" "Debug" "x64"
.\clean_box2d.bat "D:\source\vs_repos\in_time_engine\dependencies\box2d" "Debug" "x64"
.\clean_glfw.bat "D:\source\vs_repos\in_time_engine\dependencies\glfw" "Debug" "x64"
.\clean_glew.bat "D:\source\vs_repos\in_time_engine\dependencies\glew" "Debug" "x64"
```

## Sample commands (Release | x64):
```
.\clean.bat "D:\source\vs_repos\in_time_engine\" "Release" "x64"
.\clean_box2d.bat "D:\source\vs_repos\in_time_engine\dependencies\box2d" "Release" "x64"
.\clean_glfw.bat "D:\source\vs_repos\in_time_engine\dependencies\glfw" "Release" "x64"
.\clean_glew.bat "D:\source\vs_repos\in_time_engine\dependencies\glew" "Release" "x64"
```

## Notes:
- clean.bat requires the solution directory path to have a trailing '\'

# Build Stamps
All build scripts create a build stamp if they succeed building their respective dependency. They live in the [build_stamps directory](build_stamps/). The existance of these files are used as a sentinel value to skip trying to rebuild the dependencies. It is recommended to use the "clean" scripts to remove any dependency and stamp file.