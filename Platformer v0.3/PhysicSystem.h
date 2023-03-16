#pragma once
#include <unordered_map>

#include <box2d/box2d.h>

#include "IBody.h"
#include "PhysicsDebugDraw.h"
#include "Debug.h"

class PhysicSystem
{
public:
	PhysicSystem(b2Vec2 gravity)
	{
		world->SetGravity(gravity);
		world->SetAllowSleeping(false);
		Debug::Log("Initialized", typeid(*this).name());
	}
	~PhysicSystem()
	{
		delete world;
	}

	void Update(float timeStep, int velocityIterations, int positionIterations)
	{
		world->Step(timeStep, velocityIterations, positionIterations);
	}

	void DrawDebug() { world->DebugDraw(); }

	void SetDebugDraw(PhysicsDebugDraw* debugDraw)
	{
		world->SetDebugDraw(debugDraw);
	}

	static b2Body* CreateBody(b2BodyDef* bodyDef, EntityId ownerId)
	{
		b2Body* body = world->CreateBody(bodyDef);
		bodies.insert(std::make_pair(ownerId, body));
		return body;
	}

	static void DestroyBody(b2Body* body)
	{
		world->DestroyBody(body);
	}

	template<class C>
	static void SetContactListener(C* instancePtr)
	{
		world->SetContactListener(instancePtr);
	}

private:
	static std::unordered_map<EntityId, b2Body*> bodies;
	//static std::unordered_map<EntityId, IConctactListener> contactListeners; 

	static b2World* world;
};

