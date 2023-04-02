#pragma once

#include <map>

#include "IGameStateMachine.h"
#include "GameState.h"
#include "SharedContext.h"
#include "Debug.h"


class GameStateMachine : public IGameStateMachine
{
public:
	GameStateMachine() : isPaused(false) {}

	void Create() override
	{
		RunState(GameStateType::Created);
	}
	void Initialize() override
	{
		TransitToState(GameStateType::Initialized);
	}
	void Run() override
	{
		TransitToState(GameStateType::Runned);
	}
	void Pause() override
	{
		isPaused = true;
		TransitToState(GameStateType::Paused);
	}
	void Contintue() override
	{
		isPaused = false;
		TransitToState(GameStateType::Runned);
	}
	void ExitGame() override
	{
		TransitToState(GameStateType::Exited);
	}

	void Update() override
	{
		currentState->Update();
	}

	bool IsPaused() override { return isPaused; }

	template<class S>
	S* AddState(SharedContext context)
	{
		S* newState = new S(context);
		auto stateType = newState->GetStateType();

		auto itr = states.find(stateType);
		if (itr == states.end())
		{
			states.emplace(std::make_pair(stateType, newState));
			return newState;
		}
		else
		{
			Debug::LogError("Can't create state\nState with same type already exists", typeid(*this).name());
			return nullptr;
		}
	}

private:

	void TransitToState(GameStateType nextState)
	{
		currentState->LeaveState();
		RunState(nextState);
	}

	void RunState(GameStateType type)
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

	// контейнер всех созданных состояний
	std::map<GameStateType, GameState*> states;

	GameState* currentState;
	bool isPaused;
};