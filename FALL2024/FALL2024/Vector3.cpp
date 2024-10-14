#include "Vector3.h"

#include <iostream>
#include <iomanip>

Vector3 Vector3::operator+(const Vector3& other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float scalar) const
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

// Component-wise multiplication
Vector3 Vector3::operator*(const Vector3& other) const
{
    return Vector3(x * other.x, y * other.y, z * other.z);
}

float Vector3::dot(const Vector3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

float Vector3::magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

float Vector3::magnitudSquared() const
{
    return dot(*this);
}

Vector3 Vector3::normalized() const
{
    float mag = magnitude();
    if (mag == 0) throw std::runtime_error("Cannot normalize zero vector");
    return Vector3(x / mag, y / mag, z / mag);
}

Vector3 Vector3::cross(const Vector3& other) const
{
    return Vector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

// Compute reciprocal of vector components with robust handling of zeros
Vector3 Vector3::reciprocal() const
{
    const float largeNumber = 1e30f; // A very large number to represent "infinity"
    return Vector3(
        x != 0.0f ? 1.0f / x : 0.0f,
        y != 0.0f ? 1.0f / y : 0.0f,
        z != 0.0f ? 1.0f / z : 0.0f
    );
}

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
    os << std::fixed << std::setprecision(2) << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}