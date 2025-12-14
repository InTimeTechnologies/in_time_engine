#include "GLTriangleFan.h"

namespace gl {
	// class OpenGLLine

	// Static | private

	// Properties
	unsigned int TriangleFan::s_vertexArrayObject = 0U;
	Program* TriangleFan::s_program = nullptr;
	std::list<TriangleFan*> TriangleFan::s_triangleFanList = std::list<TriangleFan*>();
	std::string TriangleFan::s_vertexShaderFileName = "triangle\\triangle.vert";
	std::string TriangleFan::s_fragmentShaderFileName = "triangle\\triangle.frag";

	// Functions
	bool TriangleFan::s_init(const std::filesystem::path& parentPathToShaders) {
		s_deinit();

		Shader vertexShader = Shader(Shader::Type::VERTEX);
		Shader fragmentShader = Shader(Shader::Type::FRAGMENT);

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
	void TriangleFan::s_deinit() {
		if (s_program != nullptr) {
			delete s_program;
			s_program = nullptr;
		}
		s_triangleFanList.clear();
	}
	void TriangleFan::s_render(Buffer* transformBuffer, glm::mat4* viewProjectionMatrix) {
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
			if (triangleFan->buffer.getMemorySize() == sizeof(GPUData) * triangleFan->gpuData.size())
				triangleFan->buffer.subwrite(0, sizeof(GPUData) * triangleFan->gpuData.size(), triangleFan->gpuData.data());
			else
				triangleFan->buffer.allocate(sizeof(GPUData) * triangleFan->gpuData.size(), triangleFan->gpuData.data());
			triangleFan->buffer.bindVertexBuffer(VERTEX_BUFFER_BINDING_POINT, 0, sizeof(TriangleFan::GPUData));

			// Draw the GL_LineS
			glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<int>(triangleFan->gpuData.size()));
		}

		glBindVertexArray(0U);
	}

	// Object | public

	// Constructor / Destructor
	TriangleFan::TriangleFan() {
		s_triangleFanList.push_back(this);
		multiLineNode = std::prev(s_triangleFanList.end());

		gpuData[0].position = glm::vec3(0.5f, -0.5f, 0.0f);
		gpuData[1].position = glm::vec3(-0.5f, -0.5f, 0.0f);
		gpuData[2].position = glm::vec3(-0.5f, 0.5f, 0.0f);
		gpuData[3].position = glm::vec3(0.5f, 0.5f, 0.0f);
	}
	TriangleFan::~TriangleFan() {
		s_triangleFanList.erase(multiLineNode);
	}
}
