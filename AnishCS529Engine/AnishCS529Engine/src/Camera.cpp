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
#include "precompiled.h"

#include "Camera.h"


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
void Camera::setPerspectiveProjection(
  const float fov,
  const float aspectRatio,
  const float near,
  const float far)
{
  projectionMatrix = Matrix4::perspective(fov, aspectRatio, near, far);

  return;
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
void Camera::setOrthographicProjection(
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

  return;
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
const Matrix4& Camera::getViewMatrix()
{
  return viewMatrix;
}

const Matrix4& Camera::getInverseViewMatrix()
{
  return inverseViewMatrix;
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
