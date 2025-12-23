// Dependencies | std
#include <iostream>

// Dependencies | test
#include "Test.h"

// Game
#include "backend/glfw/GLFWBackend.h"

int main(int argc, char* argv[]) {
    std::cout << "Program operating" << std::endl;

    it::InTimeEngine* inTimeEngine = new it::InTimeEngine();

    it::GLFWBackend glfwBackend{};
    glfwBackend.init();
    glfwBackend.linkToMouseKeyboardInput(&inTimeEngine->mouseKeyboardInput);
    glfwBackend.linkToJoystickInput(&inTimeEngine->joystickInput);
    inTimeEngine->inputEventBackend = &glfwBackend;

    inTimeEngine->windowManager.createWindow();
    it::KeyPressPrinter keyPrinter{};

    inTimeEngine->run();

    // End of program
    std::cout << "Program terminating" << std::endl;
    return 0;
}
