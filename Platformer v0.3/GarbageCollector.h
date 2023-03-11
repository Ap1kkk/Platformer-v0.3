#pragma once

#include "EntityManager2.h"
#include "ComponentManager.h"

class GarbageCollector
{
public:
	// Методы для очистки объекта во всех системах

	static void DestroyEntity(EntityId entityId)
	{
		//TODO добавить очистку из всех систем
		EntityManager2::DestroyEntity(entityId);
	}

	static void DestroyComponent(ComponentId componentId)
	{
		ComponentManager::DestroyComponent(componentId);
	}

	//TODO добавить выключение и включение объекта в системе физики и отрисовки
};