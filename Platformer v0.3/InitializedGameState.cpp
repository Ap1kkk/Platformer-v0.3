#include "InitializedGameState.h"

InitializedGameState::InitializedGameState(SharedContext context) : sharedContext(context)
{
	SetStateType(GameStateType::Initialized);
}

void InitializedGameState::EnterState()
{
	//TODO перенести логику создания всех сцен
	Debug::Log("Entered Initialized state");

	Event::SetEventSystem(sharedContext.eventSystem);
	EventListener::SetEventSystem(sharedContext.eventSystem);

	//TODO подписка систем на события
	sharedContext.renderSystem->SubscribeOnEvents();
	sharedContext.objectCollection->SubscribeOnEvents();
	sharedContext.componentManager->SubscribeOnEvents();
	sharedContext.entityManger->SubscribeOnEvents();

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
