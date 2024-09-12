#include "Matrix4.h"

Matrix4::Matrix4()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = i == j ? 1.0f : 0.0f;
        }
    }
}

Matrix4::Matrix4(float x0, float y0, float z0, float w0, float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3)
{
    data[0][0] = x0;
    data[0][1] = x1;
    data[0][2] = x2;
    data[0][3] = x3;
    data[1][0] = y0;
    data[1][1] = y1;
    data[1][2] = y2;
    data[1][3] = y3;
    data[2][0] = z0;
    data[2][1] = z1;
    data[2][2] = z2;
    data[2][3] = z3;
    data[3][0] = w0;
    data[3][1] = w1;
    data[3][2] = w2;
    data[3][3] = w3;
}

void Matrix4::updateElement(int row, int col, float value)
{
    data[row][col] = value;
}

float Matrix4::getElement(int row, int col) const
{
    return data[row][col];
}

Matrix4 Matrix4::operator*(const Matrix4& other)
{
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.updateElement(i, j, 0.0f);
            for (int k = 0; k < 4; k++) {
                result.updateElement(i, j, result.getElement(i, j) + data[i][k] * other.getElement(k, j));
            }
        }
    }
	
    return result;
}

Vector3 Matrix4::operator*(const Vector3& vec) const
{
	float x,y,z;
    x = vec.x * data[0][0] + vec.y * data[0][1] + vec.z * data[0][2] + 1 * data[0][3];
    y = vec.x * data[1][0] + vec.y * data[1][1] + vec.z * data[1][2] + 1 * data[1][3];
    z = vec.x * data[2][0] + vec.y * data[2][1] + vec.z * data[2][2] + 1 * data[2][3];

    return Vector3(x, y, z);
}

Matrix4 Matrix4::translation(float tx, float ty, float tz)
{
    Matrix4 result;
    result.data[0][0] = 1;
    result.data[0][3] = tx;
    result.data[1][1] = 1;
    result.data[1][3] = ty;
    result.data[2][2] = 1.0f;
    result.data[2][3] = tz;
    result.data[3][3] = 1.0f;

    return result;
}

Matrix4 Matrix4::scale(float sx, float sy, float sz)
{
    Matrix4 result;
    result.data[0][0] = sx;
    result.data[1][1] = sy;
    result.data[2][2] = sz;
    result.data[3][3] = 1.0f;
	
    return result;
}

const float pi = 3.14159f;
Matrix4 Matrix4::rotationX(float angle)
{
    Matrix4 result;
    result.data[1][1] = cos(angle);
    result.data[1][2] = -sin(angle);
    result.data[2][1] = sin(angle);
    result.data[2][2] = cos(angle);
	
    return result;
}

Matrix4 Matrix4::rotationY(float angle)
{
    Matrix4 result;
    result.data[0][2] = sin(angle);
    result.data[0][0] = cos(angle);
    result.data[2][2] = cos(angle);
    result.data[2][0] = -sin(angle);
	
    return result;
}

Matrix4 Matrix4::rotationZ(float angle)
{
    Matrix4 result;
    result.data[0][0]= cos(angle);
    result.data[0][1]=-sin(angle);
    result.data[1][0]= sin(angle);
    result.data[1][1]= cos(angle);
	
    return result;
}