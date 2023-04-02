#pragma once

#include "GameState.h"
#include "SharedContext.h"
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

