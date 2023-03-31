#include "PhysicComponent.h"

FixtureId PhysicComponent::staticFixtureIdCounter = 0;

PhysicComponent::PhysicComponent()
{
	bodyDef.position.Set(0.f, 0.f);
	SetComponentLayer(0);
	Debug::LogInfo("Created with id: " + std::to_string(componentId), typeid(*this).name());
}

sf::Vector2f PhysicComponent::GetBodyPosition()
{
	b2Vec2 position = body->GetPosition();
	bodyPosition = { position.x, position.y };
	return bodyPosition;
}

float PhysicComponent::GetBodyAngle()
{
	return bodyAngle = body->GetAngle();
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

//TODO на доработке
Fixture* PhysicComponent::AddFixture(b2FixtureDef& newFixtureDef)
{
	auto fixture = new Fixture(body->CreateFixture(&newFixtureDef));
	auto newFixtureId = fixture->GetFixtureId();

	fixtures.emplace(std::make_pair(newFixtureId, fixture));

	Debug::LogInfo("Added fixture with id: " + std::to_string(newFixtureId), typeid(*this).name());

	return fixture;
}

void PhysicComponent::DeleteFixture(FixtureId fixtureId)
{
	auto itr = fixtures.find(fixtureId);
	if (itr != fixtures.end())
	{
		body->DestroyFixture(itr->second);
		Debug::LogWarning("Deleted fixture with id: " + std::to_string(fixtureId), typeid(*this).name());
	}
	else
	{
		Debug::LogWarning("Can't delete fixture\nFixture with id: " + std::to_string(fixtureId) + " not found", typeid(*this).name());
	}
}

void PhysicComponent::SetBodyType(b2BodyType type)
{
	bodyDef.type = type;
}

void PhysicComponent::LateUpdate()
{
	ownerTransform->SetPosition(GetBodyPosition());
	ownerTransform->SetAngleInRad(GetBodyAngle());
}

void PhysicComponent::OnDestroy()
{
	PhysicSystem::DestroyBody(this->body);
}