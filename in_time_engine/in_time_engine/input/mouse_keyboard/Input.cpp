#include "Input.h"

namespace it {
	// class Input

	// Object | public

	// Constructor / Destructor
	Input::Input() {
		size_t i = 0;
		keys[i++] = Key{ KeyCode::UNKNOWN, false, false, false, false, "unknown" };
		keys[i++] = Key{ KeyCode::SPACE, false, false, false, false, " " };
		keys[i++] = Key{ KeyCode::APOSTROPHE, false, false, false, false, "\'" };
		keys[i++] = Key{ KeyCode::COMMA, false, false, false, false, "," };
		keys[i++] = Key{ KeyCode::MINUS, false, false, false, false, "-" };
		keys[i++] = Key{ KeyCode::PERIOD, false, false, false, false, "." };
		keys[i++] = Key{ KeyCode::SLASH, false, false, false, false, "/" };
		keys[i++] = Key{ KeyCode::ALPHA_0, false, false, false, false, "0" };
		keys[i++] = Key{ KeyCode::ALPHA_1, false, false, false, false, "1" };
		keys[i++] = Key{ KeyCode::ALPHA_2, false, false, false, false, "2" };
		keys[i++] = Key{ KeyCode::ALPHA_3, false, false, false, false, "3" };
		keys[i++] = Key{ KeyCode::ALPHA_4, false, false, false, false, "4" };
		keys[i++] = Key{ KeyCode::ALPHA_5, false, false, false, false, "5" };
		keys[i++] = Key{ KeyCode::ALPHA_6, false, false, false, false, "6" };
		keys[i++] = Key{ KeyCode::ALPHA_7, false, false, false, false, "7" };
		keys[i++] = Key{ KeyCode::ALPHA_8, false, false, false, false, "8" };
		keys[i++] = Key{ KeyCode::ALPHA_9, false, false, false, false, "9" };
		keys[i++] = Key{ KeyCode::SEMICOLON, false, false, false, false, ";" };
		keys[i++] = Key{ KeyCode::EQUAL, false, false, false, false, "=" };
		keys[i++] = Key{ KeyCode::A, false, false, false, false, "a" };
		keys[i++] = Key{ KeyCode::B, false, false, false, false, "b" };
		keys[i++] = Key{ KeyCode::C, false, false, false, false, "c" };
		keys[i++] = Key{ KeyCode::D, false, false, false, false, "d" };
		keys[i++] = Key{ KeyCode::E, false, false, false, false, "e" };
		keys[i++] = Key{ KeyCode::F, false, false, false, false, "f" };
		keys[i++] = Key{ KeyCode::G, false, false, false, false, "g" };
		keys[i++] = Key{ KeyCode::H, false, false, false, false, "h" };
		keys[i++] = Key{ KeyCode::I, false, false, false, false, "i" };
		keys[i++] = Key{ KeyCode::J, false, false, false, false, "j" };
		keys[i++] = Key{ KeyCode::K, false, false, false, false, "k" };
		keys[i++] = Key{ KeyCode::L, false, false, false, false, "l" };
		keys[i++] = Key{ KeyCode::M, false, false, false, false, "m" };
		keys[i++] = Key{ KeyCode::N, false, false, false, false, "n" };
		keys[i++] = Key{ KeyCode::O, false, false, false, false, "o" };
		keys[i++] = Key{ KeyCode::P, false, false, false, false, "p" };
		keys[i++] = Key{ KeyCode::Q, false, false, false, false, "q" };
		keys[i++] = Key{ KeyCode::R, false, false, false, false, "r" };
		keys[i++] = Key{ KeyCode::S, false, false, false, false, "s" };
		keys[i++] = Key{ KeyCode::T, false, false, false, false, "t" };
		keys[i++] = Key{ KeyCode::U, false, false, false, false, "u" };
		keys[i++] = Key{ KeyCode::V, false, false, false, false, "v" };
		keys[i++] = Key{ KeyCode::W, false, false, false, false, "w" };
		keys[i++] = Key{ KeyCode::X, false, false, false, false, "x" };
		keys[i++] = Key{ KeyCode::Y, false, false, false, false, "y" };
		keys[i++] = Key{ KeyCode::Z, false, false, false, false, "z" };
		keys[i++] = Key{ KeyCode::LEFT_BRACKET, false, false, false, false, "[" };
		keys[i++] = Key{ KeyCode::BACKSLASH, false, false, false, false, "\\" };
		keys[i++] = Key{ KeyCode::RIGHT_BRACKET, false, false, false, false, "]" };
		keys[i++] = Key{ KeyCode::GRAVE_ACCENT, false, false, false, false, "`" };
		keys[i++] = Key{ KeyCode::WORLD_1, false, false, false, false, "world 1" };
		keys[i++] = Key{ KeyCode::WORLD_2, false, false, false, false, "world 2" };
		keys[i++] = Key{ KeyCode::ESCAPE, false, false, false, false, "escape" };
		keys[i++] = Key{ KeyCode::ENTER, false, false, false, false, "\n" };
		keys[i++] = Key{ KeyCode::TAB, false, false, false, false, "\t" };
		keys[i++] = Key{ KeyCode::BACKSPACE, false, false, false, false, "\b" };
		keys[i++] = Key{ KeyCode::INSERT, false, false, false, false, "insert" };
		keys[i++] = Key{ KeyCode::DELETE, false, false, false, false, "delete" };
		keys[i++] = Key{ KeyCode::RIGHT_ARROW, false, false, false, false, "right arrow" };
		keys[i++] = Key{ KeyCode::LEFT_ARROW, false, false, false, false, "left arrow" };
		keys[i++] = Key{ KeyCode::DOWN_ARROW, false, false, false, false, "down arrow" };
		keys[i++] = Key{ KeyCode::UP_ARROW, false, false, false, false, "up arrow" };
		keys[i++] = Key{ KeyCode::PAGE_UP, false, false, false, false, "page up" };
		keys[i++] = Key{ KeyCode::PAGE_DOWN, false, false, false, false, "page down" };
		keys[i++] = Key{ KeyCode::HOME, false, false, false, false, "home" };
		keys[i++] = Key{ KeyCode::END, false, false, false, false, "end" };
		keys[i++] = Key{ KeyCode::CAPS_LOCK, false, false, false, false, "caps lock" };
		keys[i++] = Key{ KeyCode::SCROLL_LOCK, false, false, false, false, "scroll lock" };
		keys[i++] = Key{ KeyCode::NUM_LOCK, false, false, false, false, "num lock" };
		keys[i++] = Key{ KeyCode::PRINT_SCREEN, false, false, false, false, "print screen" };
		keys[i++] = Key{ KeyCode::PAUSE, false, false, false, false, "pause" };
		keys[i++] = Key{ KeyCode::F1, false, false, false, false, "f1" };
		keys[i++] = Key{ KeyCode::F2, false, false, false, false, "f2" };
		keys[i++] = Key{ KeyCode::F3, false, false, false, false, "f3" };
		keys[i++] = Key{ KeyCode::F4, false, false, false, false, "f4" };
		keys[i++] = Key{ KeyCode::F5, false, false, false, false, "f5" };
		keys[i++] = Key{ KeyCode::F6, false, false, false, false, "f6" };
		keys[i++] = Key{ KeyCode::F7, false, false, false, false, "f7" };
		keys[i++] = Key{ KeyCode::F8, false, false, false, false, "f8" };
		keys[i++] = Key{ KeyCode::F9, false, false, false, false, "f9" };
		keys[i++] = Key{ KeyCode::F10, false, false, false, false, "f10" };
		keys[i++] = Key{ KeyCode::F11, false, false, false, false, "f11" };
		keys[i++] = Key{ KeyCode::F12, false, false, false, false, "f12" };
		keys[i++] = Key{ KeyCode::F13, false, false, false, false, "f13" };
		keys[i++] = Key{ KeyCode::F14, false, false, false, false, "f14" };
		keys[i++] = Key{ KeyCode::F15, false, false, false, false, "f15" };
		keys[i++] = Key{ KeyCode::F16, false, false, false, false, "f16" };
		keys[i++] = Key{ KeyCode::F17, false, false, false, false, "f17" };
		keys[i++] = Key{ KeyCode::F18, false, false, false, false, "f18" };
		keys[i++] = Key{ KeyCode::F19, false, false, false, false, "f19" };
		keys[i++] = Key{ KeyCode::F20, false, false, false, false, "f20" };
		keys[i++] = Key{ KeyCode::F21, false, false, false, false, "f21" };
		keys[i++] = Key{ KeyCode::F22, false, false, false, false, "f22" };
		keys[i++] = Key{ KeyCode::F23, false, false, false, false, "f23" };
		keys[i++] = Key{ KeyCode::F24, false, false, false, false, "f24" };
		keys[i++] = Key{ KeyCode::F25, false, false, false, false, "f25" };
		keys[i++] = Key{ KeyCode::NUMPAD_0, false, false, false, false, "numpad 0" };
		keys[i++] = Key{ KeyCode::NUMPAD_1, false, false, false, false, "numpad 1" };
		keys[i++] = Key{ KeyCode::NUMPAD_2, false, false, false, false, "numpad 2" };
		keys[i++] = Key{ KeyCode::NUMPAD_3, false, false, false, false, "numpad 3" };
		keys[i++] = Key{ KeyCode::NUMPAD_4, false, false, false, false, "numpad 4" };
		keys[i++] = Key{ KeyCode::NUMPAD_5, false, false, false, false, "numpad 5" };
		keys[i++] = Key{ KeyCode::NUMPAD_6, false, false, false, false, "numpad 6" };
		keys[i++] = Key{ KeyCode::NUMPAD_7, false, false, false, false, "numpad 7" };
		keys[i++] = Key{ KeyCode::NUMPAD_8, false, false, false, false, "numpad 8" };
		keys[i++] = Key{ KeyCode::NUMPAD_9, false, false, false, false, "numpad 9" };
		keys[i++] = Key{ KeyCode::NUMPAD_DECIMAL, false, false, false, false, "numpad ." };
		keys[i++] = Key{ KeyCode::NUMPAD_DIVIDE, false, false, false, false, "numpad /" };
		keys[i++] = Key{ KeyCode::NUMPAD_MULTIPLY, false, false, false, false, "numpad *" };
		keys[i++] = Key{ KeyCode::NUMPAD_SUBTRACT, false, false, false, false, "numpad -" };
		keys[i++] = Key{ KeyCode::NUMPAD_ADD, false, false, false, false, "numpad +" };
		keys[i++] = Key{ KeyCode::NUMPAD_ENTER, false, false, false, false, "numpad enter" };
		keys[i++] = Key{ KeyCode::NUMPAD_EQUAL, false, false, false, false, "numpad =" };
		keys[i++] = Key{ KeyCode::LEFT_SHIFT, false, false, false, false, "left shift" };
		keys[i++] = Key{ KeyCode::LEFT_CONTROL, false, false, false, false, "left control" };
		keys[i++] = Key{ KeyCode::LEFT_ALT, false, false, false, false, "left alt" };
		keys[i++] = Key{ KeyCode::LEFT_SUPER, false, false, false, false, "left super" };
		keys[i++] = Key{ KeyCode::RIGHT_SHIFT, false, false, false, false, "left shift" };
		keys[i++] = Key{ KeyCode::RIGHT_CONTROL, false, false, false, false, "right control" };
		keys[i++] = Key{ KeyCode::RIGHT_ALT, false, false, false, false, "right alt" };
		keys[i++] = Key{ KeyCode::RIGHT_SUPER, false, false, false, false, "right super" };
		keys[i++] = Key{ KeyCode::MENU, false, false, false, false, "menu" };

		i = 0;
		mouseButtons[i++] = MouseButton{ MouseButtonCode::UNKNOWN, false, false, false, "unknown" };
		mouseButtons[i++] = MouseButton{ MouseButtonCode::BUTTON_CODE_1, false, false, false, "left button" };
		mouseButtons[i++] = MouseButton{ MouseButtonCode::BUTTON_CODE_2, false, false, false, "right button" };
		mouseButtons[i++] = MouseButton{ MouseButtonCode::BUTTON_CODE_3, false, false, false, "middle button" };
		mouseButtons[i++] = MouseButton{ MouseButtonCode::BUTTON_CODE_4, false, false, false, "button 4" };
		mouseButtons[i++] = MouseButton{ MouseButtonCode::BUTTON_CODE_5, false, false, false, "button 5" };
		mouseButtons[i++] = MouseButton{ MouseButtonCode::BUTTON_CODE_6, false, false, false, "button 6" };
		mouseButtons[i++] = MouseButton{ MouseButtonCode::BUTTON_CODE_7, false, false, false, "button 7" };
		mouseButtons[i++] = MouseButton{ MouseButtonCode::BUTTON_CODE_8, false, false, false, "button 8" };
	}

	// Getters
	const std::forward_list<Key*>& Input::getKeysToReset() const {
		return keysInTransientState;
	}
	const std::forward_list<MouseButton*>& Input::getMouseButtonsToReset() const {
		return mouseButtonsInTransientState;
	}
	const std::array<Key, static_cast<size_t>(KeyCode::COUNT)>& Input::getKeys() const {
		return keys;
	}
	const std::array<MouseButton, static_cast<size_t>(MouseButtonCode::COUNT)>& Input::getMouseButtons() const {
		return mouseButtons;
	}

	const Key& Input::getKey(KeyCode keyCode) const {
		size_t i = getKeyIndex(keyCode);
		return keys[i];
	}
	size_t Input::getKeyIndex(KeyCode keyCode) const {
		size_t i = static_cast<size_t>(keyCode);
		size_t count = static_cast<size_t>(KeyCode::COUNT);
		return i < count ? i : 0;
	}

	const MouseButton& Input::getMouseButton(MouseButtonCode mouseButtonCode) const {
		size_t i = getMouseButtonIndex(mouseButtonCode);
		return mouseButtons[i];
	}
	size_t Input::getMouseButtonIndex(MouseButtonCode mouseButtonCode) const {
		size_t i = static_cast<size_t>(mouseButtonCode);
		size_t count = static_cast<size_t>(MouseButtonCode::COUNT);
		return i < count ? i : count;
	}

	// Functions
	void Input::feedAction(KeyCode keyCode, Key::Action action) {
		size_t i = getKeyIndex(keyCode);

		if (!keys[i].inTransientState())
			keysInTransientState.push_front(&keys[i]);

		keys[i].feedAction(action);
	}
	void Input::feedAction(MouseButtonCode mouseButtonCode, MouseButton::Action action) {
		size_t i = getMouseButtonIndex(mouseButtonCode);

		if (!mouseButtons[i].inTransientState())
			mouseButtonsInTransientState.push_front(&mouseButtons[i]);

		mouseButtons[i].feedAction(action);
	}
	void Input::reset() {
		for (size_t i = 0; i < keys.size(); i++)
			keys[i].reset();
	}
	void Input::resetTransientStates() {
		for (Key* key : keysInTransientState)
			key->resetTransientState();
		keysInTransientState.clear();

		for (MouseButton* mouseButton : mouseButtonsInTransientState)
			mouseButton->resetTransientState();
		mouseButtonsInTransientState.clear();
	}
	void Input::resetAllTransientStates() {
		for (size_t i = 0; i < keys.size(); i++)
			keys[i].resetTransientState();
		keysInTransientState.clear();

		for (size_t i = 0; i < mouseButtons.size(); i++)
			mouseButtons[i].resetTransientState();
		mouseButtonsInTransientState.clear();
	}
}
