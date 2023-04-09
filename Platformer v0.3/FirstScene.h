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

class FirstScene : public IScene
{
public:
	FirstScene(SharedContext context) : IScene(context) {}
	~FirstScene() {}

	//TODO помен€ть на awake
	void Initialize() override 
	{
		Debug::Log("Start initializing...", typeid(*this).name());


		//TODO сделать и убрать это в систему префабов

		//----------player--------------
		
		player = sharedContext.entityManger->CreateEntity<Player>(objectContext);
		player->SetSpawnPosition(0.f, 20.f);
		ObjectCollection::AddObject(player);
		
		//----------player--------------

		//auto tileSet = sharedContext.tileManager->CreateTileSet("Jungle Tiles.png", sf::Vector2i(32, 32), 50);
		//
		//for (int offset = 0; offset < 20 * 32; offset += 32)
		//{
		//	sharedContext.tileManager->CreateTile(tileSet, offset % 20, sf::Vector2f(-64 + offset, -20));
		//}

		//----------enemy--------------
		
		enemy = sharedContext.entityManger->CreateEntity<Enemy>(objectContext);
		ObjectCollection::AddObject(enemy);

		//----------enemy--------------



		//----------floor--------------

		mainChunk = new MainChunk(sharedContext, objectContext);
		mainChunk->Spawn(sf::Vector2f(0.f, 0.f));

		chunk1 = new TestChunk1(sharedContext, objectContext);
		chunk1->Spawn(sf::Vector2f(1920.f * 1, 0.f));

		chunk2 = new TestChunk2(sharedContext, objectContext);
		chunk2->Spawn(sf::Vector2f(1920.f * 2, 0.f));

		chunk3 = new TestChunk3(sharedContext, objectContext);
		chunk3->Spawn(sf::Vector2f(1920.f * (-1), 0.f));


		//for (int y = -100; y <= 200; y += 300)
		//{
		//	for (int x = -320 * 3; x < 320 * 3; x += 320 * 2)
		//	{
				//road = sharedContext.entityManger->CreateEntity<RoadSprite>(objectContext);
				//road->SetSpawnPosition(0.f, 0.f);
				//road->SetTexture("road.png");
				//ObjectCollection::AddObject(road);
		//	}
		//}

		//----------floor--------------
		
		//uiButton = sharedContext.entityManger->CreateEntity<UIButton>(objectContext);
		//uiButton->SetPosition(0.f, -300.f);

		//ObjectCollection::AddUiObject(uiButton);

		Debug::Log("Initialised with id: " + std::to_string(sceneId), typeid(*this).name());
	}

	void ProcessNotAwoken() override
	{
		ObjectCollection::ProcessNotAwoken();
		ObjectCollection::ProcessNotAwokenComponents();
		//TODO ƒобавить метод дл€ пробуждени€ UI
	}

	void CaptureEvents() override
	{
		if (Input::IsKeyDown(Input::Key::R))
		{
			SceneManager::SwitchScene(sceneId, sceneId);
			//Debug::Log("Left");
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
			//Debug::Log("Left");
		}
	}

	void EarlyUpdate() override 
	{
		ObjectCollection::EarlyUpdate();
	}

	void Update() override 
	{
		ObjectCollection::Update();
	}

	void LateUpdate() override 
	{
		ObjectCollection::LateUpdate();
	}

	void UpdateUI() override
	{
		ObjectCollection::UpdateUI();
	}

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

	DrawLayer floorDrawLayer = 100;
};

