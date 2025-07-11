#if defined(_DEBUG)
#include "GLDebug.h"

// Depencies | std
#include <iostream>

// class Debug

// Static | public

// Functions
void gl::Debug::s_messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	if (severity == (GLenum)MessageSeverity::NOTIFICATION)
		return;

	std::string debugSource;
	switch ((Source)source) {
		case Source::API:
			debugSource = "api";
			break;
		case Source::WINDOW_SYSTEM:
			debugSource = "window system";
			break;
		case Source::SHADER_COMPILER:
			debugSource = "shader compiler";
			break;
		case Source::THIRD_PARTY:
			debugSource = "third party";
			break;
		case Source::APPLICATION:
			debugSource = "application";
			break;
		case Source::OTHER:
			debugSource = "other";
			break;
		case Source::UNKNOWN:
		default:
			debugSource = "unknown";
			break;
	}

	std::string debugMessageType;
	switch ((MessageType)type) {
		case MessageType::ERROR_MESSAGE:
			debugMessageType = "error";
			break;
		case MessageType::DEPRECATED_BEHAVIOR:
			debugMessageType = "deprecated behavior";
			break;
		case MessageType::UNDEFINED_BEHAVIOR:
			debugMessageType = "undefined behavior";
			break;
		case MessageType::PORTABILITY:
			debugMessageType = "portability";
			break;
		case MessageType::PERFORMANCE:
			debugMessageType = "performance";
			break;
		case MessageType::MARKER:
			debugMessageType = "marker";
			break;
		case MessageType::PUSH_GROUP:
			debugMessageType = "push group";
			break;
		case MessageType::POP_GROUP:
			debugMessageType = "pop group";
			break;
		case MessageType::OTHER:
			debugMessageType = "other";
			break;
		case MessageType::UNKNOWN:
		default:
			debugMessageType = "unknown";
			break;
	}

	std::string debugMessageSeverity;
	switch ((MessageSeverity)severity) {
		case MessageSeverity::NOTIFICATION:
			debugMessageSeverity = "notification";
			break;
		case MessageSeverity::LOW:
			debugMessageSeverity = "low";
			break;
		case MessageSeverity::MEDIUM:
			debugMessageSeverity = "medium";
			break;
		case MessageSeverity::HIGH:
			debugMessageSeverity = "high";
			break;
		case MessageSeverity::UNKNOWN:
		default:
			debugMessageSeverity = "unknown";
			break;
	}

	size_t debugMessageLength = length;
	std::string debugMessage = std::string(message);

	std::cout << "Debug message callback report:" << "\n";
	std::cout << "\tSource: " << debugSource << "\n";
	std::cout << "\tType: " << debugMessageType << "\n";
	std::cout << "\tID: " << id << "\n";
	std::cout << "\tSeverity: " << debugMessageSeverity << "\n";
	std::cout << "\tMessage: " << debugMessage << "\n";
	std::cout << "\tUser parameter: " << userParam << "\n" << std::endl;
}
#endif
