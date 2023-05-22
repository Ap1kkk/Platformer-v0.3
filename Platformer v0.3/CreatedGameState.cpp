#include "CreatedGameState.h"

CreatedGameState::CreatedGameState(SharedContext context) : sharedContext(context)
{
	SetStateType(GameStateType::Created);
}

void CreatedGameState::EnterState()
{
	//TODO добавить логику загрузки сохранений
	Debug::Log("Entered Created state");
}

void CreatedGameState::Update()
{
	Debug::Log("Updating Created state");
	sharedContext.gameStateMachine->Initialize();
	//TODO переход в состояние инициализации
}

void CreatedGameState::LeaveState()
{
	Debug::Log("Leaving Created state");
}