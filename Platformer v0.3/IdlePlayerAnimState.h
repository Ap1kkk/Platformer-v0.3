#pragma once

#include "AnimationState.h"
#include "EventListener.h"

class IdlePlayerAnimState : public AnimationState, public EventListener
{
public:
	IdlePlayerAnimState() : AnimationState(AnimationType::Idle) {}

	void OnStateEnter() override 
	{
		SubscribeOnEvent(EventType::OnPlayerStartedRunning);
		SubscribeOnEvent(EventType::OnPlayerStartedSprinting);
		SubscribeOnEvent(EventType::OnPlayerJumpRaise);
		SubscribeOnEvent(EventType::OnJumpSensorLeftCollisions);
	}

	void OnStateExit() override 
	{
		UnsubscribeFromEvent(EventType::OnPlayerStartedRunning);
		UnsubscribeFromEvent(EventType::OnPlayerStartedSprinting);
		UnsubscribeFromEvent(EventType::OnPlayerJumpRaise);
		UnsubscribeFromEvent(EventType::OnJumpSensorLeftCollisions);

	}

	void OnEventHappened(EventData& data) override 
	{
		//if (data.eventType == EventType::OnPlayerStartedRunning)
		//{
		//	ChangeState(AnimationType::Run);
		//}
		switch (data.eventType)
		{
			case EventType::OnPlayerStartedRunning:
			{
				ChangeState(AnimationType::Run);
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

		}
	}
};

