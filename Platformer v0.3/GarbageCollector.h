#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"
#include "RenderSystem.h"
#include "ObjectCollection.h"

#include "Debug.h"

class GarbageCollector
{
public:
	// Методы для очистки объекта во всех системах

	static void DestroyEntity(EntityId entityId)
	{
		Debug::LogWarning("Deleting entity with id: " + std::to_string(entityId), typeid(GarbageCollector).name());
		//TODO добавить очистку из всех систем
		//TODO после написания коллекции объектов для сцены выпиливать объект оттуда
		EntityManager::DestroyEntity(entityId);
		RenderSystem::DeleteDrawable(entityId);
		ObjectCollection::DeleteObject(entityId);
	}

	static void DestroyComponent(ComponentId componentId)
	{
		ComponentManager::DestroyComponent(componentId);
	}
};