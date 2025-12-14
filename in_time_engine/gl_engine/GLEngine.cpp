#include "GLEngine.h"

namespace gl {
	// class OpenGLEngine

	// Static | private

	// Properties
	Engine* Engine::s_singleton = nullptr;

	// Static | public

	// Functions
	Engine* Engine::s_getSingleton() {
		return s_singleton;
	}

	// Object | public

	// Constructor / Destructor
	Engine::Engine() {
		// Init engine
		if (s_singleton == nullptr)
			s_singleton = this;
		
		const GLubyte* glVersionPointer = glGetString(GL_VERSION);
		openGLVersion = std::string((const char*)glVersionPointer);

#if defined(_DEBUG)
		// Set up debug message callback
		bool success{ false };
		success &= Debug::s_enableDebugOutput();
		success &= debug.registerToCallback();
		std::cout << "OpenGL debug output enabled: " << (success ? "true" : "false") << std::endl;
#endif

		// Set OpenGL features
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glDisable(GL_DEPTH_TEST);

		// Set up depth buffer
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_GEQUAL);
		glDepthRange(1.0f, -1.0f);

		// Init subsystems
		Transform::s_init();
		Line::s_init(rootPathToShaders);
		MultiLine::s_init(rootPathToShaders);
		Triangle::s_init(rootPathToShaders);
		TriangleStrip::s_init(rootPathToShaders);
		TriangleFan::s_init(rootPathToShaders);
	}
	Engine::~Engine() {
		// Deinit subsystems
		TriangleFan::s_deinit();
		TriangleStrip::s_deinit();
		Triangle::s_deinit();
		MultiLine::s_deinit();
		Line::s_deinit();
		Transform::s_deinit();

		// Deinit engine
		if (s_singleton == this)
			s_singleton = nullptr;
	}

	// Functions | render
	void Engine::render() {
		for (Camera* camera : Camera::cameraList) {
			render(camera);
		}
	}
	void Engine::render(Camera* camera) {
		if (camera->renderTarget == nullptr)
			return;

		GLFWwindow* renderTarget = camera->renderTarget;
		glfwMakeContextCurrent(renderTarget);
		ViewportRect viewportRect;
		glfwGetFramebufferSize(renderTarget, &viewportRect.width, &viewportRect.height);
		glViewport(viewportRect.x, viewportRect.y, viewportRect.width, viewportRect.height);

		glm::vec4 clearColor = camera->backgroundColor;
		float clearDepth = camera->clearDepth;
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClearDepth(clearDepth);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 cameraMatrix = camera->getCameraMatrix();

		TriangleFan::s_render(Transform::s_transformBuffer, &cameraMatrix);
		TriangleStrip::s_render(Transform::s_transformBuffer, &cameraMatrix);
		Triangle::s_render(Transform::s_transformBuffer, &cameraMatrix);
		MultiLine::s_render(Transform::s_transformBuffer, &cameraMatrix);
		Line::s_render(Transform::s_transformBuffer, &cameraMatrix);
	}
	void Engine::swapBuffers() {
		for (Camera* camera : Camera::cameraList)
			if (camera->renderTarget != nullptr)
				glfwSwapBuffers(camera->renderTarget);
	}
}