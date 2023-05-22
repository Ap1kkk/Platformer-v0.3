#include "RunnedGameState.h"

RunnedGameState::RunnedGameState(SharedContext context) : sharedContext(context)
{
	SetStateType(GameStateType::Runned);
}

void RunnedGameState::EnterState()
{
	//TODO перенести логику создания всех сцен
	Debug::Log("Entered Runned state");

}

void RunnedGameState::Update()
{
	//Debug::Log("Updating Runned state");
	sharedContext.sceneManager->ProcessNotAwoken();
	sharedContext.sceneManager->CaptureEvents();

	sharedContext.physicSystem->Update(Time::FixedDeltaTime(), 6, 2);

	sharedContext.sceneManager->EarlyUpdate();
	sharedContext.sceneManager->Update();
	sharedContext.sceneManager->LateUpdate();
	sharedContext.sceneManager->UpdateUI();
}

void RunnedGameState::LeaveState()
{
	Debug::Log("Leaving Runned state");
}
