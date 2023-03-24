#include "GarbageCollector.h"

void GarbageCollector::DestroyEntity(EntityId entityId)
{
	Debug::LogWarning("Deleting entity with id: " + std::to_string(entityId), typeid(GarbageCollector).name());
	//TODO добавить очистку из всех систем
	//TODO после написания коллекции объектов для сцены выпиливать объект оттуда
	EntityManager::DestroyEntity(entityId);
	RenderSystem::DeleteDrawable(entityId);
	ObjectCollection::DeleteObject(entityId);
}

void GarbageCollector::DestroyComponent(ComponentId componentId)
{
	ComponentManager::DestroyComponent(componentId);
}