#pragma once

#include <box2d/box2d.h>

#include "Input.h"
#include "IComponent.h"
#include "TransformComponent.h"

class PlayerMovement : public IComponent
{
public:
	PlayerMovement() { SetLayer(3); }

	void SetBody(b2Body* body)
	{
		this->body = body;
	}

	void Update() override
	{
		auto input = Input::GetInputAxes();
		if (Input::IsKeyPressed(Input::Key::Horizontal))
		{
			auto vel = body->GetLinearVelocity();
			float deltaVel = 10 - abs(vel.x);
			vel = b2Vec2(input.x * Time::FixedDeltaTime() * deltaVel, 0);
			body->ApplyLinearImpulseToCenter(vel, true);
		}
		if (Input::IsKeyDown(Input::Key::Space))
		{
			auto vel = body->GetLinearVelocity();
			float deltaVel = 200 - abs(vel.x);
			vel += b2Vec2(0, -deltaVel);
			body->SetLinearVelocity(vel);
		}
	}

private:
	b2Body* body;
};