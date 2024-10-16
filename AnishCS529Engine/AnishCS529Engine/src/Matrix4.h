/*!****************************************************************************
 * \file   Matrix4.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-05-2024
 * \brief  File conatining the custom Matrix4 implementation for use with
 * OpenGL functions and other game logic.
 * 
 *****************************************************************************/
#ifndef MATRIX4_H
#define MATRIX4_H

#pragma once

#include <cmath>
#include <array>
#include <stdexcept>

#include "Vector3.h"

/*!****************************************************************************
 * \brief Class that implements a custom 4x4 Matrix for use with OpenGL
 * functions and game logic.
 *
 *****************************************************************************/
class Matrix4
{
  /*
    We will store matrix as:
      i=0  [ x0, x1, x2, x3,
      i=1    y0, y1, y2, y3,
      i=2    z0, z1, z2, z3,
      i=3    w0, w1, w2, w3 ]
  */
private:
  /** Data of the Matrix4 object */
  float data[4][4];

public:
  // Constructors
  Matrix4();
  Matrix4(float x0, float y0, float z0, float w0,
          float x1, float y1, float z1, float w1,
          float x2, float y2, float z2, float w2,
          float x3, float y3, float z3, float w3);

  // Multiplication: * Operator Overloads
  Matrix4 operator*(const Matrix4 &other);
  Vector3 operator*(const Vector3 &vec) const;

  // Matrix-specific functions
  const float * getData() const;
  void updateElement(int row, int col, float value);
  float getElement(int row, int col) const;

  // Todo: Figure out how many of these need to be const inputs and how it'll 
  // affect the program.
  static Matrix4 translation(float tx, float ty, float tz);
  static Matrix4 translation(const Vector3& translationVec);
  static Matrix4 scale(float sx, float sy, float sz);
  static Matrix4 scale(const Vector3& scaling);
  static Matrix4 rotationX(float angle);
  static Matrix4 rotationY(float angle);
  static Matrix4 rotationZ(float angle);
  static Matrix4 rotationXYZ(float angleX, float angleY, float angleZ);
  static Matrix4 rotationXYZ(const Vector3 rotation);
  static Matrix4 orthographic(
      const float left,
      const float right,
      const float bottom,
      const float top,
      const float near,
      const float far);
  static Matrix4 perspective(const float fov, const float aspectRatio,
                             const float near, const float far);
  static Matrix4 lookAt(const Vector3 &eye, const Vector3 &center,
                        const Vector3 &up);
  // I encourage to implement the Euler Angles formula: Removes the gimball lock problem
};

#endif // MATRIX4_H
