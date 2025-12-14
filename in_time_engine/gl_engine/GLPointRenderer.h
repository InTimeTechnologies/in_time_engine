#pragma once

// Dependencies | std
#include <list>

// Dependencies | gl_engine
#include "GLHeader.h"
#include "GLProgram.h"
#include "GLBuffer.h"
#include "object/GLPoint.h"

namespace gl {
	class PointRenderer {
		// Friends
		friend class Engine;

		// Object
		private:
			// Properties
			unsigned int vertexArrayObject{ 0U };
			Program program{};
			std::list<Point> pointList{};
			Buffer instanceBuffer{};

		public:
			// Constructor / Destructor
			PointRenderer();
			PointRenderer(const PointRenderer& other) = delete;
			PointRenderer(PointRenderer&& other) noexcept = delete;
			~PointRenderer();

			// Operators | assignment
			PointRenderer& operator=(const PointRenderer& other) = delete;
			PointRenderer& operator=(PointRenderer&& other) noexcept = delete;

			// Functions
			void setup();
			Point* createPoint();
			void deletePoint(Point* point);
			void render(const glm::mat4& viewProjectionMatrix, const Buffer& transformBuffer);
	};
}