cd ..\dependencies\glfw
if not exist build mkdir build
cd build

cmake .. -G "Visual Studio 17 2022" -A $(Platform) -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX="$(SolutionDir)install\glfw\$(ConfigurationName)"
cmake --build . --config $(ConfigurationName) --target install -- /m