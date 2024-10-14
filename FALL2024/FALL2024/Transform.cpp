#include "Transform.h"

Transform::Transform()
    : position(0, 0, 0), rotation(0, 0, 0), scaling(1, 1, 1) {}

void Transform::setPosition(const Vector3& newPosition) {
    position = newPosition;
}

const Vector3& Transform::getPosition() const {
    return position;
}

void Transform::setRotation(const Vector3& newRotation) {
    rotation = newRotation;
}

const Vector3& Transform::getRotation() const {
    return rotation;
}

void Transform::setScale(const Vector3& newScale) {
    scaling = newScale;
}

const Vector3& Transform::getScale() const {
    return scaling;
}

void Transform::translate(const Vector3& translation) {
    position = position + translation;
}

void Transform::rotate(const Vector3& rotationDelta) {
    rotation = rotation + rotationDelta;
}

void Transform::scale(const Vector3& scale) {
    scaling.x = scaling.x * scale.x;
    scaling.y = scaling.y * scale.y;
    scaling.z = scaling.z * scale.z;
}


Matrix4 Transform::getLocalMatrix(){
    Matrix4 translationMatrix = Matrix4::translation(position.x, position.y, position.z);
    Matrix4 rotationMatrix = Matrix4::rotationXYZ(rotation.x, rotation.y, rotation.z);
    Matrix4 scaleMatrix = Matrix4::scale(scaling.x, scaling.y, scaling.z);
    return translationMatrix * rotationMatrix * scaleMatrix;
}

Matrix4 Transform::getInverseLocalMatrix() {
    // Invert scale
    Vector3 invScale(1.0f / scaling.x, 1.0f / scaling.y, 1.0f / scaling.z);

    // Invert rotation (negative angles)
    Vector3 invRotation(-rotation.x, -rotation.y, -rotation.z);

    // Invert translation
    Vector3 invTranslation(-position.x, -position.y, -position.z);

    // Combine in reverse order
    Matrix4 invScaleMatrix = Matrix4::scale(invScale.x, invScale.y, invScale.z);
    Matrix4 invRotationMatrix = Matrix4::rotationXYZ(invRotation.x, invRotation.y, invRotation.z);
    Matrix4 invTranslationMatrix = Matrix4::translation(invTranslation.x, invTranslation.y, invTranslation.z);

    return invScaleMatrix * invRotationMatrix * invTranslationMatrix;
}
