#include "GLPointRenderer.h"

namespace gl {
	// class OpenGLPoint

	// Object | public

	// Constructor / Destructor
	PointRenderer::PointRenderer() {
		glGenVertexArrays(1, &vertexArrayObject);
	}
	PointRenderer::~PointRenderer() {
		glDeleteVertexArrays(1, &vertexArrayObject);
	}

	// Functions
	void PointRenderer::setup() {
		glBindVertexArray(vertexArrayObject);

		program.bind();
		program.enableAttributes();
		program.autoSetAttributeFormat();

		glBindVertexArray(0U);
	}
	Point* PointRenderer::createPoint() {
		if (vertexArrayObject == 0U || !program.isLinked())
			return nullptr;

		Point& point = pointList.emplace_back();
		point.pointNode = std::prev(pointList.end());

		return &point;
	}
	void PointRenderer::deletePoint(Point* point) {
		if (point == nullptr || point->pointNode == pointList.end())
			return;

		pointList.erase(point->pointNode);
	}
	void PointRenderer::render(const glm::mat4& viewProjectionMatrix, const Buffer& transformBuffer) {
		// Abort if there are no point instances created
		if (pointList.size() == 0ULL)
			return;

		// Resize point instance buffer if necesssary
		if (instanceBuffer.getMemorySize() != sizeof(Point::GPUData) * pointList.size())
			instanceBuffer.allocate(sizeof(Point::GPUData) * pointList.size());

		// Submit data to GPU
		long long dataSize{ sizeof(Point::GPUData) };
		long long offset{ 0LL };
		for (const Point& point : pointList) {
			instanceBuffer.subwrite(offset, dataSize, &point.gpuData);
			offset += dataSize;
		}

		// Shader storage / uniform buffer locations
		const unsigned int VERTEX_BUFFER_BINDING_POINT = 0U;
		const int VIEW_PROJECTION_MATRIX_UNIFORM_LOCATION = 0;

		// Bind buffers
		glBindVertexArray(vertexArrayObject);
		instanceBuffer.bind(Buffer::Type::VERTEX_BUFFER);
		program.setUniform(VIEW_PROJECTION_MATRIX_UNIFORM_LOCATION, 1, false, &viewProjectionMatrix);
		transformBuffer.bindBufferBase(VERTEX_BUFFER_BINDING_POINT);

		// Render
		glDrawArrays(GL_POINTS, 0, pointList.size());

		// Unbind(s)
		glBindVertexArray(0U);
	}
}
