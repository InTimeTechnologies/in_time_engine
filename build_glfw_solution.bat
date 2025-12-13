cd dependencies\glfw
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64 -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF