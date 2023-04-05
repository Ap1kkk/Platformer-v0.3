#pragma once

#include "IScene.h"

#include "SceneManager.h"
#include "ObjectCollection.h"

#include "GameObject.h"
#include "UIObject.h"
#include "Input.h"

#include "Debug.h"

class PauseScene : public IScene
{
public:
	PauseScene(SharedContext context) : IScene(context) {}
	~PauseScene() {}

	void Initialize() override
	{
		Debug::Log("Start initializing...", typeid(*this).name());

		floor = sharedContext.entityManger->CreateEntity<UIObject>(objectContext);
		floor->Initialize(true);
		floor->SetTexture("floor.png");
		floor->SetPosition(sf::Vector2f(0, -100));

		ObjectCollection::AddUiObject(floor);

		Debug::Log("Initialised with id: " + std::to_string(sceneId), typeid(*this).name());
	}

	void ProcessNotAwoken() override
	{
		ObjectCollection::ProcessNotAwoken();
		ObjectCollection::ProcessNotAwokenComponents();
		//TODO Добавить метод для пробуждения UI
	}

	void CaptureEvents() override
	{
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

private:
	UIObject* floor;
	DrawLayer floorDrawLayer = 100;

};

