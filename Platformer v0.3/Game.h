#pragma once

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include "AssetAllocator.h"
#include "Window.h"
#include "EntityManager.h"
#include "SceneManager.h"
#include "PhysicSystem.h"
#include "RenderSystem.h"
#include "Input.h"
#include "PhysicsDebugDraw.h"
#include "SharedContext.h"
#include "ObjectCollection.h"
#include "FirstScene.h"
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
	RenderSystem* renderSystem;
	PhysicsDebugDraw* physicsDebugDraw;
	SceneManager* sceneManager;

	SharedContext sharedContext;

	sf::Clock clock;
	float deltaTime;
};

