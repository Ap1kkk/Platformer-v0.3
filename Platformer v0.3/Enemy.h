#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"
#include "AttackSensor.h"

class Enemy : public GameObject
{
public:
	Enemy()
	{
		Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
	}

	void Awake() override
	{
		MakeDrawable(true, drawLayer);
		SetTexture(enemyTexture);

		MakePhysical();

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = b2Vec2(-100, 20);
		bodyDef.fixedRotation = true;
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
		boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::Enemy));

		physicComponent->AddFixture(boxFixtureDef);
		body = physicComponent->GetBody();

	}

private:
	b2Body* body;

	Filename enemyTexture = "hero.png";

	DrawLayer drawLayer = 100;

};

