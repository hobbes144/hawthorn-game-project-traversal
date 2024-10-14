#pragma once
#include "Vector3.h"
#include "Matrix4.h"

class Transform {
public:
    Transform();

    // Position methods
    void setPosition(const Vector3& newPosition);
    const Vector3& getPosition() const;

    // Rotation methods (using Euler angles in radians)
    void setRotation(const Vector3& newRotation);
    const Vector3& getRotation() const;

    // Scale methods
    void setScale(const Vector3& newScale);
    const Vector3& getScale() const;

    // Get the model matrix
    Matrix4 getLocalMatrix();
    Matrix4 getInverseLocalMatrix();

    // Utility methods
    void translate(const Vector3& translation);
    void rotate(const Vector3& rotationDelta);
    void scale(const Vector3& scaling);

private:
    Vector3 position;
    Vector3 rotation;
    Vector3 scaling;

};