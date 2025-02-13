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
#include <vector>
#include <stdexcept>

class Vector3 {
public:
    float x, y, z;

    // Default Constructor
    Vector3() : x(0), y(0), z(0) {}
    // Parameterized Constructor with Initialization List
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3(float val) : x(val), y(val), z(val) {}

    // Operator overloads
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator+(float scalar) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator-(float scalar) const;
    Vector3 operator-() const;
    Vector3 operator*(float scalar) const;
    Vector3 operator*(const Vector3& other) const;
    Vector3 operator/(float scalar) const;
    Vector3 operator/(const Vector3& other) const;
    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;
    float operator[](int index) const;
    float& operator[](const int index);

    // Main mathematical operations
    float dot(const Vector3& other) const;
    float magnitude() const;
    float magnitudSquared() const;
    Vector3 normalized() const;
    Vector3 cross(const Vector3& other) const;
    Vector3 reciprocal() const;

    std::vector<float> getData() const { return { x, y, z }; }

    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};

#endif // VECTOR3_H
