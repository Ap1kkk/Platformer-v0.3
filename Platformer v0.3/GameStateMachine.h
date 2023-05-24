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

	void Create() override;
	void Initialize() override;
	void Run() override;
	void Pause() override;
	void Contintue() override;
	void ExitGame() override;

	void Update() override;

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

	void CheckTransition() override 
	{
		if (isToTransit)
		{
			TransitToState(stateToTransit);
			isToTransit = false;
		}
	}

private:

	void TransitToState(GameStateType nextState);

	void RunState(GameStateType type);

	// контейнер всех созданных состояний
	std::map<GameStateType, GameState*> states;

	GameState* currentState;
	bool isPaused;

	bool isToTransit;
	GameStateType stateToTransit;
};