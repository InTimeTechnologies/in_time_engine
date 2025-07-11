#include "UIEngine.h"

// Dependencies | in_time_engine
#include "imgui_editor/InTimeEditor.h"

// class UIEngine

// Static | private

// Properties
it::UIEngine* it::UIEngine::s_singleton = nullptr;

// Getters
it::UIEngine* it::UIEngine::s_getSingleton() {
	return s_singleton;
}

// Object | public

// Constructor / Destructor
it::UIEngine::UIEngine(GLFWwindow* window) {
    if (s_singleton == nullptr)
        s_singleton = this;

    // Dear ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Set ImGui style
    ImGui::StyleColorsDark();

    // Setup platform/renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    io.IniFilename = nullptr; // Disable automatic save/load

}
it::UIEngine::~UIEngine() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (s_singleton == this)
        s_singleton == nullptr;
}

// Functions
void it::UIEngine::render() {
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (UI* ui : UI::s_uiList) {
        if (ui->windowTarget != nullptr && ui->renderable) {
            glfwMakeContextCurrent(static_cast<GLFWwindow*>(ui->windowTarget));
            ui->render();
        }
    }

    // Editor
    it::InTimeEditor* editor = InTimeEditor::getSingleton();
    if (editor != nullptr)
        editor->update();

    // Render to render target
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
