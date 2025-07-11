#include "GLTriangleFan.h"

// class OpenGLLine

// Static | private

// Properties
unsigned int gl::TriangleFan::s_vertexArrayObject = 0U;
gl::Program* gl::TriangleFan::s_program = nullptr;
std::list<gl::TriangleFan*> gl::TriangleFan::s_triangleFanList = std::list<gl::TriangleFan*>();
std::string gl::TriangleFan::s_vertexShaderFileName = "triangle\\triangle.vert";
std::string gl::TriangleFan::s_fragmentShaderFileName = "triangle\\triangle.frag";

// Functions
bool gl::TriangleFan::s_init(const std::filesystem::path& parentPathToShaders) {
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
void gl::TriangleFan::s_deinit() {
	if (s_program != nullptr) {
		delete(s_program);
		s_program = nullptr;
	}
	s_triangleFanList.clear();
}
void gl::TriangleFan::s_render(gl::Buffer* transformBuffer, glm::mat4* viewProjectionMatrix) {
	if (!s_program->isLinked() || s_triangleFanList.size() == 0)
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

	for (TriangleFan* triangleFan : s_triangleFanList) {
		// Ready line buffer
		triangleFan->buffer.bind();
		if (triangleFan->buffer.size() == sizeof(GPUData) * triangleFan->gpuData.size())
			triangleFan->buffer.subwrite(0, sizeof(GPUData) * triangleFan->gpuData.size(), triangleFan->gpuData.data());
		else
			triangleFan->buffer.write(sizeof(GPUData) * triangleFan->gpuData.size(), triangleFan->gpuData.data(), triangleFan->buffer.getBufferUsage());
		triangleFan->buffer.bindVertexBuffer(VERTEX_BUFFER_BINDING_POINT, 0, sizeof(TriangleFan::GPUData));

		// Draw the GL_LineS
		glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<int>(triangleFan->gpuData.size()));
	}

	glBindVertexArray(0U);
}

// Object | public

// Constructor / Destructor
gl::TriangleFan::TriangleFan() {
	s_triangleFanList.push_back(this);
	multiLineNode = std::prev(s_triangleFanList.end());

	gpuData[0].position = glm::vec3(0.5f, -0.5f, 0.0f);
	gpuData[1].position = glm::vec3(-0.5f, -0.5f, 0.0f);
	gpuData[2].position = glm::vec3(-0.5f, 0.5f, 0.0f);
	gpuData[3].position = glm::vec3(0.5f, 0.5f, 0.0f);
}
gl::TriangleFan::~TriangleFan() {
	s_triangleFanList.erase(multiLineNode);
}
