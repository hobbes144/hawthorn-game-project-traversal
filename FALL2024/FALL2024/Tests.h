#pragma once

#include "Vector3.h"
#include "Matrix4.h"

// Helper function to compare floats with a small epsilon
bool approxEqual(float a, float b, float epsilon);

// Helper function to compare Vector3
bool approxEqualVector3(const Vector3& a, const Vector3& b, float epsilon);

void expectEqual(float expected, float actual, const std::string& message);

void expectEqualVector3(const Vector3& expected, const Vector3& actual, const std::string& message);

void testMatrixMultiplication();

void testVectorTransformation();

void testTranslationMatrix();

void testScaleMatrix();

void testRotationMatrices();

void runTest(void (*testFunction)(), const std::string& testName);

void runMainLoopTest();

void testNodeObjects();