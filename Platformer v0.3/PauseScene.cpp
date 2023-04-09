#include "PauseScene.h"

void PauseScene::Initialize()
{
	Debug::Log("Start initializing...", typeid(*this).name());

	button = sharedContext.entityManger->CreateEntity<UIButton>(objectContext);
	button->SetPosition(0.f, 0.f);

	ObjectCollection::AddUiObject(button);

	Debug::Log("Initialised with id: " + std::to_string(sceneId), typeid(*this).name());
}

void PauseScene::ProcessNotAwoken()
{
	ObjectCollection::ProcessNotAwoken();
	ObjectCollection::ProcessNotAwokenComponents();
	//TODO Добавить метод для пробуждения UI
}

void PauseScene::CaptureEvents()
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
	}
}

void PauseScene::EarlyUpdate()
{
	ObjectCollection::EarlyUpdate();
}

void PauseScene::Update()
{
	ObjectCollection::EarlyUpdate();
}

void PauseScene::LateUpdate()
{
	ObjectCollection::LateUpdate();
}

void PauseScene::UpdateUI()
{
	ObjectCollection::UpdateUI();
}
