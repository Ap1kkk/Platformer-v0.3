#include "FirstScene.h"

void FirstScene::Initialize()
{
	Debug::Log("Start initializing...", typeid(*this).name());


	//TODO сделать и убрать это в систему префабов

	//----------player--------------

	mainChunk = new MainChunk(sharedContext, objectContext);
	mainChunk->SetLevelName("Test main chunk");
	mainChunk->SetLevelToSwitch(GameLevels::FirstScene);
	mainChunk->Spawn(sf::Vector2f(0.f, 0.f));

	player = sharedContext.entityManger->CreateEntity<Player>(objectContext);
	if (SaveManager::IsGameLoaded())
	{
		player->SetSpawnPosition(SaveManager::GetPlayerPosition());
	}
	else
	{
		player->SetSpawnPosition(150.f, -100.f);
	}
	ObjectCollection::AddObject(player);

	levelFinisher = sharedContext.entityManger->CreateEntity<LevelFinisher>(objectContext);
	levelFinisher->SetPosition(sf::Vector2f(300.f, 200.f));
	ObjectCollection::AddObject(levelFinisher);


	//----------player--------------

	//----------enemy--------------

	//if(SaveManager::IsGameLoaded())
	//{
	//	enemy = sharedContext.entityManger->CreateEntity<Enemy>(objectContext);
	//	ObjectCollection::AddObject(enemy);
	//}

	//----------enemy--------------

	shopLevel = new MainChunk(sharedContext, objectContext);
	shopLevel->SetLevelName("Shop Level");
	shopLevel->SetLevelToSwitch(GameLevels::ShopLevel);
	shopLevel->Spawn(sf::Vector2f(1920.f * (-1), 0.f));

	firstLevel = new MainChunk(sharedContext, objectContext);
	firstLevel->SetLevelName("First Level");
	firstLevel->SetBackgroundTexture("First Level/Byers_House.png");
	firstLevel->SetLevelToSwitch(GameLevels::FirstLevel);
	firstLevel->Spawn(sf::Vector2f(1920.f * 1, 0.f));

	secondLevel = new MainChunk(sharedContext, objectContext);
	secondLevel->SetLevelName("Second Level");
	secondLevel->SetLevelToSwitch(GameLevels::SecondLevel);
	secondLevel->Spawn(sf::Vector2f(1920.f * 2, 0.f));

	thirdLevel = new MainChunk(sharedContext, objectContext);
	thirdLevel->SetLevelName("Third Level");
	thirdLevel->SetLevelToSwitch(GameLevels::ThirdLevel);
	thirdLevel->Spawn(sf::Vector2f(1920.f * 3, 0.f));

	fourthLevel = new MainChunk(sharedContext, objectContext);
	fourthLevel->SetLevelName("Fourth Level");
	fourthLevel->SetLevelToSwitch(GameLevels::FourthLevel);
	fourthLevel->Spawn(sf::Vector2f(1920.f * 4, 0.f));

	Debug::Log("Initialised with id: " + std::to_string(sceneId), typeid(*this).name());
}

void FirstScene::ProcessNotAwoken()
{
	ObjectCollection::ProcessNotAwoken();
	ObjectCollection::ProcessNotAwokenComponents();
	//TODO Добавить метод для пробуждения UI
}

void FirstScene::CaptureEvents()
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
