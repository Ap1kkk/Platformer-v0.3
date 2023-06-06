#include "PhysicSystem.h"

std::unordered_map<EntityId, b2Body*> PhysicSystem::bodies = {};
std::vector<b2Body*> PhysicSystem::destroyBuffer = {};

b2World* PhysicSystem::world = new b2World(b2Vec2(0, -10));
b2Vec2 PhysicSystem::gravity = { 0.f, -10.f };

PhysicSystem::PhysicSystem(b2Vec2 worldGravity)
{
	gravity = worldGravity;
	world->SetGravity(gravity);
	world->SetAllowSleeping(false);
	Debug::Log("Initialized", typeid(*this).name());
}

PhysicSystem::~PhysicSystem()
{
	delete world;
}

void PhysicSystem::Update(float timeStep, int velocityIterations, int positionIterations)
{
	FixtureManager::ClearDestroyBuffer();
	world->Step(timeStep, velocityIterations, positionIterations);
	FixtureManager::ClearDestroyBuffer();
	ClearDestroyBuffer();
}

void PhysicSystem::DrawDebug()
{
	world->DebugDraw();
}

void PhysicSystem::SetDebugDraw(PhysicsDebugDraw* debugDraw)
{
	world->SetDebugDraw(debugDraw);
}

b2Body* PhysicSystem::CreateBody(b2BodyDef* bodyDef, EntityId ownerId)
{
	b2Body* body = world->CreateBody(bodyDef);
	bodies.insert(std::make_pair(ownerId, body));
	return body;
}

void PhysicSystem::DestroyBody(b2Body* body)
{
	auto id = GetBodyOwnerId(body);
	bodies.erase(id);
	//world->DestroyBody(body);
	destroyBuffer.push_back(body);
}

EntityId PhysicSystem::GetBodyOwnerId(b2Body* body)
{
	for (auto itr = bodies.begin(); itr != bodies.end(); ++itr)
	{
		if (body == itr->second)
		{
			return itr->first;
		}
	}
	Debug::LogWarning("Body owner Id not found");
}
