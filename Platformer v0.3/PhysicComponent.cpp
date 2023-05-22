#include "PhysicComponent.h"

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
	//auto fix = new b2FixtureDef;
	//fix->userData.pointer = 100;

	//newFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(fix);
	//auto fixture = new Fixture(body->CreateFixture(&newFixtureDef), ownerId);
	auto fixture = FixtureManager::CreateFixture(newFixtureDef, body, ownerId);
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
		//TODO опасно, может работать не правильно
		//body->DestroyFixture(itr->second);
		FixtureManager::DestroyFixture(fixtureId, body);
		Debug::LogWarning("Deleted fixture with id: " + std::to_string(fixtureId), typeid(*this).name());
	}
	else
	{
		Debug::LogError("Can't delete fixture\nFixture with id: " + std::to_string(fixtureId) + " not found", typeid(*this).name());
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
	for (auto& pair : fixtures)
	{
		FixtureManager::DestroyFixture(pair.first, body);
	}
	fixtures.clear();

	for (auto& pair : sensors)
	{
		FixtureManager::DestroySensor(pair.second, body);
	}
	sensors.clear();

	PhysicSystem::DestroyBody(this->body);
}