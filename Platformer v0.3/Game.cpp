#include "Game.h"

Game::Game(b2Vec2 gravity) : window("Platformer")
{
	Debug::Log("Start initializing...", typeid(*this).name());

	Time::Restart();

	assetAllocator = new AssetAllocator;
	entityManger = new EntityManager;
	physicSystem = new PhysicSystem(gravity);
	renderSystem = new RenderSystem(&window);
	sceneManager = new SceneManager;
	tileManager = new TileManager;

	//-------------------Debug Draw-------------------------------
	physicsDebugDraw = new PhysicsDebugDraw(&window);

	physicSystem->SetDebugDraw(physicsDebugDraw);
	//physicsDebugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit); //с отрисовкой площади
	physicsDebugDraw->SetFlags(b2Draw::e_shapeBit); 

	//-------------------Debug Draw-------------------------------


	sharedContext.window = &window;
	sharedContext.assetAllocator = assetAllocator;
	sharedContext.entityManger = entityManger;
	sharedContext.physicsDebugDraw = physicsDebugDraw;
	sharedContext.renderSystem = renderSystem;
	sharedContext.tileManager = tileManager;


	//-------------------Создание сцен ----------------------------

	auto firstScene = SceneManager::AddScene<FirstScene>(sharedContext);
	//auto secondScene = SceneManager::AddScene<FirstScene>(sharedContext);

	sceneManager->Initialize(firstScene->GetSceneId());

	//-------------------Создание сцен----------------------------


	Debug::Log("Initialized", typeid(*this).name());
}

Game::~Game()
{
	ObjectCollection::Clear();
	delete assetAllocator;
	delete entityManger;
	delete physicSystem;
	delete renderSystem;
	delete sceneManager;

	Debug::LogWarning("Game destroyed"); 
}

void Game::ProcessInput()
{
	Input::Update();
}

void Game::EarlyUpdate()
{
	//Time::physicsTimeAccumulator += Time::DeltaTime();
	//while (Time::physicsTimeAccumulator >= Time::FixedDeltaTime())
	//{
	//	physicSystem->Update(Time::FixedDeltaTime(), 6, 2);
	//	Time::physicsTimeAccumulator -= Time::FixedDeltaTime();
	//}
	physicSystem->Update(Time::FixedDeltaTime(), 6, 2);
	sceneManager->EarlyUpdate();
}

void Game::Update()
{
	window.Update();
	sceneManager->Update();
}

void Game::LateUpdate()
{
	sceneManager->LateUpdate();
}

void Game::Draw()
{
	window.BeginDraw();

	renderSystem->Draw();
	sceneManager->Draw(&window);
	physicSystem->DrawDebug();

	window.EndDraw();
}

void Game::CalculateDeltaTime()
{
	Time::Restart();
	//SceneManager::SwitchScene(0, 0);
}
