#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "GameWindow.h"
#include "Vector3.h"

class Renderer {
private:
	GameWindow& gameWindow;
	unsigned int vertexShaderId;
	unsigned int fragmentShaderId;
	unsigned int shaderProgramId;

	void initialize();
	bool loadGraphicsAPIFunctions();
	void setupCallbacks();
	void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height);

public:
	Renderer(GameWindow& gameWindow);

	void clear(float r, float g, float b, float a);
	void swapBuffers();
	void createVertexShader(const char* vertexShaderSource);
	void createFragmentShader(const char* fragmentShaderSource);
	void initializeShaders();
	unsigned int getShaderProgramId();
	void drawTriangle(Vector3 a, Vector3 b, Vector3 c);
	unsigned int addTriangle(Vector3 a, Vector3 aColor, Vector3 b, Vector3 bColor, Vector3 c, Vector3 cColor);
	unsigned int addTriangle(Vector3 a, Vector3 b, Vector3 c);
	void drawTriangle(unsigned int triangleVaoId);
};