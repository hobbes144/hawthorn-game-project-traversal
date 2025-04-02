#include "precompiled.h"
#include "FreeCamera.h"

void FreeCamera::update() {}

std::shared_ptr<FreeCamera> FreeCamera::lookAt(const Vector3 & target, const Vector3 & upVector) {
  Vector3 forward = ( target - position ).normalized();
  right = (up.cross(forward)).normalized();
  up = forward.cross(right);
  
  viewMatrix = Matrix4::lookAt(position, target, upVector);
  inverseViewMatrix = Matrix4::inverse(viewMatrix);

  rotation = viewMatrix.toQuaternion();
  
  return shared_from_this();
}

std::shared_ptr<FreeCamera> FreeCamera::move(const Vector3 & direction, float amount) {
  position = position + ( direction * amount );

  return shared_from_this();
}

std::shared_ptr<FreeCamera> FreeCamera::rotate(float roll, float pitch, float yaw) {
  rotation = rotation * Quaternion::fromEuler(roll, pitch, yaw);
  forward = rotation * Vector3(0.0f, 0.0f, -1.0f);  // Camera forward is -Z
  up = rotation * Vector3(0.0f, 1.0f, 0.0f);
  right = rotation * Vector3(1.0f, 0.0f, 0.0f);

  viewMatrix = Matrix4::lookAt(position, position + forward, up);
  inverseViewMatrix = Matrix4::inverse(viewMatrix);
  return shared_from_this();
}

std::shared_ptr<FreeCamera> FreeCamera::rotate(Quaternion _rotation) {
  rotation = rotation * _rotation;
  forward = rotation * Vector3(0.0f, 0.0f, -1.0f);  // Camera forward is -Z
  up = rotation * Vector3(0.0f, 1.0f, 0.0f);
  right = rotation * Vector3(1.0f, 0.0f, 0.0f);

  viewMatrix = Matrix4::lookAt(position, position + forward, up);
  inverseViewMatrix = Matrix4::inverse(viewMatrix);
  return shared_from_this();
}

std::shared_ptr<FreeCamera> FreeCamera::setPosition(Vector3 _position) {
  position = _position;

  viewMatrix = Matrix4::lookAt(position, position + forward, up);
  inverseViewMatrix = Matrix4::inverse(viewMatrix);
  return shared_from_this();
}

std::shared_ptr<FreeCamera> FreeCamera::setRotation(float roll, float pitch, float yaw) {
  rotation = Quaternion::fromEuler(roll, pitch, yaw);
  forward = rotation * Vector3(0.0f, 0.0f, -1.0f);  // Camera forward is -Z
  up = rotation * Vector3(0.0f, 1.0f, 0.0f);
  right = rotation * Vector3(1.0f, 0.0f, 0.0f);

  viewMatrix = Matrix4::lookAt(position, position + forward, up);
  inverseViewMatrix = Matrix4::inverse(viewMatrix);
  return shared_from_this();
}

std::shared_ptr<FreeCamera> FreeCamera::setRotation(Quaternion _rotation) {
  rotation = _rotation;
  forward = rotation * Vector3(0.0f, 0.0f, -1.0f);  // Camera forward is -Z
  up = rotation * Vector3(0.0f, 1.0f, 0.0f);
  right = rotation * Vector3(1.0f, 0.0f, 0.0f);

  viewMatrix = Matrix4::lookAt(position, position + forward, up);
  inverseViewMatrix = Matrix4::inverse(viewMatrix);
  return shared_from_this();
}
