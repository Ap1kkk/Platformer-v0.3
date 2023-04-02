#pragma once

#include "GameState.h"
#include "SharedContext.h"
#include "Debug.h"

class PausedGameState : public GameState
{
public:
	PausedGameState(SharedContext context) : sharedContext(context)
	{
		SetStateType(GameStateType::Paused);
	}

	void EnterState() override
	{
		Debug::Log("Entered Paused state");
		sharedContext.objectCollection->MoveAllToPauseBuffer();
		sharedContext.renderSystem->MoveActiveToPauseBuffer();
		sharedContext.physicsDebugDraw->SetFlags(0);
	}
	void Update() override
	{
		//Debug::Log("Updating Paused state");
		sharedContext.sceneManager->ProcessNotAwoken();
		sharedContext.sceneManager->CaptureEvents();
		sharedContext.sceneManager->UpdateUI();

	}
	void LeaveState() override
	{
		Debug::Log("Leaving Paused state");
		sharedContext.objectCollection->RetrieveAllFromPauseBuffer();
		sharedContext.renderSystem->RetrieveActiveFromPauseBuffer();
		sharedContext.physicsDebugDraw->SetFlags(b2Draw::e_shapeBit);
	}

private:
	SharedContext sharedContext;
};

