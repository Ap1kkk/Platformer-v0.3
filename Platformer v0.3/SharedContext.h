#pragma once

#include "Window.h"
#include "ObjectCollection.h"
#include "EntityManager.h"
#include "PhysicSystem.h"
#include "RenderSystem.h"
#include "TileManager.h"
#include "ISceneManager.h"
#include "IGameStateMachine.h"

struct SharedContext
{
	Window* window;
	ObjectCollection* objectCollection;
	AssetAllocator* assetAllocator;
	EntityManager* entityManger;
	PhysicSystem* physicSystem;
	PhysicsDebugDraw* physicsDebugDraw;
	RenderSystem* renderSystem;
	TileManager* tileManager;
	ISceneManager* sceneManager;
	IGameStateMachine* gameStateMachine;

	//TODO добавить менеджера загрузки сохранений
};
