#pragma once

#include <unordered_map>

#include "IEntity.h"
#include "Debug.h"


/// <summary>
/// Responsibe for creatind, destroyig and searching existing objects
/// </summary>
class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	/// <summary>
	/// Creates new object of specified type
	/// </summary>
	/// <typeparam name="E"></typeparam>
	/// <param name="context">Object context which contains pointers to global objects</param>
	/// <returns>Pointer to created object</returns>
	template<class E>
	static E* const CreateEntity(ObjectContext context)
	{
		auto entity = new E;
		EntityId id = entity->GetEntityId();
		entities.insert(std::make_pair(id, static_cast<IEntity*>(entity)));
		entity->SetObjectContext(context);
		Debug::LogInfo("Entity with id: " + std::to_string(id) + " was created", typeid(EntityManager).name());
		return entity;
	}

	/// <summary>
	/// Destroys object and clears memory after it
	/// </summary>
	/// <param name="entityId">Id of an object which is going to be destroyed</param>
	static void DestroyEntity(EntityId entityId);
	
	/// <summary>
	/// Searches object with specified id
	/// </summary>
	/// <typeparam name="C"></typeparam>
	/// <param name="id"></param>
	/// <returns>Poiter to an object if it is found otherwise nullptr</returns>
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

	template<class C>
	static C* GetComponentByEntityId(EntityId id)
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

