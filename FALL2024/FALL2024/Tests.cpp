#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <string>
#include <Windows.h>

#include "Tests.h"
#include "Node.h"

constexpr float M_PI = 3.1416;

// Helper function to compare floats with a small epsilon
bool approxEqual(float a, float b, float epsilon = 0.0001f) {
    return std::fabs(a - b) < epsilon;
}

// Helper function to compare Vector3
bool approxEqualVector3(const Vector3& a, const Vector3& b, float epsilon = 0.0001f) {
    return approxEqual(a.x, b.x, epsilon) &&
        approxEqual(a.y, b.y, epsilon) &&
        approxEqual(a.z, b.z, epsilon);
}

void expectEqual(float expected, float actual, const std::string& message) {
    if (!approxEqual(expected, actual)) {
        throw std::runtime_error(message + " Expected: " + std::to_string(expected) + ", Actual: " + std::to_string(actual));
    }
}

void expectEqualVector3(const Vector3& expected, const Vector3& actual, const std::string& message) {
    if (!approxEqualVector3(expected, actual)) {
        throw std::runtime_error(message + " Expected: (" + std::to_string(expected.x) + ", " + std::to_string(expected.y) + ", " + std::to_string(expected.z) +
            "), Actual: (" + std::to_string(actual.x) + ", " + std::to_string(actual.y) + ", " + std::to_string(actual.z) + ")");
    }
}

void testMatrixMultiplication() {
    Matrix4 m1, m2;

    // Set up test matrices
    m1.updateElement(0, 0, 1); m1.updateElement(0, 1, 2); m1.updateElement(0, 2, 3); m1.updateElement(0, 3, 4);
    m1.updateElement(1, 0, 5); m1.updateElement(1, 1, 6); m1.updateElement(1, 2, 7); m1.updateElement(1, 3, 8);
    m1.updateElement(2, 0, 9); m1.updateElement(2, 1, 10); m1.updateElement(2, 2, 11); m1.updateElement(2, 3, 12);
    m1.updateElement(3, 0, 13); m1.updateElement(3, 1, 14); m1.updateElement(3, 2, 15); m1.updateElement(3, 3, 16);

    m2.updateElement(0, 0, 17); m2.updateElement(0, 1, 18); m2.updateElement(0, 2, 19); m2.updateElement(0, 3, 20);
    m2.updateElement(1, 0, 21); m2.updateElement(1, 1, 22); m2.updateElement(1, 2, 23); m2.updateElement(1, 3, 24);
    m2.updateElement(2, 0, 25); m2.updateElement(2, 1, 26); m2.updateElement(2, 2, 27); m2.updateElement(2, 3, 28);
    m2.updateElement(3, 0, 29); m2.updateElement(3, 1, 30); m2.updateElement(3, 2, 31); m2.updateElement(3, 3, 32);

    Matrix4 result = m1 * m2;

    expectEqual(250, result.getElement(0, 0), "Matrix multiplication failed at (0,0)");
    expectEqual(644, result.getElement(1, 1), "Matrix multiplication failed at (1,1)");
    expectEqual(1070, result.getElement(2, 2), "Matrix multiplication failed at (2,2)");
    expectEqual(1528, result.getElement(3, 3), "Matrix multiplication failed at (3,3)");
}

void testVectorTransformation() {
    Matrix4 m;
    m.updateElement(0, 0, 1); m.updateElement(0, 1, 0); m.updateElement(0, 2, 0); m.updateElement(0, 3, 5);
    m.updateElement(1, 0, 0); m.updateElement(1, 1, 1); m.updateElement(1, 2, 0); m.updateElement(1, 3, 0);
    m.updateElement(2, 0, 0); m.updateElement(2, 1, 0); m.updateElement(2, 2, 1); m.updateElement(2, 3, 0);
    m.updateElement(3, 0, 0); m.updateElement(3, 1, 0); m.updateElement(3, 2, 0); m.updateElement(3, 3, 1);

    Vector3 v(1, 1, 0);
    Vector3 result = m * v;

    expectEqualVector3(Vector3(6, 1, 0), result, "Vector transformation failed");
}

void testTranslationMatrix() {
    Matrix4 trans = Matrix4::translation(2, 3, 4);
    Vector3 v(1, 1, 1);
    Vector3 result = trans * v;

    expectEqualVector3(Vector3(3, 4, 5), result, "Translation matrix failed");
}

void testScaleMatrix() {
    Matrix4 scale = Matrix4::scale(2, 3, 4);
    Vector3 v(1, 1, 1);
    Vector3 result = scale * v;

    expectEqualVector3(Vector3(2, 3, 4), result, "Scale matrix failed");
}

void testRotationMatrices() {
    // Test rotation around X-axis
    Matrix4 rotX = Matrix4::rotationX(M_PI / 2); // 90 degrees
    Vector3 v(0, 1, 0);
    Vector3 result = rotX * v;

    expectEqualVector3(Vector3(0, 0, 1), result, "Rotation X matrix failed");

    // Test rotation around Y-axis
    Matrix4 rotY = Matrix4::rotationY(M_PI / 2); // 90 degrees
    v = Vector3(1, 0, 0);
    result = rotY * v;

    expectEqualVector3(Vector3(0, 0, -1), result, "Rotation Y matrix failed");

    // Test rotation around Z-axis
    Matrix4 rotZ = Matrix4::rotationZ(M_PI / 2); // 90 degrees
    v = Vector3(1, 0, 0);
    result = rotZ * v;

    expectEqualVector3(Vector3(0, 1, 0), result, "Rotation Z matrix failed");
}

void runTest(void (*testFunction)(), const std::string& testName) {
    try {
        testFunction();
        std::cout << "PASSED: " << testName << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "FAILED: " << testName << " - " << e.what() << std::endl;
    }
}

void runTests() {
    std::vector<std::pair<void (*)(), std::string>> tests = {
        {testMatrixMultiplication, "Matrix Multiplication"},
        {testVectorTransformation, "Vector Transformation"},
        {testTranslationMatrix, "Translation Matrix"},
        {testScaleMatrix, "Scale Matrix"},
        {testRotationMatrices, "Rotation Matrices"}
    };

    int passedTests = 0;
    for (const auto& test : tests) {
        runTest(test.first, test.second);
        passedTests++;
    }

    std::cout << "\nTest summary: " << passedTests << " out of " << tests.size() << " tests passed." << std::endl;
}

void runMainLoopTest() {
    Vector3 position{ 0.0f, 0.0f, 0.0f };
    Vector3 direction{ 10.0f, 0.0f, 0.0f };

    Matrix4 translate = Matrix4::translation(5.0f, 0.0f, 0.0f);
    Matrix4 rotation = Matrix4::rotationZ(M_PI * 0.25f);

    std::cout << direction << std::endl;
    // Infinite loop
    while (true)
    {
        position = translate * position;
        Sleep(700);
        if (position.x >= 50.0f)
            break;
        std::cout << position << std::endl;

        direction = rotation * direction;
        std::cout << direction << std::endl;
        Sleep(700);
        if (direction.y <= 0.0f && direction.x >= 0.0f)
            break;
    }
}

void testNodeObjects() {
    // test with the table example
    // root
    //  - table
    //      - pyramid
    //      - cylinder
    //  - table2
    //      - block1
    //          - block1_0
    //          - block1_1
    //          - block1_2
    //          - block1_3
    auto root = std::make_shared<Node>("root");
    auto table = std::make_shared<Node>("table");
    auto pyramid = std::make_shared<Node>("pyramid");
    auto cylinder = std::make_shared<Node>("cylinder");
    auto table2 = std::make_shared<Node>("table2");
    auto block1 = std::make_shared<Node>("block1");
    auto block1_0 = std::make_shared<Node>("block1_0");
    auto block1_1 = std::make_shared<Node>("block1_1");
    auto block1_2 = std::make_shared<Node>("block1_2");
    auto block1_3 = std::make_shared<Node>("block1_3");


    root->addChild(table);
    table->addChild(pyramid);
    table->addChild(cylinder);
    root->addChild(table2);
    table2->addChild(block1);
    block1->addChild(block1_0);
    block1->addChild(block1_1);
    block1->addChild(block1_2);
    block1->addChild(block1_3);

    std::cout << "Root has " << root->getChildren().size() << " children\n";
    //std::cout << "Table has " << table->getChildren().size() << " children\n";
    //std::cout << "Pyramid's parent is " << pyramid->getParent()->getName() << "\n";
    //std::cout << "Cylinder's parent is " << cylinder->getParent()->getName() << "\n";


    // find node
    auto detached = std::make_shared<Node>("NonSibling");

    if (!root->findNodeFast(cylinder))
        std::cout << "error finding cylinder\n";
    if (!root->findNodeFast(pyramid))
        std::cout << "error finding pyramid\n";
    if (!root->findNodeFast(table))
        std::cout << "error finding table\n";
    std::cout << "table uses: " << table.use_count() << std::endl;
    if (!root->findNodeFast(root))
        std::cout << "error finding root\n";
    if (!root->findNodeFast(detached))
        std::cout << "error finding detached\n";

    // detach node
    table->reparent(block1_0);
    std::cout << "After reparenting table:\n";
    std::cout << *root << std::endl;

    block1->reparent(root);
    std::cout << "After reparenting block1:\n";
    std::cout << *root << std::endl;

    // remove node
    std::cout << "Complete tree:\n";
    std::cout << *root << std::endl;
    root->removeNode(table);
    //std::cout << "table uses: " << table.use_count() << std::endl;
    std::cout << "After removal of table:\n";
    std::cout << *root << std::endl;
    root->removeNode(cylinder);
    //std::cout << "table uses: " << table.use_count() << std::endl;
    std::cout << "After removal of cylinder:\n";
    std::cout << *root << std::endl;
    root->removeNode(pyramid);
    //std::cout << "table uses: " << table.use_count() << std::endl;
    std::cout << "After removal of pyramid:\n";
    std::cout << *root << std::endl;

    

    return;
}