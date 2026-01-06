// Dependencies | std
#include <iostream>

// Dependencies | test
#include "Test.h"

// Dependencies | in_time_engine
#include "in_time_engine/EngineConfigurator.h"

int main(int argc, char* argv[]) {
    std::cout << "Program operating" << std::endl;

    it::InTimeEngine* inTimeEngine = new it::InTimeEngine();

    bool useWindowBackend = true;
    bool forwardMouseKeyboardInput = true;
    bool forwardJoystickInput = true;
    it::EngineConfigurator::s_linkEngineToGLFW(*inTimeEngine, useWindowBackend, forwardMouseKeyboardInput, forwardJoystickInput);

    it::Window* window = inTimeEngine->windowManager.createWindow();
    window->show();
    it::KeyPressPrinter keyPrinter{};

    inTimeEngine->run();

    // End of program
    std::cout << "Program terminating" << std::endl;
    return 0;
}
