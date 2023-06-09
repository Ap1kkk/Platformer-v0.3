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

#include "LevelSwitcher.h"

class FirstScene : public IScene
{
public:
	FirstScene(SharedContext context) : IScene(context) {}
	~FirstScene() {}

	//TODO �������� �� awake
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


	MainChunk* shopLevel;
	MainChunk* firstLevel;
	MainChunk* secondLevel;
	MainChunk* thirdLevel;
	MainChunk* fourthLevel;

	LevelSwitcher* levelSwitcher;

	DrawLayer floorDrawLayer = 100;
};

