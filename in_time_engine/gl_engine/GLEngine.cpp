#include "GLEngine.h"

// class OpenGLEngine

// Static | private

// Properties
gl::GLEngine* gl::GLEngine::s_singleton = nullptr;

// Static | public

// Functions
gl::GLEngine* gl::GLEngine::s_getSingleton() {
	return s_singleton;
}

// Object | public

// Constructor / Destructor
gl::GLEngine::GLEngine(const std::filesystem::path& rootPathToShaders) : rootPathToShaders(rootPathToShaders) {
	// Init engine
	if (s_singleton == nullptr)
		s_singleton = this;

	openGLVersion = std::string((char*)glGetString(GL_VERSION));

	// Set up OpenGL debug callback
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	#if defined(_DEBUG)
	// Set up debug message callback
	if (GLEW_KHR_debug && glDebugMessageCallback) {
		glDebugMessageCallback(Debug::s_messageCallback, nullptr);
	}
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
	Point::s_init(rootPathToShaders);
	Line::s_init(rootPathToShaders);
	MultiLine::s_init(rootPathToShaders);
	Triangle::s_init(rootPathToShaders);
	TriangleStrip::s_init(rootPathToShaders);
	TriangleFan::s_init(rootPathToShaders);
}
gl::GLEngine::~GLEngine() {
	// Deinit subsystems
	TriangleFan::s_deinit();
	TriangleStrip::s_deinit();
	Triangle::s_deinit();
	MultiLine::s_deinit();
	Line::s_deinit();
	Point::s_deinit();
	Transform::s_deinit();

	// Deinit engine
	if (s_singleton == this)
		s_singleton = nullptr;
}

// Functions
void gl::GLEngine::render() {
	for (Camera* camera : Camera::cameraList) {
		render(camera);
	}
}
void gl::GLEngine::render(Camera* camera) {
	if (camera->renderTarget == nullptr)
		return;

	GLFWwindow* renderTarget = camera->renderTarget;
	gl::ViewportRect viewportRect;
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
	Point::s_render(Transform::s_transformBuffer, &cameraMatrix);

	//TestPoint::render();
	//TestTriangle::s_render();
}
void gl::GLEngine::swapBuffers() {
	for (Camera* camera : Camera::cameraList) {
		glfwSwapBuffers(camera->renderTarget);
	}
}
