#pragma once

#include "GameState.h"

#include "SharedContext.h"
#include "SceneManager.h"
#include "FirstScene.h"
#include "PauseScene.h"

#include "Debug.h"

class InitializedGameState : public GameState
{
public:
	InitializedGameState(SharedContext context) : sharedContext(context)
	{
		SetStateType(GameStateType::Initialized);
	}

	void EnterState() override
	{
		//TODO перенести логику создания всех сцен
		Debug::Log("Entered Initialized state");

		auto firstScene = SceneManager::AddScene<FirstScene>(sharedContext);
		auto pauseScene = SceneManager::AddScene<PauseScene>(sharedContext);
		//auto secondScene = SceneManager::AddScene<FirstScene>(sharedContext);

		sharedContext.sceneManager->Initialize(firstScene->GetSceneId());
		sharedContext.sceneManager->SetPauseScene(pauseScene->GetSceneId());
		//SceneManager::AddScene<>

	}

	void Update() override
	{
		Debug::Log("Updating Initialized state");
		
		sharedContext.gameStateMachine->Run();
	}
	void LeaveState() override
	{
		Debug::Log("Leaving Initialized state");
	}

private:
	SharedContext sharedContext;

};

