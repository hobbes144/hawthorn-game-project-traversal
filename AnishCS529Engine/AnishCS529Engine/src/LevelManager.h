//#pragma once
//#include "GameWindow.h"
//#include "Input.h"
//#include "GamePad.h"
//#include "FramerateController.h"
//#include "SceneGraph.h"
//
//class LevelManager {
//
//public:
//	LevelManager() = default;
//
//	void SystemInitalization();
//
//	void MeshMatInitializations();
//
//	void RunLevels();
//	void ExecuteMainLoop();
//	void NextLevel();
//
//	void LoadLevel1();
//	void LoadLevel2();
//	void LoadLevel3();
//
//	void createPlayerObject();
//
//private:
//	//Level Counter
//	int currentLevel = 0;
//
//	//Systems
//	GameWindow* mainWindow;
//	Renderer* mainRenderer;
//	Input* mainInput;
//	GamePad* gamepad;
//	FFramerateController* mainFramerateController;
//	SceneGraph mainSceneGraph;
//	std::shared_ptr<Camera> camera;
//
//	//Materials and Meshes
//	std::shared_ptr<Mesh> boxMesh;
//	std::shared_ptr<MainTestMaterial> boxMaterial;
//	std::shared_ptr<Mesh> floorMesh;
//	std::shared_ptr<MainTestMaterial> floorMaterial;
//	std::shared_ptr<Mesh> concreteMesh;
//	std::shared_ptr<MainTestMaterial> concreteMaterial;
//	std::shared_ptr<MainTestMaterial> cracksMaterial;
//	std::shared_ptr<Mesh> sphereMesh;
//	std::shared_ptr<MainTestMaterial> skyBoxMaterial;
//
//	//Starting Locations
//	Vector3 startingPos1;
//	Vector3 startingPos2;
//	Vector3 startingPos3;
//
//	const float rad = PI / 180.0f;
//
//};