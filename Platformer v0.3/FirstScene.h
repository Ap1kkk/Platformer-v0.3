#pragma once

#include "IScene.h"
#include "Debug.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Input.h"
#include "Player.h"

class FirstScene : public IScene
{
public:
	FirstScene(SharedContext context) : IScene(context) {}
	~FirstScene() {}

	void Initialize() override 
	{
		Debug::Log("Start initializing...", typeid(*this).name());


		//TODO сделать и убрать это в систему префабов


		////----------ship--------------
		//ship = sharedContext.entityManger->CreateEntity<GameObject>();
		//ship->MakeDrawable(true);
		//ship->SetTexture("ship.png");

		//auto physicComponent = ship->MakePhysical();

		//b2BodyDef bodyDef;
		//bodyDef.type = b2_dynamicBody;
		//bodyDef.position = b2Vec2(50, 20);
		//physicComponent->SetBodyDef(bodyDef);
		//physicComponent->InitializeBody();

		//b2CircleShape circleShape;
		//circleShape.m_p.Set(0, 0);
		//circleShape.m_radius = 20.f;

		//b2FixtureDef circleFixtureDef;

		//circleFixtureDef.shape = &circleShape;
		//circleFixtureDef.density = 1;

		//physicComponent->AddFixtureDef(circleFixtureDef);

		//ObjectCollection::AddObject(ship);
		////----------ship--------------
		


		//----------player--------------
		
		player = sharedContext.entityManger->CreateEntity<Player>( );
		player->Initialize();
		ObjectCollection::AddObject(player);
		
		//----------player--------------



		//----------floor--------------

		floor = sharedContext.entityManger->CreateEntity<GameObject>();
		floor->MakeDrawable(true);
		floor->SetTexture("floor.png");

		auto physicComponent2 = floor->MakePhysical();

		b2BodyDef bodyDef2;
		bodyDef2.type = b2_staticBody;
		bodyDef2.position = b2Vec2(300, 200);
		physicComponent2->SetBodyDef(bodyDef2);
		physicComponent2->InitializeBody();

		b2PolygonShape boxShape2;
		auto floorSpriteHSize = floor->GetSpriteBoxHalfSize();
		boxShape2.SetAsBox(floorSpriteHSize.x, floorSpriteHSize.y);

		b2FixtureDef boxFixtureDef2;
		boxFixtureDef2.shape = &boxShape2;
		boxFixtureDef2.density = 0;

		physicComponent2->AddFixtureDef(boxFixtureDef2);

		ObjectCollection::AddObject(floor);

		//----------floor--------------

		Debug::Log("Initialised with id: " + std::to_string(sceneId), typeid(*this).name());
	}

	void EarlyUpdate(float deltaTime) override 
	{
		ObjectCollection::EarlyUpdate(deltaTime);
	}

	void Update(float deltaTime) override 
	{
		ObjectCollection::Update(deltaTime);

		if (Input::IsKeyDown(Input::Key::Esc))
		{
			SceneManager::SwitchScene(sceneId, sceneId);
			//Debug::Log("Left");
		}
	}

	void LateUpdate(float deltaTime) override 
	{
		ObjectCollection::LateUpdate(deltaTime);
		floor->SyncronizeDrawable();
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
	GameObject* floor;
	Player* player;
};

