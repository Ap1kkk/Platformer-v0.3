#include "Player.h"

Player::Player()
{
	Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
}

void Player::Awake()
{
	MakeDrawable(true);
	SetTexture("ship.png");

	MakePhysical();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(0, 20);
	physicComponent->SetBodyDef(bodyDef);
	physicComponent->InitializeBody();

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = 15.f;
	//b2PolygonShape boxShape;
	//b2Vec2 size = GetSpriteBoxHalfSize();
	//boxShape.SetAsBox(size.x, size.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &circleShape;
	boxFixtureDef.density = 1;

	physicComponent->AddFixtureDef(boxFixtureDef);
	body = physicComponent->GetBody();

	camera = AddComponent<Camera>();
}

void Player::Update()
{
	auto input = Input::GetInputAxes();
	if (Input::IsKeyPressed(Input::Key::Horizontal))
	{
		auto vel = body->GetLinearVelocity();
		float deltaVel = 5 - abs(vel.x);
		vel = b2Vec2(input.x * Time::FixedDeltaTime() * deltaVel, 0);
		body->ApplyLinearImpulseToCenter(vel, true);
	}
	if (Input::IsKeyDown(Input::Key::Space))
	{
		auto vel = body->GetLinearVelocity();
		float deltaVel = 20 - abs(vel.x);
		vel += b2Vec2(0, -deltaVel);
		body->SetLinearVelocity(vel);
	}
	if (Input::IsKeyPressed(Input::Key::E))
	{
		auto vel = body->GetLinearVelocity();
		vel += b2Vec2(0, -20);
		body->SetLinearVelocity(vel);
	}
}
