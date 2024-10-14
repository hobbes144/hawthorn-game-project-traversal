#pragma once

#include <glew.h>
#include <glfw3.h>
#include "GameWindow.h"
#include "Vector3.h"
#include "Matrix4.h"

class Renderer {
public:
    Renderer(GameWindow& window);

    // Delete copy constructor and assignment operator
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void clear(float r, float g, float b, float a);
    void draw(unsigned int dataCount, GLenum drawingMode, bool indexed);
    void swapBuffers();

    GameWindow& getWindowPtr() { return pWindow; }
    // temp
    //void drawTriangle(const Vector3 v1, const Vector3 v2, const Vector3 v3, const Matrix4 modelMatrix);

private:
    void initialize();
    void setupCallbacks();
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    GameWindow& pWindow;

    // temp
    /*GLuint shaderProgram;
    GLuint VAO;
    GLuint VBO;
    Matrix4 projectionMatrix;
    Matrix4 viewMatrix;*/
};