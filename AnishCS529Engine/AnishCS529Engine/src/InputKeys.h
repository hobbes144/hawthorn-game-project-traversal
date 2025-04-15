/*!****************************************************************************
 * \file   InputKeys.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-22-2024
 * \brief  Key references to set up supported key constexpr
 * 
 *****************************************************************************/
#ifndef INPUT_KEYS_H
#define INPUT_KEYS_H

#pragma once

#ifndef ENGINE_GLFW_H
#define ENGINE_GLFW_H
#include "GLFW/glfw3.h"
#endif // ENGINE_GLFW_H


using Key = unsigned int;

constexpr Key KEY_UNKNOWN = GLFW_KEY_UNKNOWN;
constexpr Key KEY_SPACE = GLFW_KEY_SPACE;
constexpr Key KEY_0 = GLFW_KEY_0;
constexpr Key KEY_1 = GLFW_KEY_1;
constexpr Key KEY_2 = GLFW_KEY_2;
constexpr Key KEY_3 = GLFW_KEY_3;
constexpr Key KEY_4 = GLFW_KEY_4;
constexpr Key KEY_5 = GLFW_KEY_5;
constexpr Key KEY_6 = GLFW_KEY_6;
constexpr Key KEY_7 = GLFW_KEY_7;
constexpr Key KEY_8 = GLFW_KEY_8;
constexpr Key KEY_9 = GLFW_KEY_9;
constexpr Key KEY_A = GLFW_KEY_A;
constexpr Key KEY_B = GLFW_KEY_B;
constexpr Key KEY_C = GLFW_KEY_C;
constexpr Key KEY_D = GLFW_KEY_D;
constexpr Key KEY_E = GLFW_KEY_E;
constexpr Key KEY_F = GLFW_KEY_F;
constexpr Key KEY_G = GLFW_KEY_G;
constexpr Key KEY_H = GLFW_KEY_H;
constexpr Key KEY_I = GLFW_KEY_I;
constexpr Key KEY_J = GLFW_KEY_J;
constexpr Key KEY_K = GLFW_KEY_K;
constexpr Key KEY_L = GLFW_KEY_L;
constexpr Key KEY_M = GLFW_KEY_M;
constexpr Key KEY_N = GLFW_KEY_N;
constexpr Key KEY_O = GLFW_KEY_O;
constexpr Key KEY_P = GLFW_KEY_P;
constexpr Key KEY_Q = GLFW_KEY_Q;
constexpr Key KEY_R = GLFW_KEY_R;
constexpr Key KEY_S = GLFW_KEY_S;
constexpr Key KEY_T = GLFW_KEY_T;
constexpr Key KEY_U = GLFW_KEY_U;
constexpr Key KEY_V = GLFW_KEY_V;
constexpr Key KEY_W = GLFW_KEY_W;
constexpr Key KEY_X = GLFW_KEY_X;
constexpr Key KEY_Y = GLFW_KEY_Y;
constexpr Key KEY_Z = GLFW_KEY_Z;
constexpr Key KEY_ESCAPE = GLFW_KEY_ESCAPE;
constexpr Key KEY_ENTER = GLFW_KEY_ENTER;
constexpr Key KEY_RIGHT = GLFW_KEY_RIGHT;
constexpr Key KEY_LEFT = GLFW_KEY_LEFT;
constexpr Key KEY_DOWN = GLFW_KEY_DOWN;
constexpr Key KEY_UP = GLFW_KEY_UP;
constexpr Key KEY_F1 = GLFW_KEY_F1;
constexpr Key KEY_F11 = GLFW_KEY_F11;
constexpr Key KEY_F13 = GLFW_KEY_F13;
constexpr Key KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL;
constexpr Key KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT;
constexpr Key KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT;

/*!****************************************************************************
 * \brief List of all keys supported by the engine
 * 
 * This is kept as a handy way to init Input.
 * 
 *****************************************************************************/
inline std::vector<Key> allKeys = {
  32, // Space
  48, 49, 50, 51, 52, 53, 54, 55, 56, 57, // 0-9
  65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83,
  84, 85, 86, 87, 88, 89, 90, // a-z
  256, // Escape
  257, // Enter
  262, 263, 264, 265, // Right, Left, Down, Up
  290, // F1
  302, // F13
  341, // Left Control
  342  // Left Alt
};

#endif // INPUT_KEYS_H
