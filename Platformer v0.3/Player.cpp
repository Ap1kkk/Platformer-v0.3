#include "Player.h"

Player::Player()
{
	Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
}

void Player::Awake()
{
	MakeDrawable(true, drawLayer);
	SetTexture("ship.png");

	MakePhysical();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(spawnPosition.x, spawnPosition.y);
	physicComponent->SetBodyDef(bodyDef);
	physicComponent->InitializeBody();

	b2PolygonShape boxShape;
	b2Vec2 size = GetSpriteBoxHalfSize();
	boxShape.SetAsBox(size.x, size.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::Player));

	physicComponent->AddFixture(boxFixtureDef);
	body = physicComponent->GetBody();
	//body->SetFixedRotation(true);
	camera = AddComponent<Camera>();
	 
	jumpSensor = AddComponent<JumpSensor>();
	jumpSensor->SetPhysicComponent(physicComponent);
	jumpSensor->SetOffset(sf::Vector2f(0, 15));

	playerMovement = AddComponent<PlayerMovement>();
	playerMovement->SetBody(body);
	playerMovement->SetJumpSensor(jumpSensor);

	attackSensor = AddComponent<AttackSensor>();
	attackSensor->SetPhysicComponent(physicComponent);
	attackSensor->SetOffset(sf::Vector2f(-15.f, 0.f));
}
