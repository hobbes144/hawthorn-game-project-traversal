//#include "Renderer.h"
//#include "GameWindow.h"
//#include <iostream>
//#include <chrono>
//#include <thread>
//#include "Tests.h"
//
//int main() {
//
//    //testNodeObjects();
//
//    try {
//        GameWindow window(800, 600, "OpenGL Window");
//        Renderer renderer(window);
//
//        float angle = 0.0f;
//        float scaleAmount = 10.0f;
//        float scaleSpeed = 20.0f;
//
//        while (!window.shouldClose()) {
//            window.pollEvents();
//
//            renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);
//            // Render your 3D scene here
//            
//            // Update transformations
//            angle += 0.01f;
//            scaleAmount = 1.0f + 0.5f * std::sin(scaleSpeed * glfwGetTime());
//            
//            //std::this_thread::sleep_for(std::chrono::milliseconds(500));
//            // Create model matrix with all transformations
//            Matrix4 translation = Matrix4::translation(angle, 0.0f, 0.0f);
//            Matrix4 rotation = Matrix4::rotationY(angle*-10);
//            Matrix4 scale = Matrix4::scale(scaleAmount, scaleAmount, scaleAmount);
//            
//            Matrix4 modelMatrix = rotation;//rotation * scale;
//            
//            Vector3 v1(-0.5f, -0.5f, 0.0f);
//            Vector3 v2(0.5f, -0.5f, 0.0f);
//            Vector3 v3(0.0f, 0.5f, 0.0f);
//
//            renderer.drawTriangle(v1, v2, v3, modelMatrix);
//
//            GLenum error = glGetError();
//            if (error != GL_NO_ERROR) {
//                std::cout << "OpenGL error: " << error << std::endl;
//            }
//
//            renderer.swapBuffers();
//        }
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//        return -1;
//    }
//
//    return 0;
//}

#include <iostream>
#include <memory>
#include <vector>
#include "Renderer.h"
#include "GameWindow.h"
#include "SceneGraph.h"
#include "RenderableNode.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "TrianglePrimitive.h"

int main() {
    try {
        // Create window and renderer
        GameWindow window(800, 600, "Triangle Rotation Test");
        Renderer renderer(window);

        // Create scene graph
        SceneGraph sceneGraph;

        // Create 3 triangles in different positions
        auto triangle1 = std::make_shared<TrianglePrimitive>("RedTriangle", &renderer);
        triangle1->setColor(Vector3(1.0f, 0.0f, 0.0f));
        triangle1->setLocalPosition(Vector3(-1.0f, 0.0f, 0.0f));
        triangle1->setLocalScale(Vector3(0.5f, 0.5f, 0.5f));
        sceneGraph.addNode(triangle1);

        auto triangle2 = std::make_shared<TrianglePrimitive>("GreenTriangle", &renderer);
        triangle2->setColor(Vector3(0.0f, 1.0f, 0.0f));
        triangle2->setLocalPosition(Vector3(1.0f, 0.0f, 0.0f));
        triangle2->setLocalScale(Vector3(0.5f, 0.5f, 0.5f));
        sceneGraph.addNode(triangle2);

        /*auto triangle3 = std::make_shared<TrianglePrimitive>("BlueTriangle", &renderer);
        triangle1->setColor(Vector3(0.0f, 0.0f, 1.0f));
        triangle3->setPosition(Vector3(1.0f, 0.0f, 0.0f));
        sceneGraph.addNode(triangle3);*/

        // TODO: complete the main!
        

        // Set up camera (view and projection matrices)
        Vector3 cameraPos(0.0f, 0.0f, 2.0);
        Vector3 cameraTarget = cameraPos + Vector3(0.0f, 0.0f, -1.0f);
        Vector3 upVector(0.0f, 1.0f, 0.0f);
        Matrix4 viewMatrix = Matrix4::lookAt(cameraPos, cameraTarget, upVector);
        float aspectRatio = static_cast<float>(window.getWidth()) / window.getHeight();
        Matrix4 projectionMatrix = Matrix4::perspective(45.0f * 3.14159f / 180.0f, aspectRatio, 0.1f, 100.0f);

        // Main loop
        float rotationAngle = 0.0f;
        float deltaTime = 1.0f / 60.0f; // Assume 60 FPS
        while (!window.shouldClose()) {
            renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);

            // Update rotation for the triangle node
            rotationAngle += 1.0f * deltaTime * 0.05;
            sceneGraph.setRootRotation(Vector3(0.0f, rotationAngle, 0.0f));
            sceneGraph.update(deltaTime);

            // Draw scene
            triangle1->localToWorldSpace();
            triangle2->localToWorldSpace();
            sceneGraph.draw(viewMatrix, projectionMatrix);
            triangle1->worldToLocalSpace();
            triangle2->worldToLocalSpace();

            renderer.swapBuffers();
            window.pollEvents();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}