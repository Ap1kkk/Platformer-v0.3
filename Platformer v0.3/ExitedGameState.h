#pragma once

#include "GameState.h"
#include "SharedContext.h"
#include "Debug.h"

class ExitedGameState : public GameState
{
public:
	ExitedGameState(SharedContext context) : sharedContext(context)
	{
		SetStateType(GameStateType::Exited);
	}

	void EnterState() override
	{
		Debug::Log("Entered Paused state");
		//TODO ������ ���������� ��������� ���� � ������� ������
	}
	void Update() override
	{

	}
	void LeaveState() override
	{
		Debug::Log("Leaving Paused state");
	}

private:
	SharedContext sharedContext;
};

