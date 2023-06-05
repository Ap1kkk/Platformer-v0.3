#pragma once

#include <unordered_map>

#include "IEntity.h"
#include "Debug.h"

#include "EventListener.h"

class EntityManager : public EventListener
{
public:
	EntityManager();
	~EntityManager();

	void SubscribeOnEvents()
	{
		SubscribeOnEvent(EventType::OnEntityDestroyedEvent);
	}

	void OnEventHappened(EventData& data) override
	{
		if (data.eventType == EventType::OnEntityDestroyedEvent)
		{
			Debug::Log("Deleting entity with id: " + std::to_string(data.id), typeid(*this).name());
			DestroyEntity(data.id);
		}
	}

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

	static void DestroyEntity(EntityId entityId);

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

	//template<class C>
	//static C* GetComponentByEntityId(EntityId id)
	//{
	//	auto itr = entities.find(id);
	//	if (itr != entities.end())
	//	{			
	//		return static_cast<C*>((*itr).second);
	//	}
	//	else
	//	{
	//		Debug::LogWarning("Entity with id: " + std::to_string(id) + " not found");
	//		return nullptr;
	//	}
	//}

private:
	static std::unordered_map<EntityId, IEntity*> entities;
};

