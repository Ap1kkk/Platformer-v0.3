#pragma once

#include <box2d/box2d.h>

#include "Input.h"
#include "IComponent.h"
#include "TransformComponent.h"
#include "JumpSensor.h"

class PlayerMovement : public IComponent
{
public:
	PlayerMovement();

	void SetBody(b2Body* body);
	
	void SetJumpSensor(JumpSensor* jumpSensor);

	void Update() override;

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

	float jumpSpeed = 30.f;

	bool isFixedRotation = true;
};