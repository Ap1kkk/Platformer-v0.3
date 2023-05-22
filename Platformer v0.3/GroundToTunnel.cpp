#include "GroundToTunnel.h"

GroundToTunnel::GroundToTunnel()
{
	Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
}

void GroundToTunnel::Awake()
{
	AddSpriteComponent(drawLayer);
	SetTexture(textureFilename);

	auto physicComponent = MakePhysical();

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(spawnPosition.x, spawnPosition.y);

	physicComponent->SetBodyDef(bodyDef);
	physicComponent->InitializeBody();

	{
		b2PolygonShape boxShape;
		boxShape.SetAsBox(colliderWidth1, colliderHeight, colliderOffset1, 0.f);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::Ground));

		physicComponent->AddFixture(boxFixtureDef);
	}

	{
		b2PolygonShape boxShape;
		boxShape.SetAsBox(colliderWidth2, colliderHeight, colliderOffset2, 0.f);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::Ground));

		physicComponent->AddFixture(boxFixtureDef);
	}
}

void GroundToTunnel::SetPosition(const sf::Vector2f& position)
{
	transform->SetPosition(sf::Vector2f(position.x, position.y));
	SetSpawnPosition(position);
}

void GroundToTunnel::SetBackgroundTexture(Filename textureFilename)
{
	this->textureFilename = textureFilename;
}