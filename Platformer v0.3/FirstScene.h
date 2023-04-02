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

	//TODO помен€ть на awake
	void Initialize() override 
	{
		Debug::Log("Start initializing...", typeid(*this).name());


		//TODO сделать и убрать это в систему префабов

		//----------player--------------
		
		player = sharedContext.entityManger->CreateEntity<Player>(objectContext);


		ObjectCollection::AddObject(player);
		
		//----------player--------------

		auto tileSet = sharedContext.tileManager->CreateTileSet("Jungle Tiles.png", sf::Vector2i(32, 32), 50);
		
		for (int offset = 0; offset < 20 * 32; offset += 32)
		{
			sharedContext.tileManager->CreateTile(tileSet, offset % 20, sf::Vector2f(-64 + offset, -20));
		}

		//----------floor--------------

		for (int i = -100; i <= 200; i += 300)
		{
			floor = sharedContext.entityManger->CreateEntity<GameObject>(objectContext);
			floor->MakeDrawable(true, floorDrawLayer);
			floor->SetTexture("floor.png");

			auto physicComponent2 = floor->MakePhysical();

			b2BodyDef bodyDef2;
			bodyDef2.type = b2_staticBody;
			bodyDef2.position = b2Vec2(0, i);
			physicComponent2->SetBodyDef(bodyDef2);
			physicComponent2->InitializeBody();

			b2PolygonShape boxShape2;
			auto floorSpriteHSize = floor->GetSpriteBoxHalfSize();
			boxShape2.SetAsBox(floorSpriteHSize.x, floorSpriteHSize.y);

			b2FixtureDef boxFixtureDef2;
			boxFixtureDef2.shape = &boxShape2;
			boxFixtureDef2.density = 0;

			physicComponent2->AddFixture(boxFixtureDef2);

			ObjectCollection::AddObject(floor);
		}

		//----------floor--------------

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
		//TODO добавить обновление UI коллекции
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

	DrawLayer floorDrawLayer = 100;
};

