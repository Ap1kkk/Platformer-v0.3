#include "Game.h"

Game::Game(b2Vec2 gravity) : window("Platformer")
{
	Debug::Log("Start initializing...", typeid(*this).name());

	assetAllocator = new AssetAllocator;
	entityManger = new EntityManager;
	physicSystem = new PhysicSystem(gravity);
	renderSystem = new RenderSystem(&window);
	sceneManager = new SceneManager;

	//-------------------Debug Draw-------------------------------
	physicsDebugDraw = new PhysicsDebugDraw(&window);


	physicSystem->SetDebugDraw(physicsDebugDraw);
	physicsDebugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit); //� ���������� �������
	//physicsDebugDraw->SetFlags(b2Draw::e_shapeBit);
	//-------------------Debug Draw-------------------------------

	sharedContext.window = &window;
	sharedContext.assetAllocator = assetAllocator;
	sharedContext.entityManger = entityManger;
	sharedContext.physicsDebugDraw = physicsDebugDraw;
	sharedContext.renderSystem = renderSystem;

	deltaTime = clock.restart().asSeconds();

	//-------------------�������� ���� ----------------------------

	auto firstScene = SceneManager::AddScene<FirstScene>(sharedContext);
	//auto secondScene = SceneManager::AddScene<FirstScene>(sharedContext);

	sceneManager->Initialize(firstScene->GetSceneId());

	//-------------------�������� ����----------------------------

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
	physicSystem->Update(1.f / 60.f, 6, 2);
	sceneManager->EarlyUpdate(deltaTime);
}

void Game::Update()
{
	window.Update();
	sceneManager->Update(deltaTime);
	//if (Input::IsKeyPressed(Input::Key::Left))
	//{
	//	Debug::Log("Left");
	//}
}

void Game::LateUpdate()
{
	sceneManager->LateUpdate(deltaTime);
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
	deltaTime = clock.restart().asSeconds();
}
