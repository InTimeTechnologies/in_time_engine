#include "GLTriangleStrip.h"

// class OpenGLLine

// Static | private

// Properties
unsigned int gl::TriangleStrip::s_vertexArrayObject = 0U;
gl::Program* gl::TriangleStrip::s_program = nullptr;
std::list<gl::TriangleStrip*> gl::TriangleStrip::s_multiLineList = std::list<gl::TriangleStrip*>();
std::string gl::TriangleStrip::s_vertexShaderFileName = "triangle\\triangle.vert";
std::string gl::TriangleStrip::s_fragmentShaderFileName = "triangle\\triangle.frag";

// Functions
bool gl::TriangleStrip::s_init(const std::filesystem::path& parentPathToShaders) {
	s_deinit();

	gl::Shader vertexShader = gl::Shader(gl::ShaderType::VERTEX);
	gl::Shader fragmentShader = gl::Shader(gl::ShaderType::FRAGMENT);

	vertexShader.loadSourceCode(parentPathToShaders / std::filesystem::path(s_vertexShaderFileName));
	fragmentShader.loadSourceCode(parentPathToShaders / std::filesystem::path(s_fragmentShaderFileName));

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
void gl::TriangleStrip::s_deinit() {
	if (s_program != nullptr) {
		delete(s_program);
		s_program = nullptr;
	}
	s_multiLineList.clear();
}
void gl::TriangleStrip::s_render(gl::Buffer* transformBuffer, glm::mat4* viewProjectionMatrix) {
	if (!s_program->isLinked() || s_multiLineList.size() == 0)
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

	for (TriangleStrip* triangleStrip : s_multiLineList) {
		// Ready line buffer
		triangleStrip->buffer.bind();
		if (triangleStrip->buffer.size() == sizeof(GPUData) * triangleStrip->gpuData.size())
			triangleStrip->buffer.subwrite(0, sizeof(GPUData) * triangleStrip->gpuData.size(), triangleStrip->gpuData.data());
		else
			triangleStrip->buffer.write(sizeof(GPUData) * triangleStrip->gpuData.size(), triangleStrip->gpuData.data(), triangleStrip->buffer.getBufferUsage());
		triangleStrip->buffer.bindVertexBuffer(VERTEX_BUFFER_BINDING_POINT, 0, sizeof(TriangleStrip::GPUData));

		// Draw the GL_LineS
		glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<int>(triangleStrip->gpuData.size()));
	}

	glBindVertexArray(0U);
}

// Object | public

// Constructor / Destructor
gl::TriangleStrip::TriangleStrip() {
	s_multiLineList.push_back(this);
	multiLineNode = std::prev(s_multiLineList.end());

	gpuData[0].position = glm::vec3(-0.5f, -0.5f, 0.0f);
	gpuData[1].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	gpuData[2].position = glm::vec3(0.5f, 0.5f, 0.0f);
	gpuData[3].position = glm::vec3(0.5f, -0.5f, 0.0f);
}
gl::TriangleStrip::~TriangleStrip() {
	s_multiLineList.erase(multiLineNode);
}
