#pragma once

// Dependencies | std
#include <iostream>

// Dependencies | InTimeEngine
#include <in_time_engine/InTimeEngine.h>

namespace it {
	class KeyPressPrinter :  public UpdateEvent {
		// Object
		public:
			// Events
			void onPreUpdate() override {
				auto spaceKey = InTimeEngine::s_getSingleton()->mouseKeyboardInput.getKey(KeyCode::SPACE);
				if (spaceKey.justPressed)
					std::cout << "space just pressed" << std::endl;
				if (spaceKey.pressed)
					std::cout << "space pressed" << std::endl;
			}
	};
}
