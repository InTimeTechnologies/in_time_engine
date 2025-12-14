// Dependencies | std
#include <iostream>

// Dependencies | src
#include "in_time_editor/InTimeEditor.h"

// Dependencies | test
#include "Test.h"

// Game
#include "UserComponentSerializer.h"

int main(int argc, char* argv[]) {
    std::cout << "Program operating" << std::endl;

    it::InTimeEditor* inTimeEditor = new it::InTimeEditor();
    do {
        if (inTimeEditor->shouldReset) {
            delete inTimeEditor;
            inTimeEditor = new it::InTimeEditor();
        }

        test::Test test{ inTimeEditor->inTimeEngine };
        test.test();

        inTimeEditor->run();
    } while (inTimeEditor->shouldReset);

    delete inTimeEditor;
    inTimeEditor = nullptr;

    // End of program
    std::cout << "Program terminating" << std::endl;
    return 0;
}
