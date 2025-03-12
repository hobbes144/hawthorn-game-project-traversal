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
    
    template <std::convertible_to<float> Numeric>
    Vector3(Numeric x, Numeric y, Numeric z) : x(float(x)), y(float(y)), z(float(z)) {}
        
    template <std::convertible_to<float> Numeric>
    Vector3(Numeric val) : x(float(val)), y(float(val)), z(float(val)) {}

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
    Vector3 abs() const;

    std::vector<float> getData() const { return { x, y, z }; }

    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};

#endif // VECTOR3_H
