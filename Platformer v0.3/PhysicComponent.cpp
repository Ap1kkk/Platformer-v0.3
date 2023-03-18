#include "PhysicComponent.h"

PhysicComponent::PhysicComponent()
{
	bodyDef.position.Set(0.f, 0.f);
	Debug::LogInfo("Created with id: " + std::to_string(componentId), typeid(*this).name());
}

sf::Vector2f PhysicComponent::GetBodyPosition()
{
	b2Vec2 position = body->GetPosition();
	bodyPosition = { position.x, position.y };
	return bodyPosition;
}

b2Body* PhysicComponent::GetBody()
{
	return body;
}

void PhysicComponent::Initialize(TransformComponent* transform)
{
	ownerTransform = transform;
}

void PhysicComponent::InitializeBody()
{
	SetBody(PhysicSystem::CreateBody(&bodyDef, this->ownerId));
}

void PhysicComponent::SetBodyDef(b2BodyDef newBodyDef)
{
	bodyDef = newBodyDef;
}

void PhysicComponent::AddFixtureDef(b2FixtureDef newFixtureDef)
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

void PhysicComponent::DeleteFixtureDef(b2Fixture* exitingFixture)
{
	body->DestroyFixture(exitingFixture);
}

void PhysicComponent::SetBodyType(b2BodyType type)
{
	bodyDef.type = type;
}

void PhysicComponent::EarlyUpdate()
{
	ownerTransform->SetPosition(GetBodyPosition());
}

void PhysicComponent::Update()
{
	ownerTransform->SetPosition(GetBodyPosition());
}

void PhysicComponent::LateUpdate()
{
	ownerTransform->SetPosition(GetBodyPosition());
}

void PhysicComponent::OnDestroy()
{
	PhysicSystem::DestroyBody(this->body);
}