/*!****************************************************************************
 * \file   Transform.h
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   10-15-2024
 * \brief  Transform object, used to store the rotation, scale and translation
 * info of an object, along with providing operations on the same.
 * 
 *****************************************************************************/
#ifndef TRANSFORM_H
#define TRANSFORM_H

#pragma once

#include "Matrix4.h"
#include "Vector3.h"

class Transform {
public:
  Transform() : position(0, 0, 0), rotation(0, 0, 0), scaling(1, 1, 1) {}

  Vector3 getPosition() const { return position; }
  Vector3 getRotation() const { return rotation; }
  Vector3 getScaling() const { return scaling; }

  void setPosition(const Vector3& newPosition) { position = newPosition; }
  void setRotation(const Vector3& newRotation) { rotation = newRotation; }
  void setScaling(const Vector3& newScaling) { scaling = newScaling; }

  Matrix4 getLocalMatrix() const {
    return Matrix4::translation(position) *
      Matrix4::rotationXYZ(rotation) *
      Matrix4::scale(scaling);
  }

  Matrix4 getInverseLocalMatrix() const {
    Vector3 invTranslation(-position.x, -position.y, -position.z);
    Vector3 invRotation(-rotation.x, -rotation.y, -rotation.z);
    Vector3 invScaling(1.0f / scaling.x, 1.0f / scaling.y, 1.0f / scaling.z);

    return Matrix4::scale(invScaling) *
      Matrix4::rotationXYZ(invRotation) *
      Matrix4::translation(invTranslation);
  }

  void translate(const Vector3& translation) { 
    position = position + translation;
  }
  void rotate(const Vector3 rotationDelta) { 
    rotation = rotation + rotationDelta;
  }
  void scale(const Vector3& scaleMult) {
    scaling = scaling * scaleMult;
  }

private:
  Vector3 position;
  Vector3 rotation;
  Vector3 scaling;

};

#endif // TRANSFORM_H
