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
#include "GameObject.h"

class Camera : public GameObject {
public:
  Camera(std::string name) : GameObject(name, GameObject::Tag::SYSTEM) {};
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
  const Matrix4 getInverseViewMatrix();
  const Matrix4& getProjectionMatrix();

private:
  Matrix4 viewMatrix;
  Matrix4 projectionMatrix;
  Matrix4 inverseViewMatrix;
  Vector3 oldPosition = Vector3();
  Quaternion oldRotation = Quaternion();

  Vector3 up;
  Vector3 front;
  Vector3 right;

  void updateViewMatrix();
};

#endif // !CAMERA_H
