#pragma once

#include <windows.h>

#include "AttachedCamera.h"
#include "Audio.h"
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
#include "LightingPass.h"
#include "MapLoader.h"
#include "Movement3D.h"
#include "OBB.h"
#include "PhysicsBody.h"
#include "PhysicsManager.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "RaycastManager.h"
#include "RectanglePrimitive.h"
#include "Render3D.h"
#include "RenderableNode.h"
#include "Renderer.h"
#include "SceneGraph.h"
#include "SkydomePass.h"
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

	void LoadLevelMenu();
	void LoadLevel0();
	void LoadLevel1();
	void LoadLevel2();
	void LoadLevel3();
	void LoadLevel4();
	void LoadLevel5();

	bool GameComplete();

	void createPlayerObject();
	void initalizePlayerInLevel();
	void SetPlayerDifficulty(FirstPersonControllerComponent::Difficulty diff);
	FirstPersonControllerComponent::Difficulty getDifficulty() const;

	void resetToMenu();

private:
	LevelManager() = default;

	//Level Counter
	int currentLevel = -1;
	int numLevels = 6;
	bool levelSwapFlag = false;
	bool isFullscreen = true;
	FirstPersonControllerComponent::Difficulty playerDifficulty = FirstPersonControllerComponent::NORMAL;

	//Systems
	GameWindow* mainWindow;
	Renderer* mainRenderer;
	Input* mainInput;
	GamePad* gamepad;
	FFramerateController* mainFramerateController;
	SceneGraph mainSceneGraph;
	std::shared_ptr<GameObject> cameraGameObject;
	std::shared_ptr<AttachedCamera> camera;

	//Materials and Meshes
	std::shared_ptr<Mesh> boxMesh;
	std::shared_ptr<TextureMaterial> boxMaterial;
	std::shared_ptr<Mesh> floorMesh;
	std::shared_ptr<TextureMaterial> floorMaterial;
	std::shared_ptr<Mesh> concreteMesh;
	std::shared_ptr<TextureMaterial> concreteMaterial;
	std::shared_ptr<TextureMaterial> cracksMaterial;
	std::shared_ptr<Mesh> sphereMesh;
	std::shared_ptr<TextureMaterial> grassMaterial;
	std::shared_ptr<TextureMaterial> myhouseMaterial;
	std::shared_ptr<TextureMaterial> brickMaterial;
	std::shared_ptr<TextureMaterial> LightBlueConcrete;
	std::shared_ptr<TextureMaterial> YellowConcrete;
	std::shared_ptr<TextureMaterial> BrownConcrete;
	std::shared_ptr<TextureMaterial> BlueConcrete;
	std::shared_ptr<TextureMaterial> WhiteFloorTiles;
	std::shared_ptr<TextureMaterial> skyBoxMaterial;
	std::shared_ptr<TextureMaterial> keyMaterial;

	//Player References
	std::shared_ptr<GameObject> playerBox;
	Vector3 startingPos0 = Vector3(0.0f, 7.0f, 0.0f);
	Quaternion startingRot0 = Quaternion::fromEuler(Vector3(0.0f,0.5f*3.14159f,0.0f));
	Vector3 startingPos1 = Vector3(0.0f, 7.0f, 0.0f);
	Quaternion startingRot1 = Quaternion::fromEuler(Vector3(0.0f, 0.5f * 3.14159f, 0.0f));
	Vector3 startingPos2 = Vector3(0.0f, 7.0f, 0.0f);
	Quaternion startingRot2 = Quaternion::fromEuler(Vector3(0.0f, 0.5f * 3.14159f, 0.0f));
	Vector3 startingPos3 = Vector3(-131.0f, 7.0f, -130.0f);
	Quaternion startingRot3 = Quaternion::fromEuler(Vector3(0.0f, 1.0f * 3.14159f, 0.0f));
	Vector3 startingPos4 = Vector3(0.0f, 7.0f, 0.0f);
	Quaternion startingRot4 = Quaternion::fromEuler(Vector3(0.0f, 1.0f * 3.14159f, 0.0f));

	const float rad = PI / 180.0f;

};