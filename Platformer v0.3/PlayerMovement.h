#pragma once

#include <box2d/box2d.h>

#include "Input.h"
#include "IComponent.h"
#include "TransformComponent.h"
#include "JumpSensor.h"

#include "PlayerTurnedFaceData.h"
#include "PlayerMovementData.h"

#include "EventListener.h"

class PlayerMovement : public IComponent, public EventListener
{
public:
	PlayerMovement();
	~PlayerMovement()
	{
		UnsubscribeFromEvent(EventType::OnPlayerMovementRequest);
	}

	void SetBody(b2Body* body);
	
	void SetJumpSensor(JumpSensor* jumpSensor);

	void Update() override;

	void OnEventHappened(EventData& eventData) override
	{
		if (eventData.eventType == EventType::OnPlayerMovementRequest)
		{
			EventData data(EventType::OnPlayerMovementCallback);
			
			auto userData = new PlayerMovementData;
			userData->isRunning = isRunningData;
			userData->isSprinting = isSprintingData;

			data.userData = userData;

			Event::Invoke(data);

			delete userData;
		}
	}

	void CheckDirectionSwap(const sf::Vector2f& direction)
	{

		if (direction.x != (float)lastDirection && direction.x != 0.f)
		{
			EventData data(EventType::OnPlayerTurnedFaceEvent);

			data.id = ownerId;

			PlayerTurnedFaceData* userData = new PlayerTurnedFaceData;

			if (direction.x < 0)
			{
				userData->direction = FaceDirection::Left;
			}
			else
			{
				userData->direction = FaceDirection::Right;
			}
			lastDirection = userData->direction;

			data.userData = userData;
			Event::Invoke(data);

			delete userData;
		}
	}

private:
	b2Body* body;
	JumpSensor* jumpSensor;

	float velocity;
	float sprintVelocity = 1000.f;
	float normalVelocity = 500.f;

	float jumpTime = 0.f;
	float jumpMaxTime = 0.5f;

	float preJumpGravityScale = 0.1f;
	float normalGravityScale = 0.4f;

	//float jumpSpeed = 30.f;
	float jumpSpeed = 50.f;

	bool isFixedRotation = true;

	sf::Vector2f lastFrameDirection;
	FaceDirection lastDirection;

	bool isRunningData = false;
	bool isSprintingData = false;
};