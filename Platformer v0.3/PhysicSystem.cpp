#include "PhysicSystem.h"

std::unordered_map<EntityId, b2Body*> PhysicSystem::bodies = {};
b2World* PhysicSystem::world = new b2World(b2Vec2(0, -10));

PhysicSystem::PhysicSystem(b2Vec2 gravity)
{
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
	world->Step(timeStep, velocityIterations, positionIterations);
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
	world->DestroyBody(body);
}
