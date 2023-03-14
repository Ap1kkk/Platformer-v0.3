#pragma once

#include "SFML/Graphics.hpp"
#include "AssetAllocator.h"
#include "Window.h"
#include "EntityManager.h"
#include "PhysicSystem.h"
#include "GameObject.h"
#include "Input.h"
#include "PhysicsDebugDraw.h"
#include "Debug.h"

class Game
{
public:
	Game(b2Vec2 gravity);
	~Game();

	void ProcessInput();
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Draw();
	void CalculateDeltaTime();

	bool IsRunning() { return window.IsOpen(); }

private:
	Window window;
	AssetAllocator* assetAllocator;
	EntityManager* entityManger;
	PhysicSystem* physicSystem;
	PhysicsDebugDraw* physicsDebugDraw;

	sf::Clock clock;
	float deltaTime;

	//временно
	GameObject* ship;
	GameObject* floor;
};

