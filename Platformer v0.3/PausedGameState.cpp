#include "PausedGameState.h"

PausedGameState::PausedGameState(SharedContext context) : sharedContext(context)
{
	SetStateType(GameStateType::Paused);
}

void PausedGameState::EnterState()
{
	Debug::Log("Entered Paused state");
	sharedContext.objectCollection->MoveAllToPauseBuffer();
	sharedContext.renderSystem->MoveActiveToPauseBuffer();
	sharedContext.physicsDebugDraw->SetFlags(0);

	sharedContext.sceneManager->ShowPauseScene();
}

void PausedGameState::Update()
{
	//Debug::Log("Updating Paused state");

	sharedContext.sceneManager->UpdatePauseScene();
}

void PausedGameState::LeaveState()
{
	Debug::Log("Leaving Paused state");

	sharedContext.sceneManager->HidePauseScene();

	sharedContext.objectCollection->RetrieveAllFromPauseBuffer();
	sharedContext.renderSystem->RetrieveActiveFromPauseBuffer();
	sharedContext.physicsDebugDraw->SetFlags(b2Draw::e_shapeBit);
}