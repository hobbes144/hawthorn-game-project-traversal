/*!****************************************************************************
 * \file   Camera.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par    **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par    **Course**
 *    CS529
 * \date   12-14-2024
 * 
 *****************************************************************************/

#include "Camera.h"

/* Private functions */

 /*!****************************************************************************
  * \brief Update the view matrix based on the location of the camera
  *
  * ## Explanation:
  *
  * The view matrix is always calculated as the same rotation of the camera, but
  * with the negative of the position of the camera. This ensures that all
  * objects in front of the camera are moved to the relative position from the
  * world origin.
  *
  *****************************************************************************/
void Camera::updateViewMatrix() {
  Vector3 position = getLocalPosition();

  // Compute rotation matrix from Node's rotation angles
  Matrix4 rotationMatrix = Matrix4::rotationXYZ(getLocalRotation());

  // Extract basis vectors (Right, Up, Forward)
  Vector3 right = rotationMatrix * Vector3(1.0f, 0.0f, 0.0f);
  Vector3 up = rotationMatrix * Vector3(0.0f, 1.0f, 0.0f);
  Vector3 forward = rotationMatrix * Vector3(0.0f, 0.0f, -1.0f);  // Camera forward is -Z

  // Compute view matrix using LookAt
  viewMatrix = Matrix4::lookAt(position, position + forward, up);
}



/* Public functions */

/*!****************************************************************************
 * \brief Set the projection matrix to a perspective transformation
 * 
 * ## Usage:
 * 
 * Call this function when the camera needs to be a perspectiv view.
 * 
 * \param fov FOV of the camera
 * \param aspectRatio Aspect Ratio of the camera
 * \param near Near plane of the camera
 * \param far Far plane of the camera
 * \return \b std::shared_ptr<Camera> Self shared pointer to allow chaining.
 *****************************************************************************/
std::shared_ptr<Camera> Camera::setPerspectiveProjection(
  const float fov,
  const float aspectRatio,
  const float near,
  const float far)
{
  projectionMatrix = Matrix4::perspective(fov, aspectRatio, near, far);

  return std::static_pointer_cast<Camera>(shared_from_this());
}

/*!****************************************************************************
 * \brief Set the projection matrix to an orthographic transformation
 * 
 * ## Usage:
 * 
 * Call this function when the camera needs to be an orthographic view.
 * 
 * \param left Left extent of the view
 * \param right Right extent of the view
 * \param bottom Bottom extent of the view
 * \param top Top extent of the view
 * \param near Near plane of the camera
 * \param far Far plane of the camera
 * \return \b std::shared_ptr<Camera> Self shared pointer to allow chaining.
 *****************************************************************************/
std::shared_ptr<Camera> Camera::setOrthographicProjection(
  const float left,
  const float right,
  const float bottom,
  const float top,
  const float near,
  const float far)
{
  projectionMatrix = Matrix4::orthographic(
    left, right, bottom, top, near, far
  );

  return std::static_pointer_cast<Camera>(shared_from_this());
}

std::shared_ptr<Camera> Camera::lookAt(const Vector3& target, const Vector3& upVector = Vector3(0,1,0)) {
  viewMatrix = Matrix4::lookAt(getLocalPosition(), target, upVector);
  return std::static_pointer_cast<Camera>( shared_from_this() );
}

std::shared_ptr<Camera> Camera::move(const Vector3 & direction, float amount) {
  setLocalPosition(getLocalPosition() + (direction * amount));
  return std::static_pointer_cast<Camera>( shared_from_this() );
}

std::shared_ptr<Camera> Camera::rotate(float roll, float pitch, float yaw) {
  setLocalRotation(getLocalRotation() + Vector3(roll, pitch, yaw));
  return std::static_pointer_cast<Camera>( shared_from_this() );
}

/*!****************************************************************************
 * \brief Get the view matrix
 * 
 * ## Usage:
 * 
 * This allows us to get the view matrix. Primarily meant for use with render
 * component draw calls.
 * 
 * \return \b View matrix
 *****************************************************************************/
const Matrix4 Camera::getViewMatrix()
{
  return viewMatrix;
}

/*!****************************************************************************
 * \brief Get the projection matrix
 * 
 * ## Usage:
 * 
 * This allows us to get the projection matrix. Primarily meant for use with render
 * component draw calls.
 * 
 * \return \b Projection matrix
 *****************************************************************************/
const Matrix4& Camera::getProjectionMatrix()
{
  return projectionMatrix;
}

/*!****************************************************************************
 * \brief Dummy initialize function
 * 
 *****************************************************************************/
void Camera::initialize() {
  updateViewMatrix();
}

/*!****************************************************************************
 * \brief Update the camera transforms
 * 
 * ## Usage:
 * 
 * This must be called after making changes to the camera's transforms to make
 * sure that viewMatrix is correctly updated.
 * 
 * \param deltaTime
 *****************************************************************************/
void Camera::update(float deltaTime) {
  GameObject::update(deltaTime);

  updateViewMatrix();
}

/*!****************************************************************************
 * \brief Dummy shutdown function
 * 
 *****************************************************************************/
void Camera::shutdown() {}
