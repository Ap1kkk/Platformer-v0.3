#pragma once

#include <box2d/box2d.h>

#include "Input.h"
#include "IComponent.h"
#include "TransformComponent.h"
#include "JumpSensor.h"

class PlayerMovement : public IComponent
{
public:
	PlayerMovement() 
	{ 
		SetLayer(3); 
		velocity = normalVelocity;
	}

	void SetBody(b2Body* body)
	{
		this->body = body;
	}
	
	void SetJumpSensor(JumpSensor* jumpSensor)
	{
		this->jumpSensor = jumpSensor;
	}

	void Update() override
	{
		auto input = Input::GetInputAxes();
		if (Input::IsKeyPressed(Input::Key::Horizontal))
		{
			auto vel = body->GetLinearVelocity();
			float deltaVel = velocity - abs(vel.x);
			vel = b2Vec2(input.x * Time::FixedDeltaTime() * deltaVel, vel.y);
			body->SetLinearVelocity(vel);
		}
		if (Input::IsKeyDown(Input::Key::LShift))
		{
			velocity = sprintVelocity;
		}
		if (Input::IsKeyUp(Input::Key::LShift))
		{
			velocity = normalVelocity;
		}
		if (Input::IsKeyDown(Input::Key::Space) && jumpSensor->IsEnabledToJump())
		{
			auto vel = body->GetLinearVelocity();
			float deltaVel = jumpSpeed - abs(vel.y);
			vel += b2Vec2(0, -deltaVel);
			body->SetLinearVelocity(vel);
			Debug::Log(body->GetLinearVelocity());
		}
	}

private:
	b2Body* body;
	JumpSensor* jumpSensor;

	float velocity;
	float sprintVelocity = 150.f;
	float normalVelocity = 50.f;

	float jumpSpeed = 100.f;
};