#pragma once

#include <windows.h>

#include "Audio.h"
#include "BasicRenderPass.h"
#include "Camera.h"
#include "CollisionListener.h"
#include "EventManager.h"
#include "FirstPersonControllerComponent.h"
#include "FramerateController.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Input.h"
#include "KeyList.h"
#include "MainTestMaterial.h"
#include "MapLoader.h"
#include "Movement3D.h"
#include "OBB.h"
#include "PhysicsBody.h"
#include "PhysicsManager.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "RaycastManager.h"
#include "RectanglePrimitive.h"
#include "Render2D.h"
#include "RenderableNode.h"
#include "Renderer.h"
#include "SceneGraph.h"
#include "TestPass.h"
#include "TextureMaterial.h"
#include "TrianglePrimitive.h"

#include "GlobalVariables.h"


class LevelManager {

public:
	static LevelManager& Instance() {
		static LevelManager instance;
		return instance;
	}
	LevelManager(const LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;

	void SystemInitalization();

	void MeshMatInitializations();

	void RunLevels();
	void ExecuteMainLoop();
	void checkPlayerBoundaries();
	void NextLevel();
	void ClearLevel();
	void ShutdownLevels();

	void LoadLevel0();
	void LoadLevel1();
	void LoadLevel2();
	void LoadLevel3();
	void LoadLevel4();
	void LoadLevel5();

	bool GameComplete();

	void createPlayerObject();
	void initalizePlayerInLevel();

private:
	LevelManager() = default;

	//Level Counter
	int currentLevel = 0;
	int numLevels = 6;
	bool levelSwapFlag = false;

	//Systems
	GameWindow* mainWindow;
	Renderer* mainRenderer;
	Input* mainInput;
	GamePad* gamepad;
	FFramerateController* mainFramerateController;
	SceneGraph mainSceneGraph;
	std::shared_ptr<Camera> camera;

	//Materials and Meshes
	std::shared_ptr<Mesh> boxMesh;
	std::shared_ptr<MainTestMaterial> boxMaterial;
	std::shared_ptr<Mesh> floorMesh;
	std::shared_ptr<MainTestMaterial> floorMaterial;
	std::shared_ptr<Mesh> concreteMesh;
	std::shared_ptr<MainTestMaterial> concreteMaterial;
	std::shared_ptr<MainTestMaterial> cracksMaterial;
	std::shared_ptr<Mesh> sphereMesh;
	std::shared_ptr<MainTestMaterial> grassMaterial;
	std::shared_ptr<MainTestMaterial> myhouseMaterial;
	std::shared_ptr<MainTestMaterial> brickMaterial;
	std::shared_ptr<MainTestMaterial> LightBlueConcrete;
	std::shared_ptr<MainTestMaterial> YellowConcrete;
	std::shared_ptr<MainTestMaterial> BrownConcrete;
	std::shared_ptr<MainTestMaterial> BlueConcrete;
	std::shared_ptr<MainTestMaterial> WhiteFloorTiles;
	std::shared_ptr<MainTestMaterial> skyBoxMaterial;
	std::shared_ptr<MainTestMaterial> keyMaterial;

	//Player References
	std::shared_ptr<GameObject> playerBox;
	Vector3 startingPos0 = Vector3(0.0f, 7.0f, 0.0f);
	Quaternion startingRot0 = Quaternion();
	Vector3 startingPos1 = Vector3(0.0f, 7.0f, 0.0f);
	Quaternion startingRot1 = Quaternion();
	Vector3 startingPos2 = Vector3(0.0f, 7.0f, 0.0f);
	Quaternion startingRot2 = Quaternion();
	Vector3 startingPos3 = Vector3(-131.0f, 7.0f, -130.0f);
	Quaternion startingRot3 = Quaternion();

	const float rad = PI / 180.0f;

};