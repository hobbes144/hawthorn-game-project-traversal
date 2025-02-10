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
#include "Node.h"

class Camera : public Node {
public:
  Camera(std::string name) : Node(name) {};
  ~Camera() = default;

  /* Component functions */
  virtual void initialize();
  virtual void update(float deltaTime);
  virtual void shutdown();

  /* Utility functions */
  std::shared_ptr<Camera> setPerspectiveProjection(
    const float fov,
    const float aspectRatio,
    const float near,
    const float far);
  std::shared_ptr<Camera> setOrthographicProjection(
    const float left,
    const float right,
    const float bottom,
    const float top,
    const float near,
    const float far);

  std::shared_ptr<Camera> lookAt(
    const Vector3& target,
    const Vector3& upVector);
  std::shared_ptr<Camera> move(
    const Vector3& direction,
    float amount);
  std::shared_ptr<Camera> rotate(
    float roll,
    float pitch,
    float yaw
  );

  const Matrix4 getViewMatrix();
  const Matrix4& getProjectionMatrix();

private:
  Matrix4 viewMatrix;
  Matrix4 projectionMatrix;

  Vector3 up;
  Vector3 front;
  Vector3 right;

  void updateViewMatrix();
};

#endif // !CAMERA_H
