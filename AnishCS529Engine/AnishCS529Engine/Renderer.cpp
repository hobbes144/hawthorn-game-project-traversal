#include "Renderer.h"


/* Private functions */
void Renderer::initialize() {
	gameWindow.setWindowHints([]() {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		/* Todo: What is this command? */
		});
	
	glfwMakeContextCurrent(gameWindow.getNativeWindow());
	setupCallbacks();

	if (!loadGraphicsAPIFunctions()) {
		throw std::runtime_error("Failed to load Graphics API Functions");
	}
}

bool Renderer::loadGraphicsAPIFunctions() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}
	return true;
}

void Renderer::setupCallbacks() {
	gameWindow.setResizeCallback([this](GLFWwindow* pWindow, int width, int height) {
		this->framebufferSizeCallback(pWindow, width, height);
		});
}

void Renderer::framebufferSizeCallback(GLFWwindow* pWindow, int width, int height) {
	glViewport(0, 0, width, height);
	// Additional rendering adjustments can be made here
}

/* Public functions */
Renderer::Renderer(GameWindow& gameWindow) : gameWindow(gameWindow) {
	initialize();
}

void Renderer::clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::swapBuffers() {
	glfwSwapBuffers(gameWindow.getNativeWindow());
}

//glViewport(0, 0, 800, 600);
//
//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);