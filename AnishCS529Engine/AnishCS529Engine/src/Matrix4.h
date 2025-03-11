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

#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>

#include "Vector3.h"
#include "VectorTemplated.h"

/*!****************************************************************************
 * \brief Class that implements a custom 4x4 Matrix for use with OpenGL
 * functions and game logic.
 *
 *****************************************************************************/
class Matrix4
{
  /*
    We will store matrix in column major:
               [
    right    =   x0, y0, z0, w0,
    up       =   x1, y1, z1, w1,
    forward  =   x2, y2, z2, w2,
    position =   x3, y3, z3, w3,
               ]
    Note that this is transposed form of a regular matrix.
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
  Matrix4 operator*(const float scalar) const;
  Matrix4 operator*(const Matrix4 &other);
  Vector3 operator*(const Vector3 &vec) const;

  float* operator[](int row);
  const float* operator[](int row) const;

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
  static Matrix4 inverse(const Matrix4& m);
  // I encourage to implement the Euler Angles formula: Removes the gimball lock problem

  Vector3 transformDirection(const Vector3& direction) const;

};

std::ostream& operator<<(std::ostream& os, const Matrix4& m);

#endif // MATRIX4_H
