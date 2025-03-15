/*!****************************************************************************
 * \file   Quaternion.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \date   03-11-2025
 * \brief  Quaternion implementation for use with Transform
 * 
 *****************************************************************************/
#ifndef QUATERNION_H
#define QUATERNION_H

#pragma once

#include "VectorTemplated.h"
#include "Vector3.h"

class Quaternion : public VectorTemplated<float,4> {
private:
  bool isNormalized = false;
  bool isEulerVector = false;
  //bool isRotationMatrix = false;

  Vector3 eulerVector;
  //Matrix4 rotationMatrix;

  void setDirty() {
    isNormalized = false;
    isEulerVector = false;
    //isRotationMatrix = false;
  }
public:
  Quaternion(float w = 1.0f, float x = .0f, float y = .0f, float z = .0f) :
    VectorTemplated(), eulerVector(Vector3()){//, rotationMatrix(Matrix4()) {
    data[0] = w;  // w
    data[1] = x;  // x
    data[2] = y;  // y
    data[3] = z;  // z
  }

  Quaternion(VectorTemplated<float, 4> vec) : VectorTemplated(vec),
    eulerVector(Vector3()) {}//, rotationMatrix(Matrix4()) {}

  // Getter functions for w, x, y, z
  float w() const { return data[0]; }
  float x() const { return data[1]; }
  float y() const { return data[2]; }
  float z() const { return data[3]; }

  // Setter functions for w, x, y, z
  void setW(float w) { setDirty(); data[0] = w; }
  void setX(float x) { setDirty(); data[1] = x; }
  void setY(float y) { setDirty(); data[2] = y; }
  void setZ(float z) { data[3] = z; }

  //friend Quaternion operator*(const Matrix4&, const Quaternion&);

  friend Quaternion operator+(Quaternion q, const Quaternion& other) {
    return q += other;
  }

  Quaternion operator+=(const Quaternion& other) {
    setDirty();
    VectorTemplated::operator+=(other);
    return *this;
  }

  friend Quaternion operator*(Quaternion q, const Quaternion& other) {
    return q *= other;
  }

  Quaternion operator*=(const Quaternion& other) {
    setDirty();
    const Quaternion p(*this);
    data[0] = p.data[0] * other.data[0] - p.data[1] * other.data[1] - p.data[2] * other.data[2] - p.data[3] * other.data[3];  // w
    data[1] = p.data[0] * other.data[1] + p.data[1] * other.data[0] + p.data[2] * other.data[3] - p.data[3] * other.data[2];  // x
    data[2] = p.data[0] * other.data[2] - p.data[1] * other.data[3] + p.data[2] * other.data[0] + p.data[3] * other.data[1];  // y
    data[3] = p.data[0] * other.data[3] + p.data[1] * other.data[2] - p.data[2] * other.data[1] + p.data[3] * other.data[0];  // z
    return *this;
  }

  Vector3 operator*(const Vector3& v) const {
    const Vector3 quatVec(data[1], data[2],data[3]);

    const Vector3 uv = quatVec.cross(v);
    const Vector3 uuv = quatVec.cross(uv);
    return v + ((uv * data[0]) + uuv) * 2.0f;
  }

  Quaternion inverse() {
    normalize();
    return conjugate();
  }

  Quaternion conjugate() const {
    Quaternion result = Quaternion(data[0], -data[1], -data[2], -data[3]);
    result.isNormalized = isNormalized;
    return result;
  }

  void normalize() {
    if (!isNormalized) {
      VectorTemplated::normalize();
      isNormalized = true;
    }
  }

  Quaternion normalized() {
    normalize();
    Quaternion result = *this;
    return result;
  }

  // Axis 0 = x, 1 = y, 2 = z
  Vector3 getAxis(int axis) {
    switch (axis) {
    case 0:
      return *this * Vector3(1, 0, 0);
      break;
    case 1:
      return *this * Vector3(0, 1, 0);
      break;
    case 2:
      return *this * Vector3(0, 0, 1);
      break;
    }
  }

  /*Matrix4 toRotationMatrix() {
    if (isRotationMatrix)
      return rotationMatrix;
    normalize();
    float qw = w();
    float qx = x();
    float qy = y();
    float qz = z();

    rotationMatrix = Matrix4(
      1.0f - 2.0f * qy * qy - 2.0f * qz * qz, 2.0f * qx * qy + 2.0f * qz * qw, 2.0f * qx * qz - 2.0f * qy * qw, 0.0f,
      2.0f * qx * qy - 2.0f * qz * qw, 1.0f - 2.0f * qx * qx - 2.0f * qz * qz, 2.0f * qy * qz + 2.0f * qx * qw, 0.0f,
      2.0f * qx * qz + 2.0f * qy * qw, 2.0f * qy * qz - 2.0f * qx * qw, 1.0f - 2.0f * qx * qx - 2.0f * qy * qy, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f
    );

    isRotationMatrix = true;
    return rotationMatrix;
  }*/

  Vector3 toEuler() {
    if (isEulerVector)
      return eulerVector;
    normalize();


    //Vector3 angles;

    ////Roll
    //float sinr_cosp = 2 * (data[0] * data[1] + data[2] * data[3]);
    //float cosr_cosp = 1 - 2 * (data[1] * data[1] + data[2] * data[2]);
    //angles.z = -std::atan2f(sinr_cosp, cosr_cosp);

    ////Pitch
    //float sinp = std::sqrt(1 + 2 * (data[0] * data[2] - data[1] * data[3]));
    //float cosp = std::sqrt(1 - 2 * (data[0] * data[2] - data[1] * data[3]));
    //angles.x = 2 * std::atan2f(sinp, cosp) - 3.141592f / 2;

    ////Yaw
    //float siny_cosp = 2 * (data[0] * data[3] + data[1] * data[2]);
    //float cosy_cosp = 1 - 2 * (data[2] * data[2] + data[3] * data[3]);
    //angles.y = std::atan2f(siny_cosp, cosy_cosp);

    //return angles;

    //---------------------

    float y, x;

    // Note: following code was taken from glm
    // Roll (X-axis rotation)
    y = 2.0f * (data[1] * data[2] + data[0] * data[3]);
    x = data[0] * data[0] + data[1] * data[1] - data[2] * data[2] - data[3] * data[3];

    if (x == 0 && y == 0) //avoid atan2(0,0) - handle singularity - Matiis
      eulerVector.z = 0.0f;
    else
      eulerVector.z = atan2(y, x);

    // Pitch (Y-axis rotation)
    y = 2.0f * (data[2] * data[3] + data[0] * data[1]);
    x = data[0] * data[0] - data[1] * data[1] - data[2] * data[2] + data[3] * data[3];
    if (x == 0 && y == 0) //avoid atan2(0,0) - handle singularity - Matiis
      eulerVector.x = 2.0f * atan2(data[1], data[0]);
    else
      eulerVector.x = atan2(y, x);

    // Yaw (Z-axis rotation)
    eulerVector.y = asin(std::min(std::max(-2.0f * (data[1] * data[3] - data[0] * data[2]), -1.0f), 1.0f));

    isEulerVector = true;
    return eulerVector;
  }

  static Quaternion fromEuler(const Vector3& euler) {
    float cx = cos(euler.x * 0.5f);
    float sx = sin(euler.x * 0.5f);
    float cy = cos(euler.y * 0.5f);
    float sy = sin(euler.y * 0.5f);
    float cz = cos(euler.z * 0.5f);
    float sz = sin(euler.z * 0.5f);

    Quaternion q;
    q[0] = cx * cy * cz + sx * sy * sz; // w
    q[1] = sx * cy * cz - cx * sy * sz; // x
    q[2] = cx * sy * cz + sx * cy * sz; // y
    q[3] = cx * cy * sz - sx * sy * cz; // z

    return q;
  }

  static Quaternion fromEuler(const float pitch, const float yaw, const float roll) {
    float cx = cos(pitch * 0.5f);
    float sx = sin(pitch * 0.5f);
    float cy = cos(yaw * 0.5f);
    float sy = sin(yaw * 0.5f);
    float cz = cos(roll * 0.5f);
    float sz = sin(roll * 0.5f);

    Quaternion q;
    q[0] = cx * cy * cz + sx * sy * sz; // w
    q[1] = sx * cy * cz - cx * sy * sz; // x
    q[2] = cx * sy * cz + sx * cy * sz; // y
    q[3] = cx * cy * sz - sx * sy * cz; // z

    return q;
  }

  static Quaternion axisAngleToQuaternion(const Vector3& axis, float angle) {
    float halfAngle = angle * 0.5f;
    float s = std::sin(halfAngle);
    return Quaternion(std::cos(halfAngle), axis.x * s, axis.y * s, axis.z * s);
  }
};

//Quaternion operator*(const Matrix4& mat, const Quaternion& quat) {
//  return Quaternion(mat * quat);
//}

#endif // !QUATERNION_H
