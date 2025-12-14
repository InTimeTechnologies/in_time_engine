#pragma once

// Dependencies | std
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <map>

// Dependencies | gl_engine
#include "GLHeader.h"

namespace gl {
	// Forward declarations
	class Engine;

	class Debug {
		// Friends
		friend class Engine;

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
				OTHER = GL_DEBUG_TYPE_OTHER,
				OTHER_ARB = GL_DEBUG_TYPE_OTHER_ARB
			};
			enum class Severity {
				UNKNOWN = -1,

				NOTIFICATION = GL_DEBUG_SEVERITY_NOTIFICATION,
				LOW = GL_DEBUG_SEVERITY_LOW,
				MEDIUM = GL_DEBUG_SEVERITY_MEDIUM,
				HIGH = GL_DEBUG_SEVERITY_HIGH
			};
			
			// Sruct
			struct Report {
				// Properties
				Source source{ Source::UNKNOWN };
				MessageType messageType{ MessageType::UNKNOWN };
				Severity severity{ Severity::UNKNOWN };
				unsigned int id{ 0U };
				std::string message{};

				// Functions
				void print() const;
			};

		// Static
		public:
			// Functions
			static bool s_enableDebugOutput();
			static void s_disableDebugOutput();
			static bool s_unregisterCallback();
			static void s_messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

		// Object
		private:
			// Properties
			size_t capacity{ 100ULL };

		public:
			// Properties
			std::list<Report> reports{};
			bool autoPrint = true;
			std::map<Source, bool> sourceFilter{
				{ Source::API, true },
				{ Source::WINDOW_SYSTEM, true },
				{ Source::SHADER_COMPILER, true },
				{ Source::THIRD_PARTY, true },
				{ Source::APPLICATION, true },
				{ Source::OTHER, true }
			};
			std::map<MessageType, bool> messageTypeFilter{
				{ MessageType::ERROR_MESSAGE, true },
				{ MessageType::DEPRECATED_BEHAVIOR, true },
				{ MessageType::UNDEFINED_BEHAVIOR, true },
				{ MessageType::PORTABILITY, true },
				{ MessageType::PERFORMANCE, true },
				{ MessageType::MARKER, true },
				{ MessageType::PUSH_GROUP, true },
				{ MessageType::POP_GROUP, true },
				{ MessageType::OTHER, true },
				{ MessageType::OTHER_ARB, true }
			};
			std::map<Severity, bool> severityFilter{
				{ Severity::NOTIFICATION, false },
				{ Severity::LOW, true },
				{ Severity::MEDIUM, true },
				{ Severity::HIGH, true }
			};
			std::vector<unsigned int> idExclusionFilter{};
			
			// Getters
			size_t getCapacity() const;

			// Setters
			void setCapacity(size_t capacity);

			// Functions
			bool registerToCallback() const;
			void print() const;
	};
}
