#include "GLPoint.h"

// Dependencies | opengl_engine
#include "../GLTransform.h"

// class OpenGLPoint

// Static | private

// Properties
unsigned int gl::Point::s_vertexArrayObject = 0U;
gl::Program* gl::Point::s_program = nullptr;
std::list<gl::Point*> gl::Point::s_pointList = std::list<gl::Point*>();
std::string gl::Point::s_vertexShaderFileName = "point\\point.vert";
std::string gl::Point::s_fragmentShaderFileName = "point\\point.frag";

// Functions
bool gl::Point::s_init(const std::filesystem::path& rootPathToShaders) {
	s_deinit();

	gl::Shader vertexShader = gl::Shader(gl::ShaderType::VERTEX);
	gl::Shader fragmentShader = gl::Shader(gl::ShaderType::FRAGMENT);

	vertexShader.loadSourceCode(rootPathToShaders / std::filesystem::path(s_vertexShaderFileName));
	fragmentShader.loadSourceCode(rootPathToShaders / std::filesystem::path(s_fragmentShaderFileName));

	vertexShader.compile();
	fragmentShader.compile();

	s_program = new gl::Program();
	s_program->link({ &vertexShader, &fragmentShader });

	glGenVertexArrays(1, &s_vertexArrayObject);
	glBindVertexArray(s_vertexArrayObject);

	s_program->bind();
	s_program->enableAttributes();
	s_program->autoSetAttributeFormat();

	glBindVertexArray(0U);

	return s_program->isLinked();
}
void gl::Point::s_deinit() {
	if (s_program != nullptr) {
		delete(s_program);
		s_program = nullptr;
	}
}
void gl::Point::s_render(gl::Buffer* transformBuffer, glm::mat4* viewProjectionMatrix) {
	if (!s_program->isLinked() || s_pointList.size() == 0)
		return;

	glBindVertexArray(s_vertexArrayObject);

	// Vertex binding point
	const unsigned int VERTEX_BUFFER_BINDING_POINT = 0;
	
	// Ready up GLSL program
	s_program->bind();
	s_program->autoSetAttributeBinding(VERTEX_BUFFER_BINDING_POINT);
	s_program->setUniform(s_program->uniforms[0].location, 1, false, viewProjectionMatrix);

	// Ready up transform buffer
	transformBuffer->bindBufferBase(s_program->ssbos[0].bindingPoint);

	for (gl::Point* point : s_pointList) {
		// Bind point buffer and update it
		point->buffer.bind();
		point->buffer.subwrite(0, sizeof(point->gpuData), &point->gpuData);
		point->buffer.bindVertexBuffer(VERTEX_BUFFER_BINDING_POINT, 0, sizeof(gl::Point::GPUData));

		// Draw the GL_POINTS
		glDrawArrays(GL_POINTS, 0, 1);
	}

	glBindVertexArray(0U);
}

// Object | public

// Constructor / Destructor
gl::Point::Point() {
	s_pointList.push_back(this);
	pointNode = std::prev(s_pointList.end());

	// To-Do: Pop an index from gl::Transform
}
gl::Point::~Point() {
	// To-Do: Push an index to gl::Transform
}
