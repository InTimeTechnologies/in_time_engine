#include "GLFWBackend.h"

// Dependencies | std
#include <cassert>

// Dependencies | glfw
#include <GLFW/glfw3.h>

// Dependencies | in_time_engine | input
#include <in_time_engine/input/mouse_keyboard/MouseKeyboardInput.h>
#include <in_time_engine/input/joystick/JoystickInput.h>

namespace it {
	GLFWwindow* toGLFWWindow(void* backendObjectHandle) {
		assert(backendObjectHandle != nullptr && "backendObjecthandle == nullptr");
		return reinterpret_cast<GLFWwindow*>(backendObjectHandle);
	}

	// class GLFWBackend

	// Static | private

	// Properties
	GLFWBackend* GLFWBackend::s_singleton{ nullptr };

	// Static | public

	// Getters
	GLFWBackend* GLFWBackend::s_getSingleton() {
		return s_singleton;
	}

	// Functions
	KeyCode GLFWBackend::s_ToKeyCode(int glfwKey) {
		switch (glfwKey) {
			case GLFW_KEY_SPACE:         return KeyCode::SPACE;
			case GLFW_KEY_APOSTROPHE:    return KeyCode::APOSTROPHE;
			case GLFW_KEY_COMMA:         return KeyCode::COMMA;
			case GLFW_KEY_MINUS:         return KeyCode::MINUS;
			case GLFW_KEY_PERIOD:        return KeyCode::PERIOD;
			case GLFW_KEY_SLASH:         return KeyCode::SLASH;
			case GLFW_KEY_0:             return KeyCode::ALPHA_0;
			case GLFW_KEY_1:             return KeyCode::ALPHA_1;
			case GLFW_KEY_2:             return KeyCode::ALPHA_2;
			case GLFW_KEY_3:             return KeyCode::ALPHA_3;
			case GLFW_KEY_4:             return KeyCode::ALPHA_4;
			case GLFW_KEY_5:             return KeyCode::ALPHA_5;
			case GLFW_KEY_6:             return KeyCode::ALPHA_6;
			case GLFW_KEY_7:             return KeyCode::ALPHA_7;
			case GLFW_KEY_8:             return KeyCode::ALPHA_8;
			case GLFW_KEY_9:             return KeyCode::ALPHA_9;
			case GLFW_KEY_SEMICOLON:     return KeyCode::SEMICOLON;
			case GLFW_KEY_EQUAL:         return KeyCode::EQUAL;
			case GLFW_KEY_A:             return KeyCode::A;
			case GLFW_KEY_B:             return KeyCode::B;
			case GLFW_KEY_C:             return KeyCode::C;
			case GLFW_KEY_D:             return KeyCode::D;
			case GLFW_KEY_E:             return KeyCode::E;
			case GLFW_KEY_F:             return KeyCode::F;
			case GLFW_KEY_G:             return KeyCode::G;
			case GLFW_KEY_H:             return KeyCode::H;
			case GLFW_KEY_I:             return KeyCode::I;
			case GLFW_KEY_J:             return KeyCode::J;
			case GLFW_KEY_K:             return KeyCode::K;
			case GLFW_KEY_L:             return KeyCode::L;
			case GLFW_KEY_M:             return KeyCode::M;
			case GLFW_KEY_N:             return KeyCode::N;
			case GLFW_KEY_O:             return KeyCode::O;
			case GLFW_KEY_P:             return KeyCode::P;
			case GLFW_KEY_Q:             return KeyCode::Q;
			case GLFW_KEY_R:             return KeyCode::R;
			case GLFW_KEY_S:             return KeyCode::S;
			case GLFW_KEY_T:             return KeyCode::T;
			case GLFW_KEY_U:             return KeyCode::U;
			case GLFW_KEY_V:             return KeyCode::V;
			case GLFW_KEY_W:             return KeyCode::W;
			case GLFW_KEY_X:             return KeyCode::X;
			case GLFW_KEY_Y:             return KeyCode::Y;
			case GLFW_KEY_Z:             return KeyCode::Z;
			case GLFW_KEY_LEFT_BRACKET:  return KeyCode::LEFT_BRACKET;
			case GLFW_KEY_BACKSLASH:     return KeyCode::BACKSLASH;
			case GLFW_KEY_RIGHT_BRACKET: return KeyCode::RIGHT_BRACKET;
			case GLFW_KEY_GRAVE_ACCENT:  return KeyCode::GRAVE_ACCENT;
			case GLFW_KEY_WORLD_1:       return KeyCode::WORLD_1;
			case GLFW_KEY_WORLD_2:       return KeyCode::WORLD_2;
			case GLFW_KEY_ESCAPE:        return KeyCode::ESCAPE;
			case GLFW_KEY_ENTER:         return KeyCode::ENTER;
			case GLFW_KEY_TAB:           return KeyCode::TAB;
			case GLFW_KEY_BACKSPACE:     return KeyCode::BACKSPACE;
			case GLFW_KEY_INSERT:        return KeyCode::INSERT;
			case GLFW_KEY_DELETE:        return KeyCode::DELETE;
			case GLFW_KEY_RIGHT:         return KeyCode::RIGHT_ARROW;
			case GLFW_KEY_LEFT:          return KeyCode::LEFT_ARROW;
			case GLFW_KEY_DOWN:          return KeyCode::DOWN_ARROW;
			case GLFW_KEY_UP:            return KeyCode::UP_ARROW;
			case GLFW_KEY_PAGE_UP:       return KeyCode::PAGE_UP;
			case GLFW_KEY_PAGE_DOWN:     return KeyCode::PAGE_DOWN;
			case GLFW_KEY_HOME:          return KeyCode::HOME;
			case GLFW_KEY_END:           return KeyCode::END;
			case GLFW_KEY_CAPS_LOCK:     return KeyCode::CAPS_LOCK;
			case GLFW_KEY_SCROLL_LOCK:   return KeyCode::SCROLL_LOCK;
			case GLFW_KEY_NUM_LOCK:      return KeyCode::NUM_LOCK;
			case GLFW_KEY_PRINT_SCREEN:  return KeyCode::PRINT_SCREEN;
			case GLFW_KEY_PAUSE:         return KeyCode::PAUSE;
			case GLFW_KEY_F1:            return KeyCode::F1;
			case GLFW_KEY_F2:            return KeyCode::F2;
			case GLFW_KEY_F3:            return KeyCode::F3;
			case GLFW_KEY_F4:            return KeyCode::F4;
			case GLFW_KEY_F5:            return KeyCode::F5;
			case GLFW_KEY_F6:            return KeyCode::F6;
			case GLFW_KEY_F7:            return KeyCode::F7;
			case GLFW_KEY_F8:            return KeyCode::F8;
			case GLFW_KEY_F9:            return KeyCode::F9;
			case GLFW_KEY_F10:           return KeyCode::F10;
			case GLFW_KEY_F11:           return KeyCode::F11;
			case GLFW_KEY_F12:           return KeyCode::F12;
			case GLFW_KEY_F13:           return KeyCode::F13;
			case GLFW_KEY_F14:           return KeyCode::F14;
			case GLFW_KEY_F15:           return KeyCode::F15;
			case GLFW_KEY_F16:           return KeyCode::F16;
			case GLFW_KEY_F17:           return KeyCode::F17;
			case GLFW_KEY_F18:           return KeyCode::F18;
			case GLFW_KEY_F19:           return KeyCode::F19;
			case GLFW_KEY_F20:           return KeyCode::F20;
			case GLFW_KEY_F21:           return KeyCode::F21;
			case GLFW_KEY_F22:           return KeyCode::F22;
			case GLFW_KEY_F23:           return KeyCode::F23;
			case GLFW_KEY_F24:           return KeyCode::F24;
			case GLFW_KEY_F25:           return KeyCode::F25;
			case GLFW_KEY_KP_0:          return KeyCode::NUMPAD_0;
			case GLFW_KEY_KP_1:          return KeyCode::NUMPAD_1;
			case GLFW_KEY_KP_2:          return KeyCode::NUMPAD_2;
			case GLFW_KEY_KP_3:          return KeyCode::NUMPAD_3;
			case GLFW_KEY_KP_4:          return KeyCode::NUMPAD_4;
			case GLFW_KEY_KP_5:          return KeyCode::NUMPAD_5;
			case GLFW_KEY_KP_6:          return KeyCode::NUMPAD_6;
			case GLFW_KEY_KP_7:          return KeyCode::NUMPAD_7;
			case GLFW_KEY_KP_8:          return KeyCode::NUMPAD_8;
			case GLFW_KEY_KP_9:          return KeyCode::NUMPAD_9;
			case GLFW_KEY_KP_DECIMAL:    return KeyCode::NUMPAD_DECIMAL;
			case GLFW_KEY_KP_DIVIDE:     return KeyCode::NUMPAD_DIVIDE;
			case GLFW_KEY_KP_MULTIPLY:   return KeyCode::NUMPAD_MULTIPLY;
			case GLFW_KEY_KP_SUBTRACT:   return KeyCode::NUMPAD_SUBTRACT;
			case GLFW_KEY_KP_ADD:        return KeyCode::NUMPAD_ADD;
			case GLFW_KEY_KP_ENTER:      return KeyCode::NUMPAD_ENTER;
			case GLFW_KEY_KP_EQUAL:      return KeyCode::NUMPAD_EQUAL;
			case GLFW_KEY_LEFT_SHIFT:    return KeyCode::LEFT_SHIFT;
			case GLFW_KEY_LEFT_CONTROL:  return KeyCode::LEFT_CONTROL;
			case GLFW_KEY_LEFT_ALT:      return KeyCode::LEFT_ALT;
			case GLFW_KEY_LEFT_SUPER:    return KeyCode::LEFT_SUPER;
			case GLFW_KEY_RIGHT_SHIFT:   return KeyCode::RIGHT_SHIFT;
			case GLFW_KEY_RIGHT_CONTROL: return KeyCode::RIGHT_CONTROL;
			case GLFW_KEY_RIGHT_ALT:     return KeyCode::RIGHT_ALT;
			case GLFW_KEY_RIGHT_SUPER:   return KeyCode::RIGHT_SUPER;
			case GLFW_KEY_MENU:          return KeyCode::MENU;
			case GLFW_KEY_UNKNOWN:       return KeyCode::UNKNOWN;
			default:                     return KeyCode::UNKNOWN;
		}
	}
	Key::Action GLFWBackend::s_ToKeyAction(int glfwAction) {
		switch (glfwAction) {
			case GLFW_PRESS:   return Key::Action::PRESSED;
			case GLFW_REPEAT:  return Key::Action::REPEAT;
			case GLFW_RELEASE: return Key::Action::RELEASED;
			default:           return Key::Action::UNKNOWN;
		}
	}
	MouseButtonCode GLFWBackend::s_toMouseButtonCode(int glfwMouseButton) {
		switch (glfwMouseButton) {
			case GLFW_MOUSE_BUTTON_1: return MouseButtonCode::BUTTON_CODE_1;
			case GLFW_MOUSE_BUTTON_2: return MouseButtonCode::BUTTON_CODE_2;
			case GLFW_MOUSE_BUTTON_3: return MouseButtonCode::BUTTON_CODE_3;
			case GLFW_MOUSE_BUTTON_4: return MouseButtonCode::BUTTON_CODE_4;
			case GLFW_MOUSE_BUTTON_5: return MouseButtonCode::BUTTON_CODE_5;
			case GLFW_MOUSE_BUTTON_6: return MouseButtonCode::BUTTON_CODE_6;
			case GLFW_MOUSE_BUTTON_7: return MouseButtonCode::BUTTON_CODE_7;
			case GLFW_MOUSE_BUTTON_8: return MouseButtonCode::BUTTON_CODE_8;
			default:                  return MouseButtonCode::UNKNOWN;
		}
	}
	MouseButton::Action GLFWBackend::s_toMouseButtonAction(int glfwAction) {
		switch (glfwAction) {
			case GLFW_PRESS:
				return MouseButton::Action::PRESSED;
			case GLFW_RELEASE:
				return MouseButton::Action::RELEASED;
			default:
				return MouseButton::Action::UNKNOWN;
		};
	}

	// Callbacks
	void GLFWBackend::s_keyCallback(GLFWwindow* glfwWindow, int glfwKey, int glfwScanCode, int glfwAction, int glfwMods) {
		assert(GLFWBackend::s_singleton != nullptr && "GLFWBackend::s_singleton is nullptr");
		if (s_singleton == nullptr)
			return;

		MouseKeyboardInput* mouseKeyboardInput = s_singleton->mouseKeyboardInput;
		if (mouseKeyboardInput == nullptr)
			return;

		KeyCode keyCode = s_ToKeyCode(glfwKey);
		Key::Action keyAction = s_ToKeyAction(glfwAction);
		mouseKeyboardInput->feedAction(keyCode, keyAction);
	}
	void GLFWBackend::s_mouseButtonCallback(GLFWwindow* glfwWindow, int glfwMouseButton, int glfwAction, int glfwMods) {
		assert(GLFWBackend::s_singleton != nullptr && "GLFWBackend::s_singleton is nullptr");
		if (s_singleton == nullptr)
			return;

		MouseKeyboardInput* mouseKeyboardInput = s_singleton->mouseKeyboardInput;
		if (mouseKeyboardInput == nullptr)
			return;

		MouseButtonCode mouseButtonCode = s_toMouseButtonCode(glfwMouseButton);
		MouseButton::Action mouseButtonAction = s_toMouseButtonAction(glfwAction);
		mouseKeyboardInput->feedAction(mouseButtonCode, mouseButtonAction);
	}

	// Object | public

	// Constructor / Destructor
	GLFWBackend::GLFWBackend() {
		assert(s_singleton == nullptr && "s_singleton already exists.");
		if (s_singleton == nullptr)
			s_singleton = this;
	}
	GLFWBackend::~GLFWBackend() {
		deinit();
	}

	// Functions
	bool GLFWBackend::init() {
		// Init
		int initiationSuccess = glfwInit();
		assert(initiationSuccess && "glfw failed to initialize.");
		if (!initiationSuccess)
			return false;
	}
	bool GLFWBackend::deinit() {
		if (this != s_singleton)
			return false;
		glfwTerminate();
	}
	bool GLFWBackend::isInit() const {
		return this == s_singleton;
	}
	bool GLFWBackend::update() {
		assert(this == s_singleton && "glfw backend attempting to update is not the singleton.");
		if (this != s_singleton)
			return false;

		mouseKeyboardInput->resetTransientStates();
		joystickInput->resetTransientStates();

		glfwPollEvents(); // TODO: Update keys through callbacks
		// TODO: Update joysticks

	}

	void GLFWBackend::linkToMouseKeyboardInput(MouseKeyboardInput* mouseKeyboardInput) {
		this->mouseKeyboardInput = mouseKeyboardInput;
	}
	void GLFWBackend::linkToJoystickInput(JoystickInput* joystickInput) {
		this->joystickInput = joystickInput;
	}

	// Object | private
	//void GLFWBackend::updateJoysticks() {
	//	if (joystickInput == nullptr)
	//		return;

	//	int joystickMaxCount = 16;
	//	for (int joystickNumber = 0; joystickNumber < joystickMaxCount; joystickNumber++) {



	//		bool joystickIsConnected = glfwJoystickPresent(joystickNumber);
	//		if (!joystickIsConnected)
	//			continue;


	//		joysticks[joystickNumber].connected = joystickIsConnected;

	//		if (joystickIsConnected) {
	//			// Get button values for current controller
	//			int buttonCount = 0;
	//			const unsigned char* buttonValues = glfwGetJoystickButtons((int)joysticks[joystickNumber].code, &buttonCount);
	//			if (buttonValues == nullptr)
	//				continue;
	//			for (int buttonIndex = 0; buttonIndex <= buttonCount; buttonIndex++) {
	//				switch ((JoystickButtonCode)buttonIndex) {
	//				case JoystickButtonCode::A:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonA;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonA.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::B:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonB;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonB.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::X:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonX;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonX.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::Y:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonY;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonY.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::LEFT_BUMPER:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonLeftBumper;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonLeftBumper.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::RIGHT_BUMPER:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonRightBumper;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonRightBumper.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::BACK:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonBack;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonBack.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::START:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonStart;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonStart.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::RIGHT_THUMB:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonRightThumb;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonRightThumb.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::LEFT_THUMB:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonLeftThumb;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonLeftThumb.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::DPAD_UP:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonDpadUp;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonDpadUp.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::DPAD_RIGHT:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonDpadRight;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonDpadRight.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::DPAD_DOWN:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonDpadDown;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonDpadDown.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				case JoystickButtonCode::DPAD_LEFT:
	//				{
	//					JoystickButton& joystickButton = joysticks[joystickNumber].buttonDpadLeft;
	//					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
	//					if (pressed && !joystickButton.pressed)
	//						joystickButton.justPressed = true;
	//					else if (!pressed && joysticks[joystickNumber].buttonDpadLeft.pressed)
	//						joystickButton.justReleased = true;
	//					joystickButton.pressed = pressed;
	//				}
	//				break;
	//				default:
	//					break;
	//				}
	//			}

	//			// Get the thumb axis values for current controller
	//			int axisCount = 0;
	//			const float* axisValues = glfwGetJoystickAxes((int)joysticks[joystickNumber].code, &axisCount);
	//			for (int axisIndex = 0; axisIndex < axisCount; axisIndex++) {
	//				switch ((JoystickAxisCode)axisIndex) {
	//				case JoystickAxisCode::LEFT_X:
	//					joysticks[joystickNumber].axisLeftX.value = axisValues[axisIndex];
	//					break;
	//				case JoystickAxisCode::LEFT_Y:
	//					joysticks[joystickNumber].axisLeftY.value = axisValues[axisIndex];
	//					break;
	//				case JoystickAxisCode::RIGHT_X:
	//					joysticks[joystickNumber].axisRightX.value = axisValues[axisIndex];
	//					break;
	//				case JoystickAxisCode::RIGHT_Y:
	//					joysticks[joystickNumber].axisRightY.value = axisValues[axisIndex];
	//					break;
	//				case JoystickAxisCode::LEFT_TRIGGER:
	//					joysticks[joystickNumber].axisLeftTrigger.value = axisValues[axisIndex];
	//					break;
	//				case JoystickAxisCode::RIGHT_TRIGGER:
	//					joysticks[joystickNumber].axisRightTrigger.value = axisValues[axisIndex];
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}
}
