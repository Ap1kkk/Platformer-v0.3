#pragma once

#include "IScene.h"
#include "SceneManager.h"

#include "Input.h"

#include "StartGameButton.h"
#include "LoadGameButton.h"
#include "ExitGameButton.h"

#include "MenuBackground.h"
#include "MenuLogo.h"

class MainMenu : public IScene
{
public:
	MainMenu(SharedContext context) : IScene(context) {}
	~MainMenu() {}

	void Initialize() override
	{
		startGameButton = sharedContext.entityManger->CreateEntity<StartGameButton>(objectContext);
		startGameButton->SetPosition(-400.f, 250.f);
		ObjectCollection::AddUiObject(startGameButton);

		loadGameButton = sharedContext.entityManger->CreateEntity<LoadGameButton>(objectContext);
		loadGameButton->SetPosition(0.f, 250.f);
		ObjectCollection::AddUiObject(loadGameButton);

		exitGameButton = sharedContext.entityManger->CreateEntity<ExitGameButton>(objectContext);
		exitGameButton->SetPosition(400.f, 250.f);
		ObjectCollection::AddUiObject(exitGameButton);

		menuBackground = sharedContext.entityManger->CreateEntity<MenuBackground>(objectContext);
		menuBackground->SetPosition(0.f, 0.f);
		ObjectCollection::AddUiObject(menuBackground);
	}

	void ProcessNotAwoken() override;

	void CaptureEvents() override
	{
		//if (Input::IsKeyDown(Input::Key::R))
		//{
		//	SceneManager::SwitchScene(sceneId, sceneId);
		//}

		//if (Input::IsKeyDown(Input::Key::Esc))
		//{
		//	if (sharedContext.gameStateMachine->IsPaused())
		//	{
		//		sharedContext.gameStateMachine->Contintue();
		//	}
		//	else
		//	{
		//		sharedContext.gameStateMachine->Pause();
		//	}
		//}
	}

	void EarlyUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void UpdateUI() override;

private:
	StartGameButton* startGameButton;
	LoadGameButton* loadGameButton;
	ExitGameButton* exitGameButton;

	MenuBackground* menuBackground;
	MenuLogo* menuLogo;
};

