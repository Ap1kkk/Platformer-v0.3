#pragma once
#include <unordered_map>
#include <vector>

#include "box2d/box2d.h"

#include "Entity.h"
#include "Window.h"
#include "Debug.h"

class PhysicSystem
{
public:
	PhysicSystem();
	~PhysicSystem();

	void Update(float deltaTime);

private:
	std::unordered_map<std::string, Entity*> entities;

	b2World* world;
};

