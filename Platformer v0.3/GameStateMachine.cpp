#include "GameStateMachine.h"

void GameStateMachine::Create()
{
	RunState(GameStateType::Created);
}

void GameStateMachine::Initialize()
{
	TransitToState(GameStateType::Initialized);
}

void GameStateMachine::Run()
{
	TransitToState(GameStateType::Runned);
}

void GameStateMachine::Pause()
{
	isPaused = true;
	TransitToState(GameStateType::Paused);
}

void GameStateMachine::Contintue()
{
	isPaused = false;
	TransitToState(GameStateType::Runned);
}

void GameStateMachine::ExitGame()
{
	TransitToState(GameStateType::Exited);
}

void GameStateMachine::Update()
{
	currentState->Update();
}

void GameStateMachine::TransitToState(GameStateType nextState)
{
	currentState->LeaveState();
	RunState(nextState);
}

void GameStateMachine::RunState(GameStateType type)
{
	auto itr = states.find(type);
	if (itr != states.end())
	{
		currentState = itr->second;
		currentState->EnterState();
		//currentState->Update();
	}
	else
	{
		Debug::LogError("Can't run state\nState with type:" + std::to_string((int)type) + " not found", typeid(GameStateMachine).name());
	}
}