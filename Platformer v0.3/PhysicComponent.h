#pragma once

#include "Component.h"
#include "IBody.h"
#include "Debug.h"

#include "PhysicSystem.h"

class PhysicComponent : public Component, public IBody
{
public:
	PhysicComponent()
	{
		bodyDef.position.Set(0.f, 0.f);
	}
	~PhysicComponent()
	{
		Debug::LogWarning("Destructor", typeid(*this).name());
		PhysicSystem::DestroyBody(this->body);
	}

	sf::Vector2f GetBodyPosition()
	{
		b2Vec2 position = body->GetPosition();
		bodyPosition = { position.x, position.y };
		Debug::Log(bodyPosition);
		return bodyPosition;
	}

	void InitializeBody()
	{
		SetBody(PhysicSystem::CreateBody(&bodyDef, this->ownerId));
	}

	void SetBodyDef(b2BodyDef newBodyDef)
	{
		bodyDef = newBodyDef;
	}

	void SetFixtureDef(b2FixtureDef newFixtureDef)
	{
		fixtureDef = newFixtureDef;
		body->CreateFixture(&fixtureDef);
	}

	void SetBodyType(b2BodyType type)
	{
		bodyDef.type = type;
	}

private:
	sf::Vector2f bodyPosition;
};

