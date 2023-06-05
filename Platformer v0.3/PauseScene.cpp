#include "PauseScene.h"

void PauseScene::Initialize()
{
	Debug::Log("Start initializing...", typeid(*this).name());

	pauseBackground = sharedContext.entityManger->CreateEntity<PauseBackground>(objectContext);
	pauseBackground->SetPosition(0.f, 0.f);
	ObjectCollection::AddUiObject(pauseBackground);

	pauseLogo = sharedContext.entityManger->CreateEntity<PauseLogo>(objectContext);
	pauseLogo->SetPosition(0.f, -250.f);
	ObjectCollection::AddUiObject(pauseLogo);

	continueButton = sharedContext.entityManger->CreateEntity<ContinueGameButton>(objectContext);
	continueButton->SetPosition(-200.f, 0.f);
	ObjectCollection::AddUiObject(continueButton);

	loadAndContinueButton = sharedContext.entityManger->CreateEntity<LoadAndContinueGameButton>(objectContext);
	loadAndContinueButton->SetPosition(-200.f, 150.f);
	ObjectCollection::AddUiObject(loadAndContinueButton);

	saveButton = sharedContext.entityManger->CreateEntity<SaveGameButton>(objectContext);
	saveButton->SetPosition(200.f, 0.f);
	ObjectCollection::AddUiObject(saveButton);

	saveAndExitButton = sharedContext.entityManger->CreateEntity<SaveAndExitButton>(objectContext);
	saveAndExitButton->SetPosition(200.f, 150.f);
	ObjectCollection::AddUiObject(saveAndExitButton);

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
