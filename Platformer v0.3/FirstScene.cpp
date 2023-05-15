#include "FirstScene.h"

void FirstScene::Initialize()
{
	Debug::Log("Start initializing...", typeid(*this).name());


	//TODO ������� � ������ ��� � ������� ��������

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



	mainChunk = new MainChunk(sharedContext, objectContext);
	mainChunk->Spawn(sf::Vector2f(0.f, 0.f));

	chunk1 = new TestChunk1(sharedContext, objectContext);
	chunk1->Spawn(sf::Vector2f(1920.f * 1, 0.f));

	chunk2 = new TestChunk2(sharedContext, objectContext);
	chunk2->Spawn(sf::Vector2f(1920.f * 2, 0.f));

	chunk3 = new TestChunk3(sharedContext, objectContext);
	chunk3->Spawn(sf::Vector2f(1920.f * (-1), 0.f));

	levelSwitcher = sharedContext.entityManger->CreateEntity<LevelSwitcher>(objectContext);
	levelSwitcher->SetPosition(sf::Vector2f(100.f, 0.f));
	levelSwitcher->SetLevelTotransit(GameLevels::MainLevel);
	ObjectCollection::AddObject(levelSwitcher);

	Debug::Log("Initialised with id: " + std::to_string(sceneId), typeid(*this).name());
}

void FirstScene::ProcessNotAwoken()
{
	ObjectCollection::ProcessNotAwoken();
	ObjectCollection::ProcessNotAwokenComponents();
	//TODO �������� ����� ��� ����������� UI
}

void FirstScene::CaptureEvents()
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

void FirstScene::EarlyUpdate()
{
	ObjectCollection::EarlyUpdate();
}

void FirstScene::Update()
{
	ObjectCollection::Update();
}

void FirstScene::LateUpdate()
{
	ObjectCollection::LateUpdate();
}

void FirstScene::UpdateUI()
{
	ObjectCollection::UpdateUI();
}
