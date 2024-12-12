///*!****************************************************************************
// * \file   Renderer.h
// * \author Anish Murthy (anish.murthy.dev@gmail.com)
// * \par    **DigiPen Email**
// *    anish.murthy@digipen.edu
// * \par    **Course**
// *    CS529
// * \date   10-14-2024
// * \brief  Renderer implementation to initialize the OpenGL libraries
// * and libraries.
// * 
// *****************************************************************************/
//#ifndef RENDERER_H
//#define RENDERER_H
//
//#pragma once
//
//#include <glad/glad.h> 
//#include <GLFW/glfw3.h>
//
//#include "GameWindow.h"
//#include "Vector3.h"
//#include "Matrix4.h"
//
//class Renderer {
//public:
//	Renderer(GameWindow& gameWindow);
//
//	void clear(float r, float g, float b, float a);
//	void swapBuffers();
//	void draw(GLenum mode, GLint count, bool indexed);
//	void enableDepth(bool enable = true);
//
//private:
//	GameWindow& gameWindow;
//	bool depthEnabled;
//
//	void initialize();
//	bool loadGraphicsAPIFunctions();
//	void setupCallbacks();
//	void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height);
//
//};
//
//#endif // RENDERER_H
