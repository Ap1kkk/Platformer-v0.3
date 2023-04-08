#pragma once

#include "GameObject.h"
#include "DataTypes.h"
#include "Debug.h"

class RoadSprite : public GameObject
{
public:
	RoadSprite()
	{
		Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
	}

	void Awake() override
	{
		MakeDrawable(true, drawLayer);
		GameObject::SetTexture(textureFilename);

		MakePhysical();

		b2BodyDef bodyDef2;
		bodyDef2.type = b2_staticBody;
		bodyDef2.position = b2Vec2(spawnPosition.x, spawnPosition.y);

		physicComponent->SetBodyDef(bodyDef2);
		physicComponent->InitializeBody();

		b2PolygonShape boxShape2;
		auto floorSpriteHSize = GetSpriteBoxHalfSize();
		boxShape2.SetAsBox(floorSpriteHSize.x, floorSpriteHSize.y);

		b2FixtureDef boxFixtureDef2;
		boxFixtureDef2.shape = &boxShape2;
		boxFixtureDef2.density = 0;
		boxFixtureDef2.filter.categoryBits = (1 << ((uint16)CollisionLayers::Ground));

		physicComponent->AddFixture(boxFixtureDef2);
	}

	void SetTexture(const Filename& textureFilename)
	{
		this->textureFilename = textureFilename;
	}

private:
	DrawLayer drawLayer = 100;
	Filename textureFilename = "floor.png";
};

