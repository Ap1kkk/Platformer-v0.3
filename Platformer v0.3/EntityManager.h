#pragma once

#include <unordered_map>

#include "IEntity.h"
#include "Debug.h"

#include <iostream>

class EntityManager
{
public:
	EntityManager()
	{
		Debug::Log("Initialized", typeid(*this).name());
	}
	~EntityManager() 
	{
		for (auto& entity : entities)
		{
			delete entity.second;
		}

	}

	template<class E>
	static E* const CreateEntity()
	{
		auto entity = new E;
		EntityId id = entity->GetEntityId();
		entities.insert(std::make_pair(id, static_cast<IEntity*>(entity)));
		Debug::LogInfo("Entity with id: " + std::to_string(id) + " was created", typeid(EntityManager).name());
		return entity;
	}

	static void DestroyEntity(EntityId entityId)
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
	
	template<class C>
	static C* GetEntityById(EntityId id)
	{
		auto itr = entities.find(id);
		if (itr != entities.end())
		{
			return static_cast<C*>((*itr).second);
		}
		else
		{
			Debug::LogWarning("Entity with id: " + std::to_string(id) + " not found");
			return nullptr;
		}
	}

private:
	static std::unordered_map<EntityId, IEntity*> entities;
};

