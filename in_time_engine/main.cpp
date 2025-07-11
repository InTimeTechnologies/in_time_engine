// Dependencies | std
#include <iostream>
#include <filesystem>
#include <limits.h>
#include <chrono>
#include <thread>

// Dependencies | Operating System
#if defined(_LINUX)
// Dependencies | Linux
#include <unistd.h>
#elif defined(_WIN64)
// Dependencies | Windows
#include <windows.h>
#endif

// Functions | Operating System
#if defined(_LINUX)
std::filesystem::path getExecutablePath() {
    char path[PATH_MAX];
    ssize_t pathLength = readlink("/proc/self/exe", path, sizeof(path) - 1);
    std::filesystem::path executablePath = std::filesystem::path();

    if (pathLength <= 0) return executablePath;

    path[pathLength] = '\0';
    executablePath = std::filesystem::path(std::string(path));

    return executablePath;
}
#elif defined(_WIN64)
std::filesystem::path getExecutablePath() {
    wchar_t buffer[MAX_PATH];
    DWORD length = GetModuleFileNameW(nullptr, buffer, MAX_PATH);

    if (length == 0 || length == MAX_PATH) {
        // Handle error or truncation
        throw std::runtime_error("Failed to get executable path");
    }

    return std::filesystem::path(buffer);
}
#endif

// Dependencies | src
#include "in_time_engine/InTimeEngine.h"

// Dependencies | test
#include "Test.h"

int main(int argc, char* argv[]) {
    std::cout << "Program operating" << std::endl;

    // Retrieve executable path
    std::filesystem::path executablePath = getExecutablePath();
    std::cout << "OS generated path: " << executablePath << std::endl;

    // GLFW engine
    glfw::GLFWEngine glfwEngine = glfw::GLFWEngine();
    glfw::WindowWrapper windowWrapper = glfw::WindowWrapper(500, 500, "Game", nullptr);

    // GL engine
    std::filesystem::path rootPathToShaders = std::filesystem::path(executablePath.parent_path() / "shader_src");
    #if defined(_DEBUG)
    rootPathToShaders = executablePath.parent_path().parent_path().parent_path() / "in_time_engine" / "shader_src";
    #endif
    gl::GLEngine openGLEngine = gl::GLEngine(rootPathToShaders);

    // UI engine
    it::UIEngine uiEngine = it::UIEngine(windowWrapper.getWindow());

    // In Time Engine
    it::InTimeEngine inTimeEngine = it::InTimeEngine(executablePath);

    // Test
    test::Test test = test::Test();
    test.test();

    // Run engine
    inTimeEngine.run();
    
    //for (size_t i = 0ULL; i < 100ULL; i++) {
    //    if (inTimeEngine.getShouldStop())
    //        break;
    //    inTimeEngine.step();
    //    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    //}

    // End of program
    std::cout << "Program terminating" << std::endl;
    return 0;
}
