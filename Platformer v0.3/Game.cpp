#include "Game.h"

Game::Game(b2Vec2 gravity) : window("Platformer")
{
	Debug::Log("Start initializing...", typeid(*this).name());

	Time::Restart();

	eventSystem = new EventSystem;


	objectCollection = new ObjectCollection;
	assetAllocator = new AssetAllocator;
	entityManger = new EntityManager;
	componentManager = new ComponentManager;
	physicSystem = new PhysicSystem(gravity);
	renderSystem = new RenderSystem(&window);
	sceneManager = new SceneManager;
	tileManager = new TileManager;
	gameStateMachine = new GameStateMachine();
	worldContactListener = new WorldContactListener();

	//-------------------Debug Draw-------------------------------
	physicsDebugDraw = new PhysicsDebugDraw(&window);

	physicSystem->SetContactListener<WorldContactListener>(worldContactListener);

	physicSystem->SetDebugDraw(physicsDebugDraw);
	//physicsDebugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit); //� ���������� �������
	physicsDebugDraw->SetFlags(b2Draw::e_shapeBit);

	//-------------------Debug Draw-------------------------------


	sharedContext.window = &window;
	sharedContext.objectCollection = objectCollection;
	sharedContext.assetAllocator = assetAllocator;
	sharedContext.entityManger = entityManger;
	sharedContext.componentManager = componentManager;
	sharedContext.physicsDebugDraw = physicsDebugDraw;
	sharedContext.renderSystem = renderSystem;
	sharedContext.tileManager = tileManager;
	sharedContext.sceneManager = sceneManager;
	sharedContext.gameStateMachine = gameStateMachine;
	sharedContext.worldContactListener = worldContactListener;
	sharedContext.eventSystem = eventSystem;


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
	delete tileManager;
	delete gameStateMachine;
	delete worldContactListener;

	delete eventSystem;

	Debug::LogWarning("Game destroyed"); 
}

void Game::Initialize()
{
	//TODO ���� �������� ������ ������������� ���������
	gameStateMachine->AddState<CreatedGameState>(sharedContext);
	gameStateMachine->AddState<InitializedGameState>(sharedContext);
	gameStateMachine->AddState<RunnedGameState>(sharedContext);
	gameStateMachine->AddState<PausedGameState>(sharedContext);

	//TODO ���������������� ��� ���������

	gameStateMachine->Create();
}

void Game::ProcessGameLoop()
{
	ProcessInput();
	window.Update();
	gameStateMachine->Update();
	Draw();
	EventSystem::ClearDestroyBuffer();
	CalculateDeltaTime();
}

void Game::ProcessInput()
{
	Input::Update();
}

void Game::EarlyUpdate()
{
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

void Game::UpdateUI()
{
	sceneManager->UpdateUI();
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
}
