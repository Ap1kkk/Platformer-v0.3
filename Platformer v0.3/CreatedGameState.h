#pragma once

#include "GameState.h"
#include "SharedContext.h"
#include "Debug.h"

class CreatedGameState : public GameState
{
public:
	CreatedGameState(SharedContext context) : sharedContext(context)
	{
		SetStateType(GameStateType::Created);
	}

	void EnterState() override
	{
		//TODO добавить логику загрузки сохранений
		Debug::Log("Entered Created state");
	}
	void Update() override
	{
		Debug::Log("Updating Created state");
		sharedContext.gameStateMachine->Initialize();
		//TODO переход в состояние инициализации
	}
	void LeaveState() override
	{
		Debug::Log("Leaving Created state");
	}

private:
	SharedContext sharedContext;
};

