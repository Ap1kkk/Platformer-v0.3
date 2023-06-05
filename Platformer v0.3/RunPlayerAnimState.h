#pragma once

#include "AnimationState.h"
#include "EventListener.h"

class RunPlayerAnimState : public AnimationState, public EventListener
{
public:
	RunPlayerAnimState() : AnimationState(AnimationType::Run) {}

	void OnStateEnter() override
	{
		SubscribeOnEvent(EventType::OnPlayerStoppedRunning);
		SubscribeOnEvent(EventType::OnPlayerStartedSprinting);
		SubscribeOnEvent(EventType::OnPlayerJumpRaise);
		SubscribeOnEvent(EventType::OnJumpSensorLeftCollisions);
		SubscribeOnEvent(EventType::OnPlayerAttack);
	}

	void OnStateExit() override
	{
		UnsubscribeFromEvent(EventType::OnPlayerStoppedRunning);
		UnsubscribeFromEvent(EventType::OnPlayerStartedSprinting);
		UnsubscribeFromEvent(EventType::OnPlayerJumpRaise);
		UnsubscribeFromEvent(EventType::OnJumpSensorLeftCollisions);
		UnsubscribeFromEvent(EventType::OnPlayerAttack);

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
			case EventType::OnPlayerStartedSprinting:
			{
				ChangeState(AnimationType::Sprint);
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
			case EventType::OnPlayerAttack:
			{
				ChangeState(AnimationType::Attack);
				break;
			}
		}
	}
};


