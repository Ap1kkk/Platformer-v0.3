#pragma once

#include <unordered_map>

#include "IEntity.h"
#include "Debug.h"

class ObjectCollection
{
public:
	ObjectCollection() {}

	static void AddObject(IEntity* newObject)
	{
		EntityId entityId = newObject->GetEntityId();
		auto itr = objects.find(entityId);
		if (itr == objects.end())
		{
			objects.emplace(entityId, newObject);
		}
		else
		{
			Debug::LogWarning("Object with id: " + std::to_string(entityId) + " has already added", typeid(ObjectCollection).name());
		}
	}

	/// Удаляет объект из коллекции но не вызывает метод Destroy у объекта
	static void DeleteObject(EntityId entityId)
	{
		auto itr = objects.find(entityId);
		if (itr != objects.end())
		{
			objects.erase(itr);
		}
		else
		{
			Debug::LogWarning("Object with id: " + std::to_string(entityId) + " was not found", typeid(ObjectCollection).name());
		}
	}

	// Вызывает у всех хранящихся объектов метод Destroy
	static void Clear()
	{
		if (objects.size() > 0)
		{
			auto itr = objects.end();
			itr--;
			while (itr != objects.end())
			{
				if (objects.size() > 1)
				{
					(itr--)->second->Destroy();
				}
				else
				{
					itr = objects.begin();
					itr->second->Destroy();
					break;
				}
			}
		}
	}

	static void EarlyUpdate(float deltaTime) 
	{
		for (auto& object : objects)
		{
			object.second->EarlyUpdate(deltaTime);
		}
	}
	static void Update(float deltaTime) 
	{
		for (auto& object : objects)
		{
			object.second->Update(deltaTime);
		}
	}
	static void LateUpdate(float deltaTime) 
	{
		for (auto& object : objects)
		{
			object.second->LateUpdate(deltaTime);
		}
	}

private:
	static std::unordered_map<EntityId, IEntity*> objects;
};

