#pragma once

#include "IScene.h"
#include "Debug.h"
#include "UIButton.h"
#include "SceneManager.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"

#include "MainChunk.h"

#include "LevelSwitcher.h"
#include "LevelFinisher.h"

#include "SaveManager.h"

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
	LevelFinisher* levelFinisher;

	DrawLayer floorDrawLayer = 100;
};

