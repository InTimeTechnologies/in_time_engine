#pragma once

// Dependencies | in_time_editor
#include "HierarchyUI.h"
#include "InspectorUI.h"
#include "EngineTimeUI.h"
#include "GameObjectUI.h"

namespace it {
	// Forward declarations
	class InTimeEngine;

	class InTimeEditor {
		// Object
		public:
			// Properties | In Time Editor
			InTimeEngine inTimeEngine{};
			glfw::Window* window{ nullptr };
			ImGuiContext* imGuiContext{ nullptr };
			HierarchyUI hierarchy{};
			InspectorUI inspector{};
			EngineTimeUI engineTime{};
			GameObjectUI gameObjectUI{};

			bool shouldClose{ false };
			bool shouldReset{ false };

			// Constructor / Destructor
			InTimeEditor();
			~InTimeEditor();

			// Functions
			void update();
			void run();
			void step();
	};
}
