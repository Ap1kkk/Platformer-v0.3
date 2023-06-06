#pragma once

#include "IScene.h"
#include "SceneManager.h"

#include "Player.h"

#include "MainChunk.h"
#include "TunnelChunk.h"
#include "GroundChunk.h"
#include "GroundToTunnelChunk.h"

#include "LevelBarrier.h"
#include "SaveManager.h"

const short LEVEL_WIDTH = 5;
const short LEVEL_HEIGHT = 4;

class FirstLevel : public IScene
{
public:
	FirstLevel(SharedContext context) : IScene(context) {}
	~FirstLevel() 
	{
		delete mainChunk;
		delete groundChunk1;
		delete groundChunk2;
		delete groundChunk3;
		delete groundChunk4;

		for (auto& tunnel : tunnels)
		{
			delete tunnel;
		}
	}

	void Initialize() override
	{
		player = sharedContext.entityManger->CreateEntity<Player>(objectContext);
		if (SaveManager::IsGameLoaded())
		{
			if (SaveManager::GetLastSavedScene() == GameLevels::FirstLevel)
			{
				player->SetSpawnPosition(SaveManager::GetPlayerPosition());
			}
			else
			{
				player->SetSpawnPosition(150.f, -100.f);

			}
			player->SetHealthPoints(SaveManager::GetSavedPlayerHealthPoints());
		}
		else
		{
			player->SetSpawnPosition(150.f, -100.f);
		}

		ObjectCollection::AddObject(player);

		mainChunk = new MainChunk(sharedContext, objectContext);
		mainChunk->SetLevelName("First Level");
		mainChunk->SetBackgroundTexture("First Level/Byers_House.png");
		mainChunk->SetLevelToSwitch(GameLevels::FirstScene);
		mainChunk->Spawn(sf::Vector2f(0.f, 0.f));

		groundChunk1 = new GroundChunk(sharedContext, objectContext);
		groundChunk1->SetBackgroundTexture("First Level/part5.png");
		groundChunk1->Spawn(sf::Vector2f(1920.f * (-2) , 0.f));

		groundChunk2 = new GroundChunk(sharedContext, objectContext);
		groundChunk2->SetBackgroundTexture("First Level/part2.png");
		groundChunk2->Spawn(sf::Vector2f(1920.f * (-1), 0.f));

		groundChunk3 = new GroundToTunnelChunk(sharedContext, objectContext);
		groundChunk3->SetBackgroundTexture("First Level/part3.png");
		groundChunk3->Spawn(sf::Vector2f(1920.f * 1, 0.f));

		groundChunk4 = new GroundChunk(sharedContext, objectContext);
		groundChunk4->SetBackgroundTexture("First Level/part4.png");
		groundChunk4->Spawn(sf::Vector2f(1920.f * 2, 0.f));

		levelBarrierLeft = sharedContext.entityManger->CreateEntity<LevelBarrier>(objectContext);
		levelBarrierLeft->SetSpawnPosition(sf::Vector2f(1920.f * (-2) - 754.f, 0.f));
		ObjectCollection::AddObject(levelBarrierLeft);

		levelBarrierRight = sharedContext.entityManger->CreateEntity<LevelBarrier>(objectContext);
		levelBarrierRight->SetSpawnPosition(sf::Vector2f(1920.f * 2 + 754.f, 0.f));
		ObjectCollection::AddObject(levelBarrierRight);

		for (int y = 0; y < LEVEL_HEIGHT; ++y)
		{
			for (int x = 0; x < LEVEL_WIDTH; ++x)
			{
				auto tunnelChunk = new TunnelChunk(sharedContext, objectContext);
				tunnelChunk->SetTunnelChunkNumber(tunnelNumbers[y][x]);
				tunnelChunk->SetChunkSpawnId(y * LEVEL_HEIGHT + x);
				tunnelChunk->Spawn(sf::Vector2f(1920.f * (-2) + 1920.f * x , 1080.f + 1080.f * y));

				tunnels.push_back(tunnelChunk);
			}
		}
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

	void OnReload() override
	{
		Chunk::RefreshIdCounter();
	}

	void OnDestroy() override
	{
		Chunk::RefreshIdCounter();
	}

private:
	Player* player;
	MainChunk* mainChunk;
	GroundChunk* groundChunk1;
	GroundChunk* groundChunk2;
	GroundToTunnelChunk* groundChunk3;
	GroundChunk* groundChunk4;

	LevelBarrier* levelBarrierLeft;
	LevelBarrier* levelBarrierRight;

	std::vector<TunnelChunk*> tunnels;

	int tunnelNumbers[LEVEL_HEIGHT][LEVEL_WIDTH] =
	{
		11,	16,	15,	17,	8,
		6,	5,	14,	15,	7,
		18,	19,	14,	16,	10,
		20,	16,	15,	1,	7
	};
};

