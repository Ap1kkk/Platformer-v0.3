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
		SetComponentLayer(3); 
		velocity = normalVelocity;
	}

	void SetBody(b2Body* body)
	{
		this->body = body;
		body->SetFixedRotation(isFixedRotation);
	}
	
	void SetJumpSensor(JumpSensor* jumpSensor)
	{
		this->jumpSensor = jumpSensor;
	}

	void Update() override
	{
		auto input = Input::GetInputAxes();

		//Horizontal movement
		if (Input::IsKeyPressed(Input::Key::Horizontal))
		{
			auto vel = body->GetLinearVelocity();
			float deltaVel = velocity - abs(vel.x);
			vel = b2Vec2(input.x * Time::FixedDeltaTime() * deltaVel, vel.y);
			body->SetLinearVelocity(vel);
		}

		//Sprint
		if (Input::IsKeyDown(Input::Key::LShift))
		{
			velocity = sprintVelocity;
		}
		if (Input::IsKeyUp(Input::Key::LShift))
		{
			velocity = normalVelocity;
		}


		// Jump
		if (Input::IsKeyDown(Input::Key::Space) && jumpSensor->IsEnabledToJump())
		{
			body->SetGravityScale(preJumpGravityScale);

			auto vel = body->GetLinearVelocity();
			float deltaVel = jumpSpeed - abs(vel.y);
			vel += b2Vec2(0, -deltaVel);
			body->SetLinearVelocity(vel);
		}
		if (Input::IsKeyPressed(Input::Key::Space) )
		{
			jumpTime += Time::DeltaTime();

			if (jumpTime > jumpMaxTime)
			{
				body->SetGravityScale(normalGravityScale);
			}
		}
		if (Input::IsKeyUp(Input::Key::Space) )
		{

			body->SetGravityScale(normalGravityScale);
			jumpTime = 0.f;
		}
	}

private:
	b2Body* body;
	JumpSensor* jumpSensor;

	float velocity;
	float sprintVelocity = 550.f;
	float normalVelocity = 300.f;

	float jumpTime = 0.f;
	float jumpMaxTime = 0.5f;

	float preJumpGravityScale = 0.1f;
	float normalGravityScale = 0.4f;

	float jumpSpeed = 20.f;

	bool isFixedRotation = true;
};