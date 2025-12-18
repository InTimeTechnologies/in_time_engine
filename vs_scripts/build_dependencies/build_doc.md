# Sample commands (all)
```
.\build_all.bat
```

# Sample commands (Debug | x64):
```
.\build_dependencies.bat "D:\source\vs_repos\in_time_engine\" "Debug" "x64"
.\build_box2d_dependency.bat "D:\source\vs_repos\in_time_engine\dependencies\box2d" "Debug" "x64"
.\build_glfw_dependency.bat "D:\source\vs_repos\in_time_engine\dependencies\glfw" "Debug" "x64"
.\build_glew_dependency.bat "D:\source\vs_repos\in_time_engine\dependencies\glew" "Debug" "x64"
```

# Sample commands (Release | x64):
```
.\build_dependencies.bat "D:\source\vs_repos\in_time_engine\" "Release" "x64"
.\build_box2d_dependency.bat "D:\source\vs_repos\in_time_engine\dependencies\box2d" "Release" "x64"
.\build_glfw_dependency.bat "D:\source\vs_repos\in_time_engine\dependencies\glfw" "Release" "x64"
.\build_glew_dependency.bat "D:\source\vs_repos\in_time_engine\dependencies\glew" "Release" "x64"
```

# Notes:
- build_all.bat works when launched through cmd or double clicked.
- build_dependencies.bat requires the solution directory path to have a trailing '\'
- In Time Engine x86 intentionally unsuported
