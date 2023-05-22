#include "LevelBarrier.h"

LevelBarrier::LevelBarrier()
{
	Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
}

void LevelBarrier::Awake()
{
	auto physicComponent = MakePhysical();

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(spawnPosition.x, spawnPosition.y);

	physicComponent->SetBodyDef(bodyDef);
	physicComponent->InitializeBody();

	b2PolygonShape boxShape;
	boxShape.SetAsBox(colliderWidth, colliderHeight);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::Ground));

	physicComponent->AddFixture(boxFixtureDef);
}

void LevelBarrier::SetPosition(const sf::Vector2f& position)
{
	transform->SetPosition(sf::Vector2f(position.x, position.y));
	SetSpawnPosition(position);
}