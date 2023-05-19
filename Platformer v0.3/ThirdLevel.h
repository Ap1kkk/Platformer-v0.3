#pragma once

#include "IScene.h"
#include "SceneManager.h"

#include "Player.h"

#include "MainChunk.h"
#include "LevelSwitcher.h"

class ThirdLevel : public IScene
{
public:
	ThirdLevel(SharedContext context) : IScene(context) {}
	~ThirdLevel() {}

	void Initialize() override
	{
		player = sharedContext.entityManger->CreateEntity<Player>(objectContext);
		player->SetSpawnPosition(0.f, 20.f);
		ObjectCollection::AddObject(player);

		mainChunk = new MainChunk(sharedContext, objectContext);
		mainChunk->SetLevelName("Third Level");
		mainChunk->SetLevelToSwitch(GameLevels::FirstScene);
		mainChunk->Spawn(sf::Vector2f(0.f, 0.f));
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

