#include "GLDebug.h"

// Depencies | std
#include <iostream>

// Dependencies | gl_engine
#include "GLEngine.h"

namespace gl {
	// struct Report

	// Object | public

	// Functions
	void Debug::Report::print() const {
		std::string sourceString{};
		std::string messageTypeString{};
		std::string severityString{};

		switch (source) {
		case Source::API:
			sourceString = "api";
			break;
		case Source::WINDOW_SYSTEM:
			sourceString = "window system";
			break;
		case Source::SHADER_COMPILER:
			sourceString = "shader compiler";
			break;
		case Source::THIRD_PARTY:
			sourceString = "third party";
			break;
		case Source::APPLICATION:
			sourceString = "application";
			break;
		case Source::OTHER:
			sourceString = "other";
			break;
		case Source::UNKNOWN:
		default:
			sourceString = "unknown";
			break;
		}
		switch (messageType) {
		case MessageType::ERROR_MESSAGE:
			messageTypeString = "error";
			break;
		case MessageType::DEPRECATED_BEHAVIOR:
			messageTypeString = "deprecated behavior";
			break;
		case MessageType::UNDEFINED_BEHAVIOR:
			messageTypeString = "undefined behavior";
			break;
		case MessageType::PORTABILITY:
			messageTypeString = "portability";
			break;
		case MessageType::PERFORMANCE:
			messageTypeString = "performance";
			break;
		case MessageType::MARKER:
			messageTypeString = "marker";
			break;
		case MessageType::PUSH_GROUP:
			messageTypeString = "push group";
			break;
		case MessageType::POP_GROUP:
			messageTypeString = "pop group";
			break;
		case MessageType::OTHER:
			messageTypeString = "other";
			break;
		case MessageType::UNKNOWN:
		default:
			messageTypeString = "unknown";
			break;
		}
		switch (severity) {
		case Severity::NOTIFICATION:
			severityString = "notification";
			break;
		case Severity::LOW:
			severityString = "low";
			break;
		case Severity::MEDIUM:
			severityString = "medium";
			break;
		case Severity::HIGH:
			severityString = "high";
			break;
		case Severity::UNKNOWN:
		default:
			severityString = "unknown";
			break;
		}

		std::cout << "Debug report:" << "\n";
		std::cout << "\tSource: " << sourceString << "\n";
		std::cout << "\tType: " << messageTypeString << "\n";
		std::cout << "\tSeverity: " << severityString << "\n";
		std::cout << "\tID: " << id << "\n";
		std::cout << "\tMessage: " << message << std::endl;
	}

	// class Debug

	// Static | public

	// Functions
	bool Debug::s_enableDebugOutput() {
		if (GLEW_KHR_debug && glDebugMessageCallback) {
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			return true;
		}
		return false;
	}
	void Debug::s_disableDebugOutput() {
		glDisable(GL_DEBUG_OUTPUT);
		glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	}
	bool Debug::s_unregisterCallback() {
		if (GLEW_KHR_debug && glDebugMessageCallback) {
			glDebugMessageCallback(nullptr, nullptr);
			return true;
		}
		return false;
	}
	void Debug::s_messageCallback(GLenum glSource, GLenum glMessageType, GLuint glId, GLenum glSeverity, GLsizei length, const GLchar* glMessage, const void* userParam) {
		std::string debugSource;
		switch ((Source)glSource) {
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
		switch ((MessageType)glMessageType) {
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
		switch ((Severity)glSeverity) {
		case Severity::NOTIFICATION:
			debugMessageSeverity = "notification";
			break;
		case Severity::LOW:
			debugMessageSeverity = "low";
			break;
		case Severity::MEDIUM:
			debugMessageSeverity = "medium";
			break;
		case Severity::HIGH:
			debugMessageSeverity = "high";
			break;
		case Severity::UNKNOWN:
		default:
			debugMessageSeverity = "unknown";
			break;
		}

		// Divider
		Debug* debug = const_cast<Debug*>(reinterpret_cast<const Debug*>(userParam));
		if (debug == nullptr)
			return;

		Report report{
			static_cast<Source>(glSource),
			static_cast<MessageType>(glMessageType),
			static_cast<Severity>(glSeverity),
			glId,
			std::string(glMessage)
		};

		// sourceFilter
		{
			auto iterator = debug->sourceFilter.find(report.source);
			if (iterator == debug->sourceFilter.end() || iterator->second == false)
				return;
		}

		// messageTypeFilter
		{
			auto iterator = debug->messageTypeFilter.find(report.messageType);
			if (iterator == debug->messageTypeFilter.end() || iterator->second == false)
				return;
		}

		// severityFilter
		{
			auto iterator = debug->severityFilter.find(report.severity);
			if (iterator == debug->severityFilter.end() || iterator->second == false)
				return;
		}

		// idExclusionFilter
		for (size_t i = 0ULL; i < debug->idExclusionFilter.size(); i++)
			if (debug->idExclusionFilter[i] == glId)
				return;

		// Add report
		debug->reports.push_back(report);
		while (debug->reports.size() > debug->capacity)
			debug->reports.pop_back();

		// If autoprint is enable, print report
		if (debug->autoPrint)
			debug->print();
	}

	// Oject | public

	// Getters
	size_t Debug::getCapacity() const {
		return capacity;
	}

	// Setters
	void Debug::setCapacity(size_t capacity) {
		this->capacity = capacity;
		while (reports.size() > capacity)
			reports.pop_back();
	}

	// Functions
	bool Debug::registerToCallback() const {
		if (GLEW_KHR_debug && glDebugMessageCallback) {
			glDebugMessageCallback(s_messageCallback, this);
			return true;
		}
		return false;
	}
	void Debug::print() const {
		for (const Report& report : reports)
			report.print();
	}
}

