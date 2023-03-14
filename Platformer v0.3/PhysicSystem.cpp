#include "PhysicSystem.h"

std::unordered_map<EntityId, b2Body*> PhysicSystem::bodies = {};
b2World* PhysicSystem::world = new b2World(b2Vec2(0, -10));