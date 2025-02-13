#include "Vector3.h"

#include <iostream>
#include <iomanip>

Vector3 Vector3::operator+(const Vector3& other) const
{
  return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator+(float scalar) const {
  return Vector3(x + scalar, y + scalar, z + scalar);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
  return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator-(float scalar) const {
  return Vector3(x - scalar, y - scalar, z - scalar);
}

Vector3 Vector3::operator-() const {
  return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(float scalar) const
{
  return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator*(const Vector3& other) const
{
  return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator/(float scalar) const
{
  return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3 Vector3::operator/(const Vector3& other) const
{
  return Vector3(x / other.x, y / other.y, z / other.z);
}

bool Vector3::operator==(const Vector3 & other) const {
  return ( x == other.x && y == other.y && z == other.z );
}

bool Vector3::operator!=(const Vector3 & other) const {
  return ( !(*this == other) );
}

float Vector3::operator[](int index) const {
  if (index == 0) return x;
  else if (index == 1) return y;
  else return z;
}

float& Vector3::operator[](const int index) {
  if (index == 0) return x;
  else if (index == 1) return y;
  else return z;
}

float Vector3::dot(const Vector3& other) const
{
  return ((x * other.x) + (y * other.y) + (z * other.z));
}

float Vector3::magnitude() const
{
  return (float)(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
}

float Vector3::magnitudSquared() const
{
  return (float)(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector3 Vector3::normalized() const
{
  float magnitude_val = magnitude();
  if (magnitude_val == 0) throw std::runtime_error("Cannot normalize zero vector");
  return Vector3(x / magnitude_val, y / magnitude_val, z / magnitude_val);
}

Vector3 Vector3::cross(const Vector3& other) const
{
  return Vector3((y * other.z - z * other.y), (z * other.x - x * other.z), (x * other.y - y * other.x));
}

Vector3 Vector3::reciprocal() const
{
  const float largeNumber = 1e30f;
  return Vector3(
    x != 0.0f ? 1.0f / x : largeNumber,
    y != 0.0f ? 1.0f / y : largeNumber,
    z != 0.0f ? 1.0f / z : largeNumber
  );
}

std::ostream& operator<<(std::ostream& os, const Vector3& v) {
  os << std::fixed << std::setprecision(2) << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}