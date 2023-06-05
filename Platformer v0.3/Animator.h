#pragma once

#include "IComponent.h"
#include "IAnimator.h"
#include "AnimationState.h"

#include "Debug.h"

class Animator : public IComponent, public IAnimator
{
public:
	virtual ~Animator()
	{
		currentState->OnStateExit();
		for (auto& state : states)
		{
			delete state.second;
		}
	}

	void LateUpdate() override
	{
		currentState->Update();
	}

	void ChangeState(AnimationType nextType) override
	{
		auto itr = states.find(nextType);
		if (itr != states.end())
		{
			currentState->OnStateExit();
			itr->second->OnStateEnter();
			currentState = itr->second;
		}
		else
		{
			Debug::LogError("Can't switch animation\nAnimation for state:" + std::to_string((short)nextType) + " was not found");
		}
	}

	template<class S>
	void AddState(AnimationType type, Animation* animation)
	{
		auto state = new S;

		state->SetAnimation(animation);
		state->SetIAnimator(this);

		animation->SetIAnimStatePtr(state);

		states.emplace(type, state);
	}

	void SetInitialState(AnimationType type)
	{
		auto itr = states.find(type);
		if (itr != states.end())
		{
			currentState = itr->second;
			currentState->OnStateEnter();
		}
		else
		{
			Debug::LogError("Can't set initial animation state", typeid(*this).name());
		}
	}

private:
	IAnimationState* currentState;

	std::map<AnimationType, IAnimationState*> states;
};

