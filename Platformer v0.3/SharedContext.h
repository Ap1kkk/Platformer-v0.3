#pragma once

#include "Window.h"
#include "EntityManager.h"
#include "PhysicSystem.h"
#include "RenderSystem.h"
#include "TileManager.h"

struct SharedContext
{
	Window* window;
	const AssetAllocator* assetAllocator;
	const EntityManager* entityManger;
	const PhysicSystem* physicSystem;
	const PhysicsDebugDraw* physicsDebugDraw;
	const RenderSystem* renderSystem;
	TileManager* tileManager;
};
