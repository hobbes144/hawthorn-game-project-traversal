/*!****************************************************************************
 * \file   Camera.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-14-2024
 * \brief  Camera object
 * 
 *****************************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <cassert>

/* Base class */
#include "Matrix4.h"

class Camera {
public:
  Camera(std::string _name) : 
    name(_name), position(Vector3()),
    rotation(Quaternion(0.0f,0.0f,1.0f,0.0f)),
    viewProjectionMatrix(Matrix4())
  {
    forward = rotation.forward();
    up = rotation.up();
    right = rotation.right();
    viewMatrix = Matrix4::lookAt(position, position + forward, up);
    inverseViewMatrix = Matrix4::inverse(viewMatrix);
  };

  ~Camera() = default;

  /* Component functions */
  virtual void update();

  /* Utility functions */
  void setPerspectiveProjection(
    const float fov,
    const float aspectRatio,
    const float near,
    const float far);
  void setOrthographicProjection(
    const float left,
    const float right,
    const float bottom,
    const float top,
    const float near,
    const float far);

  const Matrix4& getViewMatrix();
  const Matrix4& getInverseViewMatrix();
  const Matrix4& getProjectionMatrix();
  const Matrix4& getViewProjectionMatrix();
  const Matrix4& getViewProjectionWithoutPositionMatrix();

protected:
  std::string name;
  Matrix4 viewMatrix;
  Matrix4 projectionMatrix;
  Matrix4 inverseViewMatrix;
  Matrix4 viewProjectionMatrix;
  Vector3 position = Vector3();
  Quaternion rotation = Quaternion();

  Vector3 forward;
  Vector3 right;
  Vector3 up;

  virtual void updateViewProjectionMatrix();
  virtual void updateViewMatrix();
};

#endif // !CAMERA_H
