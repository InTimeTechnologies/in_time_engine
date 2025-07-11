/******************************************************************************
 * Copyright (c) 2024 Christopher Barrios Agosto. All Rights Reserved.
 *
 * Licensing Information:
 *  This software and associated documentation files (the "Software") may not
 *  be used, copied, modified, merged, published, distributed, sublicensed,
 *  or sold without the prior written permission of the copyright owner.
 *
 *  Unauthorized use of this file, via any medium, is strictly prohibited.
 *****************************************************************************/

/******************************************************************************
 * Project: In Time Engine
 * File: Joystick.h
 * Author: Christopher Barrios Agosto
 * Created on: 29DEC2024
 *
 * Description:
 *  Sructure that represent the state of each keyboard key and mouse button:
 *   - pressed
 *   - just pressed
 *   - just released
 *****************************************************************************/

#include "Input.h"

// class Input

// Object | public

// Constructor / Destructor
glfw::Input::Input() {
	// Register all the keys
	int i = 0;
	keys[i++] = Key(KeyCode::UNKNOWN, "unknown");
	keys[i++] = Key(KeyCode::SPACE, " ");
	keys[i++] = Key(KeyCode::APOSTROPHE, "\'");
	keys[i++] = Key(KeyCode::COMMA, ",");
	keys[i++] = Key(KeyCode::MINUS, "-");
	keys[i++] = Key(KeyCode::PERIOD, ".");
	keys[i++] = Key(KeyCode::SLASH, "/");
	keys[i++] = Key(KeyCode::ALPHA_0, "0");
	keys[i++] = Key(KeyCode::ALPHA_1, "1");
	keys[i++] = Key(KeyCode::ALPHA_2, "2");
	keys[i++] = Key(KeyCode::ALPHA_3, "3");
	keys[i++] = Key(KeyCode::ALPHA_4, "4");
	keys[i++] = Key(KeyCode::ALPHA_5, "5");
	keys[i++] = Key(KeyCode::ALPHA_6, "6");
	keys[i++] = Key(KeyCode::ALPHA_7, "7");
	keys[i++] = Key(KeyCode::ALPHA_8, "8");
	keys[i++] = Key(KeyCode::ALPHA_9, "9");
	keys[i++] = Key(KeyCode::SEMICOLON, ";");
	keys[i++] = Key(KeyCode::EQUAL, "=");
	keys[i++] = Key(KeyCode::A, "a");
	keys[i++] = Key(KeyCode::B, "b");
	keys[i++] = Key(KeyCode::C, "c");
	keys[i++] = Key(KeyCode::D, "d");
	keys[i++] = Key(KeyCode::E, "e");
	keys[i++] = Key(KeyCode::F, "f");
	keys[i++] = Key(KeyCode::G, "g");
	keys[i++] = Key(KeyCode::H, "h");
	keys[i++] = Key(KeyCode::I, "i");
	keys[i++] = Key(KeyCode::J, "j");
	keys[i++] = Key(KeyCode::K, "k");
	keys[i++] = Key(KeyCode::L, "l");
	keys[i++] = Key(KeyCode::M, "m");
	keys[i++] = Key(KeyCode::N, "n");
	keys[i++] = Key(KeyCode::O, "o");
	keys[i++] = Key(KeyCode::P, "p");
	keys[i++] = Key(KeyCode::Q, "q");
	keys[i++] = Key(KeyCode::R, "r");
	keys[i++] = Key(KeyCode::S, "s");
	keys[i++] = Key(KeyCode::T, "t");
	keys[i++] = Key(KeyCode::U, "u");
	keys[i++] = Key(KeyCode::V, "v");
	keys[i++] = Key(KeyCode::W, "w");
	keys[i++] = Key(KeyCode::X, "x");
	keys[i++] = Key(KeyCode::Y, "y");
	keys[i++] = Key(KeyCode::Z, "z");
	keys[i++] = Key(KeyCode::LEFT_BRACKET, "[");
	keys[i++] = Key(KeyCode::BACKSLASH, "\\");
	keys[i++] = Key(KeyCode::RIGHT_BRACKET, "]");
	keys[i++] = Key(KeyCode::GRAVE_ACCENT, "`");
	keys[i++] = Key(KeyCode::WORLD_1, "world 1");
	keys[i++] = Key(KeyCode::WORLD_2, "world 2");
	keys[i++] = Key(KeyCode::ESCAPE, "escape");
	keys[i++] = Key(KeyCode::ENTER, "\n");
	keys[i++] = Key(KeyCode::TAB, "\t");
	keys[i++] = Key(KeyCode::BACKSPACE, "\b");
	keys[i++] = Key(KeyCode::INSERT, "insert");
	keys[i++] = Key(KeyCode::_DELETE, "delete");
	keys[i++] = Key(KeyCode::RIGHT_ARROW, "right arrow");
	keys[i++] = Key(KeyCode::LEFT_ARROW, "left arrow");
	keys[i++] = Key(KeyCode::DOWN_ARROW, "down arrow");
	keys[i++] = Key(KeyCode::UP_ARROW, "up arrow");
	keys[i++] = Key(KeyCode::PAGE_UP, "page up");
	keys[i++] = Key(KeyCode::PAGE_DOWN, "page down");
	keys[i++] = Key(KeyCode::HOME, "home");
	keys[i++] = Key(KeyCode::END, "end");
	keys[i++] = Key(KeyCode::CAPS_LOCK, "caps lock");
	keys[i++] = Key(KeyCode::SCROLL_LOCK, "scroll lock");
	keys[i++] = Key(KeyCode::NUM_LOCK, "num lock");
	keys[i++] = Key(KeyCode::PRINT_SCREEN, "print screen");
	keys[i++] = Key(KeyCode::PAUSE, "pause");
	keys[i++] = Key(KeyCode::F1, "f1");
	keys[i++] = Key(KeyCode::F2, "f2");
	keys[i++] = Key(KeyCode::F3, "f3");
	keys[i++] = Key(KeyCode::F4, "f4");
	keys[i++] = Key(KeyCode::F5, "f5");
	keys[i++] = Key(KeyCode::F6, "f6");
	keys[i++] = Key(KeyCode::F7, "f7");
	keys[i++] = Key(KeyCode::F8, "f8");
	keys[i++] = Key(KeyCode::F9, "f9");
	keys[i++] = Key(KeyCode::F10, "f10");
	keys[i++] = Key(KeyCode::F11, "f11");
	keys[i++] = Key(KeyCode::F12, "f12");
	keys[i++] = Key(KeyCode::F13, "f13");
	keys[i++] = Key(KeyCode::F14, "f14");
	keys[i++] = Key(KeyCode::F15, "f15");
	keys[i++] = Key(KeyCode::F16, "f16");
	keys[i++] = Key(KeyCode::F17, "f17");
	keys[i++] = Key(KeyCode::F18, "f18");
	keys[i++] = Key(KeyCode::F19, "f19");
	keys[i++] = Key(KeyCode::F20, "f20");
	keys[i++] = Key(KeyCode::F21, "f21");
	keys[i++] = Key(KeyCode::F22, "f22");
	keys[i++] = Key(KeyCode::F23, "f23");
	keys[i++] = Key(KeyCode::F24, "f24");
	keys[i++] = Key(KeyCode::F25, "f25");
	keys[i++] = Key(KeyCode::NUMPAD_0, "numpad 0");
	keys[i++] = Key(KeyCode::NUMPAD_1, "numpad 1");
	keys[i++] = Key(KeyCode::NUMPAD_2, "numpad 2");
	keys[i++] = Key(KeyCode::NUMPAD_3, "numpad 3");
	keys[i++] = Key(KeyCode::NUMPAD_4, "numpad 4");
	keys[i++] = Key(KeyCode::NUMPAD_5, "numpad 5");
	keys[i++] = Key(KeyCode::NUMPAD_6, "numpad 6");
	keys[i++] = Key(KeyCode::NUMPAD_7, "numpad 7");
	keys[i++] = Key(KeyCode::NUMPAD_8, "numpad 8");
	keys[i++] = Key(KeyCode::NUMPAD_9, "numpad 9");
	keys[i++] = Key(KeyCode::NUMPAD_DECIMAL, "numpad .");
	keys[i++] = Key(KeyCode::NUMPAD_DIVIDE, "numpad /");
	keys[i++] = Key(KeyCode::NUMPAD_MULTIPLY, "numpad *");
	keys[i++] = Key(KeyCode::NUMPAD_SUBTRACT, "numpad -");
	keys[i++] = Key(KeyCode::NUMPAD_ADD, "numpad +");
	keys[i++] = Key(KeyCode::NUMPAD_ENTER, "numpad enter");
	keys[i++] = Key(KeyCode::NUMPAD_EQUAL, "numpad =");
	keys[i++] = Key(KeyCode::LEFT_SHIFT, "left shift");
	keys[i++] = Key(KeyCode::LEFT_CONTROL, "left control");
	keys[i++] = Key(KeyCode::LEFT_ALT, "left alt");
	keys[i++] = Key(KeyCode::LEFT_SUPER, "left super");
	keys[i++] = Key(KeyCode::RIGHT_SHIFT, "left shift");
	keys[i++] = Key(KeyCode::RIGHT_CONTROL, "right control");
	keys[i++] = Key(KeyCode::RIGHT_ALT, "right alt");
	keys[i++] = Key(KeyCode::RIGHT_SUPER, "right super");
	keys[i++] = Key(KeyCode::MENU, "menu");
}

// Functinos
void glfw::Input::reset() {
	for (Key* key : keysToReset) {
		key->justPressed = false;
		key->justReleased = false;
		key->repeat = false;
	}
	keysToReset.clear();

	for (MouseButton* mouseButton : mouseButtonsToReset) {
		mouseButton->justPressed = false;
		mouseButton->justReleased = false;
	}
	mouseButtonsToReset.clear();
}
glfw::Key glfw::Input::getKey(KeyCode keyCode) {
	// Key index
	int i = getKeyIndex(keyCode);

	// Error check
	if (i < 0)
		return Key();

	// Return key using index
	return keys[i];
}
int glfw::Input::getKeyIndex(KeyCode keyCode) {
	// Search for index associated with key in the list
	int i = 0;
	switch (keyCode) {
		case KeyCode::UNKNOWN:         i = 0;   break;
		case KeyCode::SPACE:           i = 1;   break;
		case KeyCode::APOSTROPHE:      i = 2;   break;
		case KeyCode::COMMA:           i = 3;   break;
		case KeyCode::MINUS:           i = 4;   break;
		case KeyCode::PERIOD:          i = 5;   break;
		case KeyCode::SLASH:           i = 6;   break;
		case KeyCode::ALPHA_0:         i = 7;   break;
		case KeyCode::ALPHA_1:         i = 8;   break;
		case KeyCode::ALPHA_2:         i = 9;   break;
		case KeyCode::ALPHA_3:         i = 10;  break;
		case KeyCode::ALPHA_4:         i = 11;  break;
		case KeyCode::ALPHA_5:         i = 12;  break;
		case KeyCode::ALPHA_6:         i = 13;  break;
		case KeyCode::ALPHA_7:         i = 14;  break;
		case KeyCode::ALPHA_8:         i = 15;  break;
		case KeyCode::ALPHA_9:         i = 16;  break;
		case KeyCode::SEMICOLON:       i = 17;  break;
		case KeyCode::EQUAL:           i = 18;  break;
		case KeyCode::A:               i = 19;  break;
		case KeyCode::B:               i = 20;  break;
		case KeyCode::C:               i = 21;  break;
		case KeyCode::D:               i = 22;  break;
		case KeyCode::E:               i = 23;  break;
		case KeyCode::F:               i = 24;  break;
		case KeyCode::G:               i = 25;  break;
		case KeyCode::H:               i = 26;  break;
		case KeyCode::I:               i = 27;  break;
		case KeyCode::J:               i = 28;  break;
		case KeyCode::K:               i = 29;  break;
		case KeyCode::L:               i = 30;  break;
		case KeyCode::M:               i = 31;  break;
		case KeyCode::N:               i = 32;  break;
		case KeyCode::O:               i = 33;  break;
		case KeyCode::P:               i = 34;  break;
		case KeyCode::Q:               i = 35;  break;
		case KeyCode::R:               i = 36;  break;
		case KeyCode::S:               i = 37;  break;
		case KeyCode::T:               i = 38;  break;
		case KeyCode::U:               i = 39;  break;
		case KeyCode::V:               i = 40;  break;
		case KeyCode::W:               i = 41;  break;
		case KeyCode::X:               i = 42;  break;
		case KeyCode::Y:               i = 43;  break;
		case KeyCode::Z:               i = 44;  break;
		case KeyCode::LEFT_BRACKET:    i = 45;  break;
		case KeyCode::BACKSLASH:       i = 46;  break;
		case KeyCode::RIGHT_BRACKET:   i = 47;  break;
		case KeyCode::GRAVE_ACCENT:    i = 48;  break;
		case KeyCode::WORLD_1:         i = 49;  break;
		case KeyCode::WORLD_2:         i = 50;  break;
		case KeyCode::ESCAPE:          i = 51;  break;
		case KeyCode::ENTER:           i = 52;  break;
		case KeyCode::TAB:             i = 53;  break;
		case KeyCode::BACKSPACE:       i = 54;  break;
		case KeyCode::INSERT:          i = 55;  break;
		case KeyCode::_DELETE:         i = 56;  break;
		case KeyCode::RIGHT_ARROW:     i = 57;  break;
		case KeyCode::LEFT_ARROW:      i = 58;  break;
		case KeyCode::DOWN_ARROW:      i = 59;  break;
		case KeyCode::UP_ARROW:        i = 60;  break;
		case KeyCode::PAGE_UP:         i = 61;  break;
		case KeyCode::PAGE_DOWN:       i = 62;  break;
		case KeyCode::HOME:            i = 63;  break;
		case KeyCode::END:             i = 64;  break;
		case KeyCode::CAPS_LOCK:       i = 65;  break;
		case KeyCode::SCROLL_LOCK:     i = 66;  break;
		case KeyCode::NUM_LOCK:        i = 67;  break;
		case KeyCode::PRINT_SCREEN:    i = 68;  break;
		case KeyCode::PAUSE:           i = 69;  break;
		case KeyCode::F1:              i = 70;  break;
		case KeyCode::F2:              i = 71;  break;
		case KeyCode::F3:              i = 72;  break;
		case KeyCode::F4:              i = 73;  break;
		case KeyCode::F5:              i = 74;  break;
		case KeyCode::F6:              i = 75;  break;
		case KeyCode::F7:              i = 76;  break;
		case KeyCode::F8:              i = 77;  break;
		case KeyCode::F9:              i = 78;  break;
		case KeyCode::F10:             i = 79;  break;
		case KeyCode::F11:             i = 80;  break;
		case KeyCode::F12:             i = 81;  break;
		case KeyCode::F13:             i = 82;  break;
		case KeyCode::F14:             i = 83;  break;
		case KeyCode::F15:             i = 84;  break;
		case KeyCode::F16:             i = 85;  break;
		case KeyCode::F17:             i = 86;  break;
		case KeyCode::F18:             i = 87;  break;
		case KeyCode::F19:             i = 88;  break;
		case KeyCode::F20:             i = 89;  break;
		case KeyCode::F21:             i = 90;  break;
		case KeyCode::F22:             i = 91;  break;
		case KeyCode::F23:             i = 92;  break;
		case KeyCode::F24:             i = 93;  break;
		case KeyCode::F25:             i = 94;  break;
		case KeyCode::NUMPAD_0:        i = 95;  break;
		case KeyCode::NUMPAD_1:        i = 96;  break;
		case KeyCode::NUMPAD_2:        i = 97;  break;
		case KeyCode::NUMPAD_3:        i = 98;  break;
		case KeyCode::NUMPAD_4:        i = 99;  break;
		case KeyCode::NUMPAD_5:        i = 100; break;
		case KeyCode::NUMPAD_6:        i = 101; break;
		case KeyCode::NUMPAD_7:        i = 102; break;
		case KeyCode::NUMPAD_8:        i = 103; break;
		case KeyCode::NUMPAD_9:        i = 104; break;
		case KeyCode::NUMPAD_DECIMAL:  i = 105; break;
		case KeyCode::NUMPAD_DIVIDE:   i = 106; break;
		case KeyCode::NUMPAD_MULTIPLY: i = 107; break;
		case KeyCode::NUMPAD_SUBTRACT: i = 108; break;
		case KeyCode::NUMPAD_ADD:      i = 109; break;
		case KeyCode::NUMPAD_ENTER:    i = 110; break;
		case KeyCode::NUMPAD_EQUAL:    i = 111; break;
		case KeyCode::LEFT_SHIFT:      i = 112; break;
		case KeyCode::LEFT_CONTROL:    i = 113; break;
		case KeyCode::LEFT_ALT:        i = 114; break;
		case KeyCode::LEFT_SUPER:      i = 115; break;
		case KeyCode::RIGHT_SHIFT:     i = 116; break;
		case KeyCode::RIGHT_CONTROL:   i = 117; break;
		case KeyCode::RIGHT_ALT:       i = 118; break;
		case KeyCode::RIGHT_SUPER:     i = 119; break;
		case KeyCode::MENU:            i = 120; break;
		default:                           i = 0;   break;
	}

	// Return index
	return i;
}

glfw::MouseButton glfw::Input::getMouseButton(MouseButtonCode mouseButtonCode) {
	// Mouse button index
	int i = getMouseButtonIndex(mouseButtonCode);

	// Error check
	if (i < 0)
		return MouseButton();

	// Return mouse button code using index
	return mouseButtons[i];

}
int glfw::Input::getMouseButtonIndex(MouseButtonCode mouseButtonCode) {
	// To-Do: Review. Check of you can move the return i to inside the switch.
	int i = 0;

	switch (mouseButtonCode) {
		case MouseButtonCode::BUTTON_CODE_1: i = 0; break;
		case MouseButtonCode::BUTTON_CODE_2: i = 1; break;
		case MouseButtonCode::BUTTON_CODE_3: i = 2; break;
		case MouseButtonCode::BUTTON_CODE_4: i = 3; break;
		case MouseButtonCode::BUTTON_CODE_5: i = 4; break;
		case MouseButtonCode::BUTTON_CODE_6: i = 5; break;
		case MouseButtonCode::BUTTON_CODE_7: i = 6; break;
		case MouseButtonCode::BUTTON_CODE_8: i = 7; break;
		default:
			return -1;
	}
	
	return i;
}
