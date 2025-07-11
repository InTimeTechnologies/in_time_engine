#include "GLTriangle.h"

// class OpenGLTriangle

// Static | private

// Properties
unsigned int gl::Triangle::s_vertexArrayObject = 0U;
gl::Program* gl::Triangle::s_program = nullptr;
std::list<gl::Triangle*> gl::Triangle::s_triangleList = std::list<gl::Triangle*>();
std::string gl::Triangle::s_vertexShaderFileName = "triangle\\triangle.vert";
std::string gl::Triangle::s_fragmentShaderFileName = "triangle\\triangle.frag";

// Functions
bool gl::Triangle::s_init(const std::filesystem::path& parentPathToShaders) {
	s_deinit();

	Shader vertexShader = gl::Shader(gl::ShaderType::VERTEX);
	Shader fragmentShader = gl::Shader(gl::ShaderType::FRAGMENT);

	vertexShader.loadSourceCode(parentPathToShaders / std::filesystem::path(s_vertexShaderFileName));
	fragmentShader.loadSourceCode(parentPathToShaders / std::filesystem::path(s_fragmentShaderFileName));

	vertexShader.compile();
	fragmentShader.compile();

	s_program = new Program();
	s_program->link({ &vertexShader, &fragmentShader });

	glGenVertexArrays(1, &s_vertexArrayObject);
	glBindVertexArray(s_vertexArrayObject);

	s_program->bind();
	s_program->enableAttributes();
	s_program->autoSetAttributeFormat();

	glBindVertexArray(0U);

	return s_program->isLinked();
}
void gl::Triangle::s_deinit() {
	if (s_program != nullptr) {
		delete(s_program);
		s_program = nullptr;
	}
}
void gl::Triangle::s_render(gl::Buffer* transformBuffer, glm::mat4* viewProjectionMatrix) {
	if (!s_program->isLinked() || s_triangleList.size() == 0)
		return;

	glBindVertexArray(s_vertexArrayObject);

	// Vertex binding point
	const unsigned int VERTEX_BUFFER_BINDING_POINT = 0;

	// Ready up GLSL program
	s_program->bind();
	s_program->autoSetAttributeBinding(VERTEX_BUFFER_BINDING_POINT);
	s_program->setUniform(s_program->uniforms[0].location, 1, false, viewProjectionMatrix);

	// Ready up transform buffer
	transformBuffer->bind();
	transformBuffer->bindBufferBase(s_program->ssbos[0].bindingPoint);

	for (Triangle* triangle : s_triangleList) {
		// Ready triangle buffer
		triangle->buffer.bind();
		triangle->buffer.subwrite(0, sizeof(triangle->gpuData), triangle->gpuData);
		triangle->buffer.bindVertexBuffer(VERTEX_BUFFER_BINDING_POINT, 0, sizeof(Triangle::GPUData));

		// Draw the GL_LineS
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	// Disable attributes
	glBindVertexArray(0U);
}

// Object | public

// Constructor / Destructor
gl::Triangle::Triangle() {
	s_triangleList.push_back(this);
	triangleNode = std::prev(s_triangleList.end());

	gpuData[0].position = glm::vec3(-0.5f, -0.5f, 0.0f);
	gpuData[1].position = glm::vec3(0.5f, -0.5f, 0.0f);
	gpuData[2].position = glm::vec3(0.0f, 0.5f, 0.0f);
}
gl::Triangle::~Triangle() {
	s_triangleList.erase(triangleNode);
}
