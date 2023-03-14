#include "Game.h"

Game::Game(b2Vec2 gravity) : window("Platformer")
{
	assetAllocator = new AssetAllocator;
	entityManger = new EntityManager;
	physicSystem = new PhysicSystem(gravity);

	//-------------------Debug Draw-------------------------------
	physicsDebugDraw = new PhysicsDebugDraw(&window);

	physicSystem->SetDebugDraw(physicsDebugDraw);
	//physicsDebugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit); //с отрисовкой площади
	physicsDebugDraw->SetFlags(b2Draw::e_shapeBit);
	//-------------------Debug Draw-------------------------------


	deltaTime = clock.restart().asSeconds();

	// -----------------------TEST------------------------------------

	//----------ship--------------
	ship = entityManger->CreateEntity<GameObject>();
	ship->MakeDrawable();
	ship->SetTexture("ship.png");

	auto physicComponent = ship->MakePhysical();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(50, 20);
	physicComponent->SetBodyDef(bodyDef);
	physicComponent->InitializeBody();

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = 20.f;

	b2FixtureDef circleFixtureDef;

	circleFixtureDef.shape = &circleShape;
	circleFixtureDef.density = 1;

	physicComponent->SetFixtureDef(circleFixtureDef);
	//----------ship--------------


	//----------floor--------------
	
	floor = entityManger->CreateEntity<GameObject>();
	floor->MakeDrawable();
	floor->SetTexture("floor.png");

	auto physicComponent2 = floor->MakePhysical();

	b2BodyDef bodyDef2;
	bodyDef2.type = b2_staticBody;
	bodyDef2.position = b2Vec2(50, 200);
	physicComponent2->SetBodyDef(bodyDef2);
	physicComponent2->InitializeBody();

	b2PolygonShape boxShape2;
	auto floorSpriteHSize = floor->GetSpriteBoxHalfSize();
	boxShape2.SetAsBox(floorSpriteHSize.x, floorSpriteHSize.y);

	b2FixtureDef boxFixtureDef2;
	boxFixtureDef2.shape = &boxShape2;
	boxFixtureDef2.density = 0;

	physicComponent2->SetFixtureDef(boxFixtureDef2);

	//----------floor--------------

	// -----------------------TEST------------------------------------

	Debug::Log("Initialized", typeid(*this).name());
}

Game::~Game()
{
	delete assetAllocator;
	delete entityManger;
}

void Game::ProcessInput()
{
	Input::Update();
}

void Game::EarlyUpdate()
{
	physicSystem->Update(1.f / 60.f, 6, 2);
	ship->EarlyUpdate();
	floor->EarlyUpdate();
}

void Game::Update()
{

	window.Update();
	auto direction = Input::GetInputAxes();
}

void Game::LateUpdate()
{
}

void Game::Draw()
{
	window.BeginDraw();

	//entityManger->Draw(&window);
	////TODO вызов отрисовки у объектов
	ship->Draw(&window);
	floor->Draw(&window);
	physicSystem->DrawDebug();

	window.EndDraw();
}

void Game::CalculateDeltaTime()
{
	deltaTime = clock.restart().asSeconds();
}
