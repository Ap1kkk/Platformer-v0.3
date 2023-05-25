#include "ExitedGameState.h"

ExitedGameState::ExitedGameState(SharedContext context) : sharedContext(context)
{
	SetStateType(GameStateType::Exited);
}

void ExitedGameState::EnterState()
{
	Debug::Log("Entered Exited state");
	//TODO логика сохранения прогресса игры и очистка памяти
	sharedContext.window->Close();
}

void ExitedGameState::Update()
{

}

void ExitedGameState::LeaveState()
{
	Debug::Log("Leaving Exited state");
}
