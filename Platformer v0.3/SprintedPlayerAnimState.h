#pragma once

#include "AnimationState.h"
#include "EventListener.h"

class SprintedPlayerAnimState : public AnimationState, public EventListener
{
public:
	SprintedPlayerAnimState() : AnimationState(AnimationType::Sprint) {}

	void OnStateEnter() override
	{
		SubscribeOnEvent(EventType::OnPlayerStoppedRunning);
		SubscribeOnEvent(EventType::OnPlayerStoppedSprinting);
		SubscribeOnEvent(EventType::OnPlayerJumpRaise);
		SubscribeOnEvent(EventType::OnJumpSensorLeftCollisions);

	}

	void OnStateExit() override
	{
		UnsubscribeFromEvent(EventType::OnPlayerStoppedSprinting);
		UnsubscribeFromEvent(EventType::OnPlayerStoppedRunning);
		UnsubscribeFromEvent(EventType::OnPlayerJumpRaise);
		UnsubscribeFromEvent(EventType::OnJumpSensorLeftCollisions);
	}

	void OnEventHappened(EventData& data) override
	{
		switch (data.eventType)
		{
			case EventType::OnPlayerStoppedRunning:
			{
				ChangeState(AnimationType::Idle);
				break;
			}
			case EventType::OnPlayerStoppedSprinting: 
			{
				ChangeState(AnimationType::Run);
				break;
			}
			case EventType::OnPlayerJumpRaise:
			{
				ChangeState(AnimationType::JumpRaise);
				break;
			}
			case EventType::OnJumpSensorLeftCollisions:
			{
				ChangeState(AnimationType::JumpFall);
				break;
			}
		}
	}
};

