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
		SetTexture("ship.png");

		MakePhysical();

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = b2Vec2(-100, 20);
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
		boxFixtureDef.filter.categoryBits = (uint16)CollisionLayers::Enemy;


		physicComponent->AddFixture(boxFixtureDef);
		body = physicComponent->GetBody();

		attackSensor = AddComponent<AttackSensor>();
		attackSensor->SetPhysicComponent(physicComponent);
		attackSensor->SetOffset(sf::Vector2f(-15.f, 0.f));

	}

private:
	b2Body* body;

	AttackSensor* attackSensor;

	DrawLayer drawLayer = 100;

};

