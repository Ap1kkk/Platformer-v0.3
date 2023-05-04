#pragma once

#include <box2d/box2d.h>

#include "Input.h"
#include "IComponent.h"
#include "TransformComponent.h"
#include "JumpSensor.h"

#include "OnPlayerTurnedFaceEvent.h"
#include "PlayerTurnedFaceData.h"

class PlayerMovement : public IComponent
{
public:
	PlayerMovement();

	void SetBody(b2Body* body);
	
	void SetJumpSensor(JumpSensor* jumpSensor);

	void Update() override;

	void CheckDirectionSwap(const sf::Vector2f& direction)
	{

		if (direction.x != (float)lastDirection && direction.x != 0.f)
		{
			EventData data(OnPlayerTurnedFaceEvent::GetType());

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
			OnPlayerTurnedFaceEvent::Invoke(data);

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
};