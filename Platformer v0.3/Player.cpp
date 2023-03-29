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

	//b2CircleShape circleShape;  
	//circleShape.m_p.Set(0, 0);
	//circleShape.m_radius = 15.f;
	b2PolygonShape boxShape;
	b2Vec2 size = GetSpriteBoxHalfSize();
	boxShape.SetAsBox(size.x, size.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
 

	physicComponent->AddFixture(boxFixtureDef);
	body = physicComponent->GetBody();
	//body->SetFixedRotation(true);
	camera = AddComponent<Camera>();
	playerMovement = AddComponent<PlayerMovement>();
	playerMovement->SetBody(body);
	 
	jumpSensor = AddComponent<JumpSensor>();
	jumpSensor->SetPhysicComponent(physicComponent);
	jumpSensor->SetOffset(sf::Vector2f(0, 15));
}

void Player::Update()
{

}
