#include "GarbageCollector.h"

void GarbageCollector::DestroyEntity(EntityId entityId)
{
	Debug::LogWarning("Deleting entity with id: " + std::to_string(entityId), typeid(GarbageCollector).name());
	//TODO добавить очистку из всех систем
	//TODO после написания коллекции объектов для сцены выпиливать объект оттуда

	//RenderSystem::DeleteDrawable(entityId);
	//EntityManager::DestroyEntity(entityId);
	//ObjectCollection::DeleteObject(entityId);
}

void GarbageCollector::DestroyComponent(ComponentId componentId)
{
	//ComponentManager::DestroyComponent(componentId);
}