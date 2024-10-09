/*!****************************************************************************
 * \file Matrix4.cpp
 * \author Anish Murthy (anish.murthy.dev@gmail.com)
 * \par **DigiPen Email**
 *    anish.murthy@digipen.edu
 * \par **Course**
 *    CS525
 * \version 0.1
 * \date 10-05-2024
 *****************************************************************************/
#include "Matrix4.h"

/*!****************************************************************************
 * \brief Construct a new Matrix 4:: Matrix 4 object
 *
 *****************************************************************************/
Matrix4::Matrix4()
{
  data[0][0] = 1.0f;
  data[0][1] = 0.0f;
  data[0][2] = 0.0f;
  data[0][3] = 0.0f;
  data[1][0] = 0.0f;
  data[1][1] = 1.0f;
  data[1][2] = 0.0f;
  data[1][3] = 0.0f;
  data[2][0] = 0.0f;
  data[2][1] = 0.0f;
  data[2][2] = 1.0f;
  data[2][3] = 0.0f;
  data[3][0] = 0.0f;
  data[3][1] = 0.0f;
  data[3][2] = 0.0f;
  data[3][3] = 1.0f;
}

/*!****************************************************************************
 * \brief Construct a new Matrix 4:: Matrix 4 object
 *
 * \param x0
 * \param y0
 * \param z0
 * \param w0
 * \param x1
 * \param y1
 * \param z1
 * \param w1
 * \param x2
 * \param y2
 * \param z2
 * \param w2
 * \param x3
 * \param y3
 * \param z3
 * \param w3
 *****************************************************************************/
Matrix4::Matrix4(
    float x0, float y0, float z0, float w0,
    float x1, float y1, float z1, float w1,
    float x2, float y2, float z2, float w2,
    float x3, float y3, float z3, float w3)
{
  data[0][0] = x0;
  data[0][1] = y0;
  data[0][2] = z0;
  data[0][3] = w0;
  data[1][0] = x1;
  data[1][1] = y1;
  data[1][2] = z1;
  data[1][3] = w1;
  data[2][0] = x2;
  data[2][1] = y2;
  data[2][2] = z2;
  data[2][3] = w2;
  data[3][0] = x3;
  data[3][1] = y3;
  data[3][2] = z3;
  data[3][3] = w3;
}

/*!****************************************************************************
 * \brief Getter for the address to the Matrix's data for use with GL code
 *
 * \return \b float* Address of the Matrix data.
 *****************************************************************************/
float *Matrix4::getData()
{
  return &data[0][0];
}

/*!****************************************************************************
 * \brief Setter for specific elements in the Matrix
 *
 * \param row Row of the element.
 * \param col Column of the element.
 * \param value Value of the element.
 *****************************************************************************/
void Matrix4::updateElement(int row, int col, float value)
{
  data[row][col] = value;
}

/*!****************************************************************************
 * \brief Getter for specific elements in the Matrix
 *
 * \param row Row of the element.
 * \param col Column of the element.
 * \return \b float Value of the element.
 *****************************************************************************/
float Matrix4::getElement(int row, int col) const
{
  return data[row][col];
}

/*!****************************************************************************
 * \brief * Operator overloader for Matrix4 multiplication
 *
 * \param other Matrix4 object to be multiplied with.
 * \return \b Matrix4 The result of the multiplication.
 *****************************************************************************/
Matrix4 Matrix4::operator*(const Matrix4 &other)
{
  Matrix4 result;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      result.updateElement(i, j, 0.0f);
      for (int k = 0; k < 4; k++)
      {
        result.updateElement(i, j, result.getElement(i, j) + data[i][k] * other.getElement(k, j));
      }
    }
  }

  return result;
}

/*!****************************************************************************
 * \brief * Operator overloader for Vector3 multiplication
 *
 * \param vec Vector3 object to be multiplied with.
 * \return \b Vector3 The result of the multiplication.
 *****************************************************************************/
Vector3 Matrix4::operator*(const Vector3 &vec) const
{
  float x, y, z;
  x = vec.x * data[0][0] + vec.y * data[0][1] + vec.z * data[0][2] + 1 * data[0][3];
  y = vec.x * data[1][0] + vec.y * data[1][1] + vec.z * data[1][2] + 1 * data[1][3];
  z = vec.x * data[2][0] + vec.y * data[2][1] + vec.z * data[2][2] + 1 * data[2][3];

  return Vector3(x, y, z);
}

/*!****************************************************************************
 * \brief Static function to create a Translation matrix
 *
 * \param tx Translation in the x axis.
 * \param ty Translation in the y axis.
 * \param tz Translation in the z axis.
 * \return \b Matrix4 The resulting Translation matrix.
 *****************************************************************************/
Matrix4 Matrix4::translation(float tx, float ty, float tz)
{
  Matrix4 result = Matrix4(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    tx, ty, tz, 1.0f);

  return result;
}

/*!****************************************************************************
 * \brief Static function to create a Scaling matrix
 *
 * \param sx Scaling in the x axis.
 * \param sy Scaling in the y axis.
 * \param sz Scaling in the z axis.
 * \return \b Matrix4 The resulting Scaling matrix.
 *****************************************************************************/
Matrix4 Matrix4::scale(float sx, float sy, float sz)
{
  Matrix4 result = Matrix4(
    sx,   0.0f, 0.0f, 0.0f,
    0.0f, sy,   0.0f, 0.0f,
    0.0f, 0.0f, sz,   0.0f,
    0.0f, 0.0f, 0.0f, 1.0f);

  return result;
}

/** Pi constant for maths */
const float pi = 3.14159f;

/*!****************************************************************************
 * \brief Static function to create a Rotation matrix in the x axis
 *
 * \param angle Angle of rotation in the x axis.
 * \return \b Matrix4 The resulting Rotation matrix.
 *****************************************************************************/
Matrix4 Matrix4::rotationX(float angle)
{
  Matrix4 result = Matrix4(
    1.0f, 0.0f,       0.0f,       0.0f,
    0.0f, cos(angle), sin(angle), 0.0f,
    0.0f,-sin(angle), cos(angle), 0.0f,
    0.0f, 0.0f,       0.0f,       1.0f);

  return result;
}

/*!****************************************************************************
 * \brief Static function to create a Rotation matrix in the y axis
 *
 * \param angle Angle of rotation in the y axis.
 * \return \b Matrix4 The resulting Rotation matrix.
 *****************************************************************************/
Matrix4 Matrix4::rotationY(float angle)
{
  Matrix4 result = Matrix4(
    cos(angle), 0.0f,-sin(angle), 0.0f,
    0.0f,       1.0f, 0.0f,       0.0f,
    sin(angle), 0.0f, cos(angle), 0.0f,
    0.0f,       0.0f, 0.0f,       1.0);

  return result;
}

/*!****************************************************************************
 * \brief Static function to create a Rotation matrix in the z axis
 *
 * \param angle Angle of rotation in the z axis.
 * \return \b Matrix4 The resulting Rotation matrix.
 *****************************************************************************/
Matrix4 Matrix4::rotationZ(float angle)
{
  Matrix4 result = Matrix4(
    cos(angle),   sin(angle), 0.0f, 0.0f,
   -sin(angle),   cos(angle), 0.0f, 0.0f,
    0.0f,         0.0f,       1.0f, 0.0f,
    0.0f,         0.0f,       0.0f, 1.0f);

  return result;
}

/*!****************************************************************************
 * \brief Static function to create an Orthographic projection matrix
 *
 * \param left Leftmost position in the world to be projected.
 * \param right Rightmost position in the world to be projected.
 * \param bottom Bottommost position in the world to be projected.
 * \param top Topmost position in the world to be projected.
 * \param near Near plane of the projection.
 * \param far Far plane of the projection.
 * \return \b Matrix4 The resulting Orthographic projection matrix.
 *****************************************************************************/
Matrix4 Matrix4::orthographic(
    const float left,
    const float right,
    const float bottom,
    const float top,
    const float near,
    const float far)
{
  Matrix4 result;
  result.data[0][0] = 2.0f / (right - left);
  result.data[1][1] = 2.0f / (top - bottom);
  result.data[2][2] = -2.0f / (far - near);
  result.data[0][3] = -(right + left) / (right - left);
  result.data[1][3] = -(top + bottom) / (top - bottom);
  result.data[2][3] = -(far + near) / (far - near);
  result.data[3][3] = 1.0f;
  return result;
}

/*!****************************************************************************
 * \brief Static function to create a Perspective projection matrix
 *
 * \param fov FOV of the camera.
 * \param aspectRatio Aspect ratio of the screen to be projected on.
 * \param near Near plane of the projection.
 * \param far Far plane of the projection.
 * \return \b Matrix4 The resulting Perspective projection matrix.
 *****************************************************************************/
Matrix4 Matrix4::perspective(const float fov, const float aspectRatio,
                             const float near, const float far)
{
  float tanHalfFov = tan(fov / 2.0f);
    
  Matrix4 result = Matrix4(
    1.0f / (aspectRatio * tanHalfFov),  0.0f,               0.0f,                               0.0f,
    0.0f,                               1.0f / tanHalfFov,  0.0f,                               0.0f,
    0.0f,                               0.0f,              -(far + near) / (far - near),       -1.0f,
    0.0f,                               0.0f,              -(2.0f * far * near) / (far - near), 0.0f);

  return result;
}

/*!****************************************************************************
 * \brief Static function to generate a Viewing matrix to setup the eye
 *
 * \param eye Eye position.
 * \param center Position in the world to be centered on.
 * \param up Up vector to help determine camera orientation.
 * \return \b Matrix4 The resulting Viewing matrix.
 *****************************************************************************/
Matrix4 Matrix4::lookAt(const Vector3 &eye, const Vector3 &center,
                        const Vector3 &up)
{
  Vector3 f = (eye - center).normalized();
  Vector3 s = f.cross(up).normalized();
  Vector3 u = s.cross(f).normalized();

  Matrix4 result = Matrix4(
    s.x,          u.x,        f.x,        0.0f,
    s.y,          u.y,        f.y,        0.0f,
    s.z,          u.z,        f.z,        0.0f,
   -s.dot(eye),  -u.dot(eye),-f.dot(eye), 1.0f);

  return result;
}