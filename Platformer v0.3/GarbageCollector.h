#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"
#include "RenderSystem.h"
#include "ObjectCollection.h"

#include "Debug.h"

/// <summary>
/// Responsible for correct deleting of objects
/// </summary>
class GarbageCollector
{
public:
	/// <summary>
	/// Delete pointer to an destoryed object from all systems
	/// </summary>
	/// <param name="entityId"></param>
	static void DestroyEntity(EntityId entityId);

	static void DestroyComponent(ComponentId componentId);
};