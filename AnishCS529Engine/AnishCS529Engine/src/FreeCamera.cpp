#include "precompiled.h"
#include "FreeCamera.h"

std::shared_ptr<FreeCamera> FreeCamera::lookAt(const Vector3 & target, const Vector3 & upVector) {
  viewMatrix = Matrix4::lookAt(position, target, upVector);

  rotation = viewMatrix.toQuaternion();
  
  return shared_from_this();
}

std::shared_ptr<FreeCamera> FreeCamera::move(const Vector3 & direction, float amount) {
  position = position + ( direction * amount );

  return shared_from_this();
}

std::shared_ptr<FreeCamera> FreeCamera::rotate(float roll, float pitch, float yaw) {
  rotation = rotation * Quaternion::fromEuler(roll, pitch, yaw);

  return shared_from_this();
}

std::shared_ptr<FreeCamera> FreeCamera::rotate(Quaternion _rotation) {
  rotation = rotation * _rotation;

  return shared_from_this();
}

std::shared_ptr<FreeCamera> FreeCamera::setPosition(Vector3 _position) {
  position = _position;

  return shared_from_this();
}

std::shared_ptr<FreeCamera> FreeCamera::setRotation(float roll, float pitch, float yaw) {
  rotation = Quaternion::fromEuler(roll, pitch, yaw);

  return shared_from_this();
}

std::shared_ptr<FreeCamera> FreeCamera::setRotation(Quaternion _rotation) {
  rotation = _rotation;

  return shared_from_this();
}
