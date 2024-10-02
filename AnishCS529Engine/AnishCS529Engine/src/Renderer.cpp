#include "Renderer.h"

const float pi = 3.14159f;

// OpenGL Debugging function
void APIENTRY openglCallbackFunction(
	GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam)
{
	std::string sourceStr;
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             sourceStr = "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceStr = "Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceStr = "Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     sourceStr = "Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           sourceStr = "Other"; break;
	}

	std::string typeStr;
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               typeStr = "Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Deprecated Behavior"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeStr = "Undefined Behavior"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         typeStr = "Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         typeStr = "Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              typeStr = "Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          typeStr = "Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           typeStr = "Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               typeStr = "Other"; break;
	}

	std::string severityStr;
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         severityStr = "High"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       severityStr = "Medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          severityStr = "Low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "Notification"; break;
	}

	std::cerr << "OpenGL Debug Message\n"
		<< "Source: " << sourceStr << "\n"
		<< "Type: " << typeStr << "\n"
		<< "ID: " << id << "\n"
		<< "Severity: " << severityStr << "\n"
		<< "Message: " << message << std::endl;
}

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
	// Enable debug
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Makes sure errors are reported immediately
	glDebugMessageCallback(openglCallbackFunction, nullptr);
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

void Renderer::createVertexShader(const char* vertexShaderSource) {
	int  success;
	char infoLog[512];

	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShaderId);

	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}


void Renderer::createFragmentShader(const char* fragmentShaderSource) {
	int  success;
	char infoLog[512];

	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderId);

	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Renderer::initializeShaders() {
	int  success;
	char infoLog[512];

	shaderProgramId = glCreateProgram();

	glAttachShader(shaderProgramId, vertexShaderId);
	glAttachShader(shaderProgramId, fragmentShaderId);
	glLinkProgram(shaderProgramId);

	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	

	glUseProgram(shaderProgramId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	initializeBasicUniforms();
}

void Renderer::initializeBasicUniforms() {
	modelMatrixLoc = glGetUniformLocation(shaderProgramId, "modelMatrix");
	viewMatrixLoc = glGetUniformLocation(shaderProgramId, "viewMatrix");
	perspectiveMatrixLoc = glGetUniformLocation(shaderProgramId, "perspectiveMatrix");
	orthographicMatrixLoc = glGetUniformLocation(shaderProgramId, "orthographicMatrix");
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, Matrix4().getData());
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, Matrix4::lookAt(Vector3(0.0f, 0.0f, 3.0f), Vector3(), Vector3(0.0f, 1.0f, 0.0f)).getData());
	glUniformMatrix4fv(perspectiveMatrixLoc, 1, GL_FALSE, Matrix4::perspective(90.0f * pi / 180, gameWindow.getWidth() / gameWindow.getHeight(), 0.1f, 100.0f).getData());
	glUniformMatrix4fv(orthographicMatrixLoc, 1, GL_FALSE, Matrix4::orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f).getData());
}

unsigned int Renderer::getShaderProgramId() {
	return shaderProgramId;
}

void Renderer::drawTriangle(Vector3 a, Vector3 b, Vector3 c) {
	float vertices[] = {
		a.x, a.y, a.z,
		b.x, b.y, b.z,
		c.x, c.y, c.z
	};
	unsigned int vaoId, vboId;
	glGenVertexArrays(1, &vaoId);
	glGenBuffers(1, &vboId);

	glBindVertexArray(vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgramId);
	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

unsigned int Renderer::addTriangle(Vector3 a, Vector3 aColor, Vector3 b, Vector3 bColor, Vector3 c, Vector3 cColor) {
	float vertices[] = {
		a.x, a.y, a.z, aColor.x, aColor.y, aColor.z,
		b.x, b.y, b.z, bColor.x, bColor.y, bColor.z,
		c.x, c.y, c.z, cColor.x, cColor.y, cColor.z
	};

	unsigned int vaoId, vboId;
	glGenVertexArrays(1, &vaoId);
	glGenBuffers(1, &vboId);

	glBindVertexArray(vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vaoId;
}

unsigned int Renderer::addTriangle(Vector3 a, Vector3 b, Vector3 c) {
	float vertices[] = {
		a.x, a.y, a.z,
		b.x, b.y, b.z,
		c.x, c.y, c.z
	};

	unsigned int vaoId, vboId;
	glGenVertexArrays(1, &vaoId);
	glGenBuffers(1, &vboId);

	glBindVertexArray(vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vaoId;
}

void Renderer::UpdateTriangle(Matrix4 modelMatrix) {
	glUniformMatrix4fv(viewMatrixLoc, 
		1, 
		GL_FALSE, 
		Matrix4::lookAt(Vector3(0.0f, 0.0f, 3.0f), Vector3(), Vector3(0.0f, 1.0f, 0.0f)).getData()
	);
	glUniformMatrix4fv(perspectiveMatrixLoc, 
		1, 
		GL_FALSE, 
		Matrix4::perspective(45.0f * pi / 180, gameWindow.getWidth() / gameWindow.getHeight(), 0.1f, 100.0f).getData()
	);
	glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix.getData());
}

void Renderer::drawTriangle(unsigned int triangleVaoId) {
	glBindVertexArray(triangleVaoId);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}