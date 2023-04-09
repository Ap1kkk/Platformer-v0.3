#include "InitializedGameState.h"

InitializedGameState::InitializedGameState(SharedContext context) : sharedContext(context)
{
	SetStateType(GameStateType::Initialized);
}

void InitializedGameState::EnterState()
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

void InitializedGameState::Update()
{
	Debug::Log("Updating Initialized state");

	sharedContext.gameStateMachine->Run();
}

void InitializedGameState::LeaveState()
{
	Debug::Log("Leaving Initialized state");
}
