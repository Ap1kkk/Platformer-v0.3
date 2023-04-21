#pragma once

#include "Window.h"
#include "ObjectCollection.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "PhysicSystem.h"
#include "RenderSystem.h"
#include "TileManager.h"
#include "ISceneManager.h"
#include "IGameStateMachine.h"
#include "WorldContactListener.h"
#include "EventSystem.h"

struct SharedContext
{
	Window* window;
	ObjectCollection* objectCollection;
	AssetAllocator* assetAllocator;
	EntityManager* entityManger;
	ComponentManager* componentManager;
	PhysicSystem* physicSystem;
	PhysicsDebugDraw* physicsDebugDraw;
	RenderSystem* renderSystem;
	TileManager* tileManager;
	ISceneManager* sceneManager;
	IGameStateMachine* gameStateMachine;
	WorldContactListener* worldContactListener;
	EventSystem* eventSystem;

	//TODO добавить менеджера загрузки сохранений
};
