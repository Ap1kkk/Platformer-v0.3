#include "EntityManager.h"

std::unordered_map<EntityId, IEntity*> EntityManager::entities = {};

EntityManager::EntityManager()
{
	Debug::Log("Initialized", typeid(*this).name());
}

EntityManager::~EntityManager()
{
	for (auto& entity : entities)
	{
		delete entity.second;
	}

}

void EntityManager::DestroyEntity(EntityId entityId)
{
	auto itr = entities.find(entityId);
	if (itr != entities.end())
	{
		auto entity = (*itr).second;
		delete entity;
		entities.erase(itr);
		Debug::LogWarning("Entity with id: " + std::to_string(entityId) + " was deleted", typeid(EntityManager).name());
	}
}