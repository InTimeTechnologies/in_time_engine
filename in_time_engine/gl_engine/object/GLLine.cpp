#include "GLLine.h"

// class OpenGLLine

// Static | private

// Properties
unsigned int gl::Line::s_vertexArrayObject = 0U;
gl::Program* gl::Line::s_program = nullptr;
std::list<gl::Line*> gl::Line::s_lineList = std::list<gl::Line*>();
std::string gl::Line::s_vertexShaderFileName = "line\\line.vert";
std::string gl::Line::s_fragmentShaderFileName = "line\\line.frag";

// Functions
bool gl::Line::s_init(const std::filesystem::path& parentPathToShaders) {
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
void gl::Line::s_deinit() {
	if (s_program != nullptr) {
		delete(s_program);
		s_program = nullptr;
	}
	s_lineList.clear();
}
void gl::Line::s_render(gl::Buffer* transformBuffer, glm::mat4* viewProjectionMatrix) {
	if (!s_program->isLinked() || s_lineList.size() == 0)
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

	for (Line* line : s_lineList) {
		// Set line width
		glLineWidth(line->width);

		// Ready line buffer
		line->buffer.bind();
		line->buffer.subwrite(0, sizeof(line->gpuData), line->gpuData);
		line->buffer.bindVertexBuffer(VERTEX_BUFFER_BINDING_POINT, 0, sizeof(Line::GPUData));

		// Draw the GL_LineS
		glDrawArrays(GL_LINES, 0, 2);
	}

	glBindVertexArray(0U);
}

// Object | public

// Constructor / Destructor
gl::Line::Line() {
	s_lineList.push_back(this);
	lineNode = std::prev(s_lineList.end());

	gpuData[0].position = glm::vec3(-0.5f, 0.0f, 0.0f);
	gpuData[1].position = glm::vec3(0.5f, 1.0f, 0.0f);
}
gl::Line::~Line() {
	s_lineList.erase(lineNode);
}
