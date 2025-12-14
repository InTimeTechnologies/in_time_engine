#include "InTimeEditor.h"

// Dependencies | std
#include <thread>

// Dependencies | in_time_engine
#include <in_time_engine/InTimeEngine.h>

// Dependencies | imgui
#include <glfw/glfw3.h>
#include <GL/glew.h>
#include <imgui/imgui.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace it {
	// class InTimeEditor

	// Object | public

	// Constructor / Destructor
	InTimeEditor::InTimeEditor() {
		// Create editor gameWindow
		glfw::Window& gameWindow{ inTimeEngine.glfwEngine.windowManager.windows.front() };
		GLFWwindow* sharedContext{ gameWindow.getWindow() };
		window = new glfw::Window(800, 600, "In Time Editor", nullptr, sharedContext);
		imGuiContext = ImGui::CreateContext();
		ImGui::SetCurrentContext(imGuiContext);
		ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");

		// Optional: set up IO / configuration
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		// Set style
		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();

		// Colors
		ImVec4* colors = style.Colors;

		// Window
		colors[ImGuiCol_Text] = ImVec4(0.0f, 0.45f, 0.0f, 1.0f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
		colors[ImGuiCol_ChildBg] = ImVec4(1.0f, 0.10f, 0.10f, 1.0f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);

		// Border
		style.WindowBorderSize = 1.0f;
		colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);  // No shadow

		// Background of checkbox, radio button, plot, slider, text input
		colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.0f, 0.15f, 0.0f, 1.0f);

		// Title bar
		colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f); // Title bar
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f); // Title bar when focused
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f); // Title bar when collapsed

		// Buttons
		colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.0f, 0.15f, 0.0f, 1.0f);

		// Checkbox tick and RadioButton circle
		colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 0.35f, 0.0f, 1.0f);

		// Separators (lines between items including when you resize vertically and horizontally)
		colors[ImGuiCol_Separator] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.0f, 0.25f, 0.0f, 1.0f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.0f, 0.45f, 0.0f, 1.0f);

		// Resize grip | the little triangle in lower-right and lower-left corners of windows.
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.0f, 0.15f, 0.0f, 1.0f);  // Normal
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.0f, 0.25f, 0.0f, 1.0f);  // Hovered
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.0f, 0.45f, 0.0f, 1.0f);  // Active

		// Header
		colors[ImGuiCol_Header] = ImVec4(0.0f, 0.15f, 0.0f, 1.0f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);

		// Docking
		colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.00f, 0.15f, 0.00f, 1.0f);
		colors[ImGuiCol_TabSelected] = ImVec4(0.00f, 0.00f, 0.00f, 1.0f);
		colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.00f, 0.15f, 0.00f, 1.0f);
		colors[ImGuiCol_TabDimmed] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
		colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.00f, 0.00f, 0.00f, 1.0f);
		colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.00f, 0.15f, 0.00f, 1.0f);
		colors[ImGuiCol_DockingPreview] = ImVec4(0.00f, 0.15f, 0.00f, 1.0f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);

		glfwIconifyWindow(window->getWindow());
	}
	InTimeEditor::~InTimeEditor() {
		if (imGuiContext != nullptr) {
			ImGui::SetCurrentContext(imGuiContext);
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext(imGuiContext);
			imGuiContext = nullptr;
		}
		if (window != nullptr) {
			delete window;
			window = nullptr;
		}
	}

	// Functions
	void InTimeEditor::update() {
		// ImGui IO
		ImGuiIO& io = ImGui::GetIO();

		// New frame
		ImGui::SetCurrentContext(imGuiContext);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Create a full-screen window for docking
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::Begin("DockSpace Demo", nullptr, window_flags);
		ImGui::PopStyleVar(2);

		// Create the DockSpace
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

		// Menu bar
		bool showResetPopup = false;
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Reset")) {
					showResetPopup = true;
				}
				if (ImGui::MenuItem("Exit")) {
					shouldClose = true;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit")) {
				if (ImGui::MenuItem("Create game object")) {
					gameObjectUI.isOpen = true;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("View")) {
				if (ImGui::MenuItem("Hierarchy")) {
					hierarchy.isOpen = true;
				}
				if (ImGui::MenuItem("Inspector")) {
					inspector.isOpen = true;
				}
				if (ImGui::MenuItem("Time View")) {
					engineTime.isOpen = true;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		// Confirmation popup: Reset editor
		if (showResetPopup)
			ImGui::OpenPopup("Confirm Reset");
		if (ImGui::BeginPopupModal("Confirm Reset", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text("Are you sure you want to reset the editor?");
			ImGui::Separator();

			if (ImGui::Button("Yes", ImVec2(120, 0))) {
				shouldReset = true;
				ImGui::CloseCurrentPopup();
			}

			ImGui::SameLine();

			if (ImGui::Button("No", ImVec2(120, 0))) {
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::End();

		// Draw engine time ui
		engineTime.update(inTimeEngine);

		// Draw hierarchy
		hierarchy.update(inTimeEngine.gameObjectManager.gameObjects);

		// Draw inspector
		GameObject* selectedGameObject = hierarchy.selectedGameObject;
		if (selectedGameObject != nullptr) {
			inspector.setGameObject(selectedGameObject);
			hierarchy.selectedGameObject = nullptr;
		}
		inspector.update();

		// Exit
		if (io.KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_E)) {
			shouldClose = true;
			return;
		}

		// Draw game object ui
		bool control{ io.KeyCtrl };
		bool shift{ io.KeyShift };
		bool a{ ImGui::IsKeyPressed(ImGuiKey_A) };
		if (gameObjectUI.isOpen || (control && shift && a)) {
			gameObjectUI.isOpen = true;
			gameObjectUI.update(inTimeEngine);
		}

		// Render your UI
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update platform windows (viewport windows)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

	}
	void InTimeEditor::run() {

		// Engine references
		RealTime& realTime = inTimeEngine.realTime;
		FixedTime& fixedTime = inTimeEngine.fixedTime;
		Time& coreTime = inTimeEngine.coreTime;

		realTime.start();

		std::chrono::nanoseconds lastPhysicsTick = realTime.getRunTime();
		std::chrono::nanoseconds lastCoreTick = realTime.getRunTime();

		// Update time
		while (!inTimeEngine.getShouldStop() && !shouldClose && !shouldReset) {
			realTime.tick();

			bool physicsShouldUpdate = fixedTime.shouldTick(realTime.getRunTime() - lastPhysicsTick);
			bool coreShouldUpdate = coreTime.shouldTick(realTime.getRunTime() - lastCoreTick);

			if (physicsShouldUpdate) {
				fixedTime.tick();
				lastPhysicsTick += fixedTime.tickRate;
			}
			if (coreShouldUpdate) {
				std::chrono::nanoseconds deltaTimeSinceLastCoreUpdate = realTime.getRunTime() - lastCoreTick;
				coreTime.tick(deltaTimeSinceLastCoreUpdate);
				if (coreTime.fixed)
					lastCoreTick += coreTime.tickRate;
				else
					lastCoreTick = realTime.getRunTime();
			}

			if (!physicsShouldUpdate && !coreShouldUpdate)
				continue;

			// If core or physics requires update, update UI and input
			if (coreShouldUpdate || physicsShouldUpdate) {
				inTimeEngine.resetInput();
				inTimeEngine.processInput();

				// Init components (enable, disable, start)
				inTimeEngine.initializeLogics();
			}

			// Update physics if it requires update
			if (physicsShouldUpdate) {
				// Update physics engine
				inTimeEngine.prePhysicsUpdate();
				inTimeEngine.updatePhysics(fixedTime.getScaledDeltaTimeF());
				inTimeEngine.postPhysicsUpdate();
			}

			// Update core if it requires update
			if (coreShouldUpdate) {
				// Update core engine
				inTimeEngine.preUpdate();
				inTimeEngine.update();
				inTimeEngine.postUpdate();

				// Render
				inTimeEngine.preRender();
				inTimeEngine.render();
				inTimeEngine.postRender();
			}

			// Collect garbage
			inTimeEngine.collectGarbage();

			// Process termination
			if (inTimeEngine.shouldStop) {
				bool callbackIsSet = static_cast<bool>(inTimeEngine.onStopCallback);
				if (callbackIsSet)
					inTimeEngine.shouldStop = inTimeEngine.onStopCallback();

				if (!inTimeEngine.shouldStop)
					continue;

				inTimeEngine.gameObjectManager.destroyGameObjectsImmediately();
				break;
			}

			// Process pause
			if (inTimeEngine.shouldPause) {
				bool processed = false;
				do {
					bool callbackIsSet = static_cast<bool>(inTimeEngine.onPauseCallback);
					if (callbackIsSet)
						processed = inTimeEngine.onPauseCallback();
				} while (!processed);

				inTimeEngine.shouldPause = false;
			}

			glfwMakeContextCurrent(window->getWindow());
			glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			update();
			glfwSwapBuffers(window->getWindow());
		}

	}
	void InTimeEditor::step() {
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point nextTimeToStep = now;
		while (!inTimeEngine.getShouldStop()) {
			inTimeEngine.step();
			nextTimeToStep += inTimeEngine.fixedTime.tickRate;

			if (now < nextTimeToStep)
				std::this_thread::sleep_until(nextTimeToStep);
		}
	}
}
