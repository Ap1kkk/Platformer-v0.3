#pragma once

#include "IScene.h"
#include "Debug.h"
#include "GameObject.h"
#include "UIButton.h"
#include "SceneManager.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"
#include "RoadSprite.h"

#include "MainChunk.h"
#include "TestChunk1.h"
#include "TestChunk2.h"
#include "TestChunk3.h"

#include "LevelSwitcher.h"

class FirstScene : public IScene
{
public:
	FirstScene(SharedContext context) : IScene(context) {}
	~FirstScene() {}

	//TODO поменять на awake
	void Initialize() override;

	void ProcessNotAwoken() override;

	void CaptureEvents() override;

	void EarlyUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void UpdateUI() override;

	//void Draw(Window* window) override 
	//{
	//	
	//}

	//void OnDestroy() override
	//{

	//}

private:
	GameObject* ship;
	RoadSprite* road;
	UIButton* uiButton;
	Player* player;
	Enemy* enemy;

	MainChunk* mainChunk;
	TestChunk1* chunk1;
	TestChunk2* chunk2;
	TestChunk3* chunk3;


	MainChunk* shopLevel;
	MainChunk* firstLevel;
	MainChunk* secondLevel;
	MainChunk* thirdLevel;
	MainChunk* fourthLevel;

	LevelSwitcher* levelSwitcher;

	DrawLayer floorDrawLayer = 100;
};

