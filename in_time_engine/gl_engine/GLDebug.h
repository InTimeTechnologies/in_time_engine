#if defined(_DEBUG)
#pragma once

// Dependencies | glew
#include <glew/glew.h>

// Dependencies | glfw
#include <glfw/glfw3.h>

namespace gl {
	class Debug {
		public:
			// Enum
			enum class Source {
				UNKNOWN = -1,
				API = GL_DEBUG_SOURCE_API,
				WINDOW_SYSTEM = GL_DEBUG_SOURCE_WINDOW_SYSTEM,
				SHADER_COMPILER = GL_DEBUG_SOURCE_SHADER_COMPILER,
				THIRD_PARTY = GL_DEBUG_SOURCE_THIRD_PARTY,
				APPLICATION = GL_DEBUG_SOURCE_APPLICATION,
				OTHER = GL_DEBUG_SOURCE_OTHER
			};
			enum class MessageType {
				UNKNOWN = -1,
				ERROR_MESSAGE = GL_DEBUG_TYPE_ERROR,
				DEPRECATED_BEHAVIOR = GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,
				UNDEFINED_BEHAVIOR = GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,
				PORTABILITY = GL_DEBUG_TYPE_PORTABILITY,
				PERFORMANCE = GL_DEBUG_TYPE_PERFORMANCE,
				MARKER = GL_DEBUG_TYPE_MARKER,
				PUSH_GROUP = GL_DEBUG_TYPE_PUSH_GROUP,
				POP_GROUP = GL_DEBUG_TYPE_POP_GROUP,
				OTHER = GL_DEBUG_TYPE_OTHER
			};
			enum class MessageSeverity {
				UNKNOWN = -1,
				NOTIFICATION = GL_DEBUG_SEVERITY_NOTIFICATION,
				LOW = GL_DEBUG_SEVERITY_LOW,
				MEDIUM = GL_DEBUG_SEVERITY_MEDIUM,
				HIGH = GL_DEBUG_SEVERITY_HIGH
			};

		// Static
		public:
			// Properties
			bool printNotificationSeverityMessage = false;
			bool printLowSeverityMessage = true;
			bool printMediumSeverityMessage = true;
			bool printHighSeverityMessage = true;

			// Functions
			static void s_messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	};
}
#endif
