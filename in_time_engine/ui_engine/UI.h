#pragma once

// Dependencies | std
#include <list>

// Dependencies | imgui
#include <imgui/imgui.h>

namespace it {
	class UI {
		// Friends
		friend class UIEngine;

		// Static
		private:
			// Properties
			static std::list<UI*> s_uiList;

		public:
			// Getters
			static std::list<UI*> s_getUIList();

		// Object
		private:
			// Properties
			std::list<UI*>::iterator node;

		public:
			// Properties
			void* windowTarget = nullptr;
			bool renderable = true;

			// Constructor / Destructor
			UI();
			virtual ~UI();

			// Functions
			virtual void render();
	};
}
