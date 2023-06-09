#pragma once
#include <unordered_map>

#include <box2d/box2d.h>

#include "IBody.h"
#include "PhysicsDebugDraw.h"
#include "Debug.h"

#include "FixtureManager.h"

/// <summary>
/// Responsible for storing pointer to the world and some interaction with it
/// </summary>
class PhysicSystem
{
public:
	PhysicSystem(b2Vec2 gravity);
	~PhysicSystem();

	void Update(float timeStep, int velocityIterations, int positionIterations);

	void DrawDebug();

	void SetDebugDraw(PhysicsDebugDraw* debugDraw);

	static b2Body* CreateBody(b2BodyDef* bodyDef, EntityId ownerId);

	static void DestroyBody(b2Body* body);

	static EntityId GetBodyOwnerId(b2Body* body);

	template<class C>
	static void SetContactListener(C* instancePtr)
	{
		world->SetContactListener(instancePtr);
	}

	static void ClearDestroyBuffer()
	{
		for (auto& body : destroyBuffer)
		{
			world->DestroyBody(body);
		}
		destroyBuffer.clear();
	}

	//static void Reload()
	//{
	//	FixtureManager::ClearDestroyBuffer();
	//	ClearDestroyBuffer();

	//	delete world;
	//	world = new b2World(gravity);
	//	//world->SetAllowSleeping(false);
	//}

private:
	static std::unordered_map<EntityId, b2Body*> bodies;
	static std::vector<b2Body*> destroyBuffer;

	static b2World* world;
	static b2Vec2 gravity;
};

