#pragma once

#include <cmath>
#include <array>
#include <stdexcept>

#include "Vector3.h"

class Matrix4 {
/*
    We will store matrix as:
      i=0  [ x0, x1, x2, x3,
      i=1    y0, y1, y2, y3,
      i=2    z0, z1, z2, z3,
      i=3    w0, w1, w2, w3 ]
*/
private:
    float data[4][4];

public:
    Matrix4();
    Matrix4(float x0, float y0, float z0, float w0, float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3);

    // Multiplication: * Operator Overloads
    Matrix4 operator*(const Matrix4& other);
    Vector3 operator*(const Vector3& vec) const;

    // Matrix-specific functions
    void updateElement(int row, int col, float value);
    float getElement(int row, int col) const;

    // Transformation utilities based on matrix
    // For practicity, I added these in the Matrix API,
    // however, these might be better candidates for a Transform class (think about it)
    // ... That's your homework!
    static Matrix4 translation(float tx, float ty, float tz);
    static Matrix4 scale(float sx, float sy, float sz);
    static Matrix4 rotationX(float angle);
    static Matrix4 rotationY(float angle);
    static Matrix4 rotationZ(float angle);
    // I encourage to implement the Euler Angles formula: Removes the gimball lock problem
};