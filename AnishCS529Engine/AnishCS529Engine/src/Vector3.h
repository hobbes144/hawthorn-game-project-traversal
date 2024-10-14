/*!****************************************************************************
 * \file   Vector3.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-14-2024
 * \brief  File conatining the custom Vector3 implementation for use with
 * OpenGL functions and other game logic.
 * 
 *****************************************************************************/
#ifndef VECTOR3_H
#define VECTOR3_H

#pragma once

#include <cmath>
#include <array>
#include <stdexcept>

class Vector3 {
public:
    float x, y, z;

    // Default Constructor
    Vector3() : x(0), y(0), z(0) {}
    // Parameterized Constructor with Initialization List
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Operator overloads
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float scalar) const;

    // Main mathematical operations
    float dot(const Vector3& other) const;
    float magnitude() const;
    float magnitudSquared() const;
    Vector3 normalized() const;
    Vector3 cross(const Vector3& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};

#endif // VECTOR3_H
