#pragma once

#include "AnimationState.h"
#include "EventListener.h"

class AttackEnemyAnimState : public AnimationState, public EventListener
{
public:
	AttackEnemyAnimState() : AnimationState(AnimationType::Attack) {}

	void OnStateEnter() override
	{
		//SubscribeOnEvent(EventType::OnPlayerStartedRunning);
	}

	void OnStateExit() override
	{
		//UnsubscribeFromEvent(EventType::OnPlayerStartedRunning);
	}

	void OnEventHappened(EventData& data) override
	{

	}

	void OnNonCyclicAnimEnded() override
	{
		ChangeState(AnimationType::Run);
	}
};