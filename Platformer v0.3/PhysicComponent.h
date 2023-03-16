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
		Debug::LogInfo("Created with id: " + std::to_string(componentId), typeid(*this).name());
	}
	~PhysicComponent()
	{
		//Debug::LogWarning("Destructor", typeid(*this).name());
	}

	sf::Vector2f GetBodyPosition()
	{
		b2Vec2 position = body->GetPosition();
		bodyPosition = { position.x, position.y };
		//Debug::Log(bodyPosition);
		return bodyPosition;
	}

	b2Body* GetBody()
	{
		return body;
	}

	void InitializeBody()
	{
		SetBody(PhysicSystem::CreateBody(&bodyDef, this->ownerId));
	}

	void SetBodyDef(b2BodyDef newBodyDef)
	{
		bodyDef = newBodyDef;
	}

	void AddFixtureDef(b2FixtureDef newFixtureDef)
	{
		bool isExists = false;
		for (auto itr = fixtureDefVector.begin(); itr != fixtureDefVector.end(); ++itr)
		{
			if (newFixtureDef == *itr)
			{
				isExists = true;
				break;
			}
		}

		if (!isExists)
		{
			auto itr = fixtureDefVector.emplace_back(newFixtureDef);
			auto fixture = body->CreateFixture(&itr);
			fixturesVector.emplace_back(fixture);
		}
		else
		{
			Debug::LogWarning("The same fixture already exists!", typeid(*this).name());
		}
	}

	void DeleteFixtureDef(b2Fixture* exitingFixture)
	{
		body->DestroyFixture(exitingFixture);
	}

	void SetBodyType(b2BodyType type)
	{
		bodyDef.type = type;
	}

	void OnDestroy() override
	{
		PhysicSystem::DestroyBody(this->body);
		//Debug::LogInfo("OnDestroy", typeid(*this).name());
	}

private:
	sf::Vector2f bodyPosition;
};

