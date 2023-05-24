#pragma once

#include "IScene.h"
#include "SceneManager.h"

#include "Player.h"

#include "MainChunk.h"
#include "LevelSwitcher.h"

class MainScene : public IScene
{
public:
	MainScene(SharedContext context) : IScene(context) {}
	~MainScene() {}

	void Initialize() override
	{
		mainChunk = new MainChunk(sharedContext, objectContext);
		mainChunk->SetLevelName("Main Scene");
		mainChunk->SetLevelToSwitch(GameLevels::FirstScene);
		mainChunk->Spawn(sf::Vector2f(0.f, 0.f));


		player = sharedContext.entityManger->CreateEntity<Player>(objectContext);
		player->SetSpawnPosition(150.f, -100.f);
		ObjectCollection::AddObject(player);

	}

	void ProcessNotAwoken() override;

	void CaptureEvents() override
	{
		if (Input::IsKeyDown(Input::Key::R))
		{
			SceneManager::SwitchScene(sceneId, sceneId);
		}

		if (Input::IsKeyDown(Input::Key::Esc))
		{
			if (sharedContext.gameStateMachine->IsPaused())
			{
				sharedContext.gameStateMachine->Contintue();
			}
			else
			{
				sharedContext.gameStateMachine->Pause();
			}
		}
	}

	void EarlyUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void UpdateUI() override;

private:
	Player* player;
	MainChunk* mainChunk;
	LevelSwitcher* levelSwitcher;

};

