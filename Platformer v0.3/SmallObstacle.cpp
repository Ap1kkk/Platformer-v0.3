#include "SmallObstacle.h"

SmallObstacle::SmallObstacle()
{
	Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
}

void SmallObstacle::Awake()
{
	AddSpriteComponent(drawLayer);
	SetTexture(textureFilename);

	auto physicComponent = MakePhysical();

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(spawnPosition.x, spawnPosition.y);

	physicComponent->SetBodyDef(bodyDef);
	physicComponent->InitializeBody();

	b2PolygonShape boxShape;
	b2Vec2 size = GetSpriteBoxHalfSize();
	boxShape.SetAsBox(size.x, size.y);
	//boxShape.SetAsBox(size.x, 20.f, colliderOffset, 0.f);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::SmallObstacle));

	physicComponent->AddFixture(boxFixtureDef);
}

void SmallObstacle::SetPosition(const sf::Vector2f& position)
{
	transform->SetPosition(sf::Vector2f(position.x, position.y));
	SetSpawnPosition(position);
}

void SmallObstacle::SetObstacleTexture(Filename textureFilename)
{
	this->textureFilename = textureFilename;
}
