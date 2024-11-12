#include <windows.h>

#include "Renderer.h"
#include "GameWindow.h"
#include "Input.h"
#include "SceneGraph.h"
#include "RenderableNode.h"
#include "TrianglePrimitive.h"
#include "RectanglePrimitive.h"
#include "FramerateController.h"
#include "EventManager.h"
#include "GameObject.h"
#include "PhysicsBody.h"
#include "AABB.h"
#include "OBB.h"
#include "Circle.h"
#include "PhysicsManager.h"


int main() {
        // Create window, renderer and input systems
        GameWindow window(800, 600, "2D Example");
        Renderer renderer(window);
        Input input(window);
        FramerateController* framerateController = FramerateController::GetInstance();

        // Create scene graph
        SceneGraph sceneGraph;

        // Set up camera (view and projection matrices)
        Vector3 cameraPos(0.0f, 0.0f, 1.0);
        Vector3 cameraTarget = cameraPos + Vector3(0.0f, 0.0f, -1.0f);
        Vector3 upVector(0.0f, 1.0f, 0.0f);
        Matrix4 viewMatrix = Matrix4::lookAt(cameraPos, cameraTarget, upVector);
        float aspectRatio = static_cast<float>(window.getWidth()) / window.getHeight();
        float bottom = -window.getWidth() * 0.5f;
        float top = window.getHeight() * 0.5f;
        float left = -window.getWidth() * 0.5f;
        float right = window.getWidth() * 0.5f;
        Matrix4 projectionMatrix = Matrix4::orthographic(left, right, bottom, top, 0.1f, 1000.0f);

        // Drawable objects
        auto box1 = std::make_shared<GameObject>("Icon1", &renderer);
        box1->setLocalPosition(Vector3(-1.0f, 0.0f, 0.0f));
        box1->setLocalScale(Vector3(100.0f, 100.f, 1.0f));

        auto box2 = std::make_shared<GameObject>("Icon2", &renderer);
        box2->setLocalPosition(Vector3(1.0f, 0.0f, 0.0f));
        box2->setLocalScale(Vector3(100.0f, 100.f, 1.0f));

        sceneGraph.addNode(box1);
        sceneGraph.addNode(box2);

        // Create instances of bodies for boxes
        auto body1 = std::make_unique<PhysicsBody>(box1.get());
        auto body2 = std::make_unique<PhysicsBody>(box2.get());

        // Create OBBs
        auto shape1 = std::make_shared<OBB>(
            Vector3(-0.0f, -0.0f, 0.0f),  // half width/height of 50 for 100x100 box
            Vector3(0.5f, 0.5f, 0.0f));
        auto shape2 = std::make_shared<OBB>(
            Vector3(-0.0f, -0.0f, 0.0f),  // half width/height of 50 for 100x100 box
            Vector3(0.5f, 0.5f, 0.0f));
        shape1->initializeDebugDraw(&renderer);
        shape2->initializeDebugDraw(&renderer);

        // Create AABB shapes
        body1->setShape(shape1);
        body2->setShape(shape2);

        // Add bodies to physics system
        PhysicsManager::Instance().addBody(body1.get());
        PhysicsManager::Instance().addBody(body2.get());
        

        float angle = 0.0f;
        float speed = 10.0f;
        float deltaTime = 0.0f;
        int expectedFrameRate = 60; // 1000;
        framerateController->SetTargetFramerate(expectedFrameRate);

        
        while (!window.shouldClose()) {

            renderer.clear(0.2f, 0.3f, 0.3f, 1.0f);
            framerateController->FrameStart();              // record the time from frame start

            
            // Input for box1
            Vector3 velocity(0.0f, 0.0f, 0.0f);
            if (input.isKeyHeld(k_D)) 
                velocity.x = speed;
            if (input.isKeyHeld(k_A)) 
                velocity.x = -speed;
            if (input.isKeyHeld(k_W)) 
                velocity.y = speed;
            if (input.isKeyHeld(k_S))
                velocity.y = -speed;
            body1->setVelocity(velocity);

            if(input.isKeyHeld(A_LEFT))
                box1->setLocalRotation(Vector3(0.0f, 0.0f, (angle -= 0.01f)));
            if (input.isKeyHeld(A_RIGHT))
                box1->setLocalRotation(Vector3(0.0f, 0.0f, (angle += 0.01f)));

            

            // Physics update deltaTime
            //objectDelta.Update(deltaTime);
            
            //// Physics update loop fixedStepTime
            //while (framerateController->ShouldUpdatePhysics()) {
            //    PhysicsManager::Instance().update(FramerateController::DEFAULT_FIXED_TIME_STEP);
            //    framerateController->ConsumePhysicsTime();
            //}
            PhysicsManager::Instance().update(deltaTime);
            
            input.update(); 
            if (input.isKeyHeld(K_ESCAPE))
                break;

            sceneGraph.update(deltaTime);

            // draw debug lines for all bodies
            // In your render loop, after sceneGraph.draw:
            //std::cout << "Number of physics bodies: " << PhysicsManager::Instance().getBodies().size() << "\n";
            for (auto body : PhysicsManager::Instance().getBodies()) {
                if (auto obb = dynamic_cast<OBB*>(body->getShape())) {
                    //std::cout << "Drawing OBB at position: " << body->getOwner()->getLocalPosition().x
                    //    << ", " << body->getOwner()->getLocalPosition().y << "\n";
                    obb->drawDebugLines(viewMatrix, projectionMatrix);
                }
            }


            sceneGraph.draw(viewMatrix, projectionMatrix);

            //std::cout << "Angle for box1: " << angle << std::endl;
            //std::cout << "========================" << std::endl;
            renderer.swapBuffers();
            window.pollEvents();

            framerateController->FrameEnd();
            deltaTime = framerateController->DeltaTime;

        }

        return 0;
}
