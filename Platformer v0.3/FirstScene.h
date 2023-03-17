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

		//----------player--------------
		
		player = sharedContext.entityManger->CreateEntity<Player>( );
		//TODO заменить на вызов Start который будет делать коллекция и убрать эту строчку
		player->Initialize();
		player->SetWindow(sharedContext.window);
		ObjectCollection::AddObject(player);
		
		//----------player--------------



		//----------floor--------------

		floor = sharedContext.entityManger->CreateEntity<GameObject>();
		floor->MakeDrawable(true);
		floor->SetTexture("floor.png");

		auto physicComponent2 = floor->MakePhysical();

		b2BodyDef bodyDef2;
		bodyDef2.type = b2_staticBody;
		bodyDef2.position = b2Vec2(0, 200);
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

