#pragma once

// Dependencies | std
#include <array>
#include <forward_list>

// Dependencies | in_time_engine | input | mouse_keyboard
#include "Key.h"
#include "MouseButton.h"

namespace it {
	class MouseKeyboardInput {
		// Object
		private:
			// Properties
			std::forward_list<Key*> keysInTransientState{};
			std::forward_list<MouseButton*> mouseButtonsInTransientState{};
			std::array<Key, static_cast<size_t>(KeyCode::COUNT)> keys{};
			std::array<MouseButton, static_cast<size_t>(MouseButtonCode::COUNT)> mouseButtons{};

		public:
			// Constructor / Destructor
			MouseKeyboardInput();
			MouseKeyboardInput(const MouseKeyboardInput& other) = default;
			MouseKeyboardInput(MouseKeyboardInput&& other) noexcept = default;
			~MouseKeyboardInput() = default;

			// Operators | assignment
			MouseKeyboardInput& operator=(const MouseKeyboardInput& other) = default;
			MouseKeyboardInput& operator=(MouseKeyboardInput&& other) noexcept = default;

			// Getters
			const std::forward_list<Key*>& getKeysToReset() const;
			const std::forward_list<MouseButton*>& getMouseButtonsToReset() const;
			const std::array<Key, static_cast<size_t>(KeyCode::COUNT)>& getKeys() const;
			const std::array<MouseButton, static_cast<size_t>(MouseButtonCode::COUNT)>& getMouseButtons() const;

			const Key& getKey(KeyCode keyCode) const;
			size_t getKeyIndex(KeyCode keyCode) const;

			const MouseButton& getMouseButton(MouseButtonCode mouseButtonCode) const;
			size_t getMouseButtonIndex(MouseButtonCode mouseButtonCode) const;

			// Functions
			void feedAction(KeyCode keyCode, Key::Action action);
			void feedAction(MouseButtonCode code, MouseButton::Action action);
			void reset();
			void resetTransientStates();
			void resetAllTransientStates();

	};
}
