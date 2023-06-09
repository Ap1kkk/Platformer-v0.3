#include "PlayerMovement.h"

PlayerMovement::PlayerMovement()
{
	SetComponentLayer(3);
	velocity = normalVelocity;
}

void PlayerMovement::SetBody(b2Body* body)
{
	this->body = body;
	body->SetFixedRotation(isFixedRotation);
}

void PlayerMovement::SetJumpSensor(JumpSensor* jumpSensor)
{
	this->jumpSensor = jumpSensor;
}

void PlayerMovement::Update()
{
	auto input = Input::GetInputAxes();

	//Horizontal movement
	if (Input::IsKeyPressed(Input::Key::Horizontal))
	{
		CheckDirectionSwap(input);

		auto vel = body->GetLinearVelocity();
		float deltaVel = velocity - abs(vel.x);
		vel = b2Vec2(input.x * Time::FixedDeltaTime() * deltaVel, vel.y);
		body->SetLinearVelocity(vel);
	}

	if (Input::IsInputAxesEnabled())
	{
		EventData data(EventType::OnPlayerStartedRunning);
		Event::Invoke(data);
	}

	if (Input::IsInputAxesDisabled())
	{
		EventData data(EventType::OnPlayerStoppedRunning);
		Event::Invoke(data);
	}

	//Sprint
	if (Input::IsKeyDown(Input::Key::LShift))
	{
		velocity = sprintVelocity;

		EventData data(EventType::OnPlayerStartedSprinting);
		Event::Invoke(data);
	}
	if (Input::IsKeyUp(Input::Key::LShift))
	{
		velocity = normalVelocity;

		EventData data(EventType::OnPlayerStoppedSprinting);
		Event::Invoke(data);
	}


	// Jump
	if (Input::IsKeyDown(Input::Key::Space) && jumpSensor->IsEnabledToJump())
	{
		EventData data(EventType::OnPlayerJumpRaise);
		Event::Invoke(data);

		body->SetGravityScale(preJumpGravityScale);

		auto vel = body->GetLinearVelocity();
		float deltaVel = jumpSpeed - abs(vel.y);
		vel += b2Vec2(0, -deltaVel);
		body->SetLinearVelocity(vel);
	}
	if (Input::IsKeyPressed(Input::Key::Space))
	{
		jumpTime += Time::DeltaTime();

		if (jumpTime > jumpMaxTime)
		{
			EventData data(EventType::OnPlayerJumpFall);
			Event::Invoke(data);

			body->SetGravityScale(normalGravityScale);
		}
	}
	if (Input::IsKeyUp(Input::Key::Space))
	{
		EventData data(EventType::OnPlayerJumpFall);
		Event::Invoke(data);

		body->SetGravityScale(normalGravityScale);
		jumpTime = 0.f;
	}

	//lastFrameDirection = input;
}
