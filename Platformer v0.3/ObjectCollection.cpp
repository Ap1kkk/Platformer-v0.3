#include "ObjectCollection.h"

std::unordered_map<EntityId, IEntity*> ObjectCollection::objects = {};
std::vector<IEntity*> ObjectCollection::notAwokenObjects = {};
std::vector<IEntity*> ObjectCollection::withNotAwokenComponents = {};
bool ObjectCollection::hasNotAwokenComponents = false;

void ObjectCollection::AddObject(IEntity* newObject)
{
	EntityId entityId = newObject->GetEntityId();
	auto itr = objects.find(entityId);
	if (itr == objects.end())
	{
		objects.emplace(entityId, newObject);
		notAwokenObjects.emplace_back(newObject);
	}
	else
	{
		Debug::LogWarning("Object with id: " + std::to_string(entityId) + " has already added", typeid(ObjectCollection).name());
	}
}

void ObjectCollection::DeleteObject(EntityId entityId)
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

void ObjectCollection::Clear()
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

void ObjectCollection::ProcessNotAwoken()
{
	if (notAwokenObjects.size() > 0)
	{
		for (auto& object : notAwokenObjects)
		{
			object->Awake();
			object->ProcessNotAwokenComponents();
		}
		notAwokenObjects.clear();
	}
}

void ObjectCollection::ProcessNotAwokenComponents()
{
	if (hasNotAwokenComponents && withNotAwokenComponents.size() > 0)
	{
		for (auto& object : notAwokenObjects)
		{
			object->ProcessNotAwokenComponents();
		}
		hasNotAwokenComponents = false;
		withNotAwokenComponents.clear();
	}
}

void ObjectCollection::EarlyUpdate()
{
	for (auto& object : objects)
	{
		object.second->EarlyUpdate();
		object.second->ComponentsEarlyUpdate();
	}
}

void ObjectCollection::Update()
{
	for (auto& object : objects)
	{
		object.second->Update();
		object.second->ComponentsUpdate();
	}
}

void ObjectCollection::LateUpdate()
{
	for (auto& object : objects)
	{
		object.second->LateUpdate();
		object.second->ComponentsLateUpdate();
	}
}

void ObjectCollection::HasNotAwokenComponents(EntityId entityId)
{
	{
		hasNotAwokenComponents = true;
		auto itr = objects.find(entityId);
		if (itr != objects.end())
		{

			withNotAwokenComponents.emplace_back(itr->second);
		}
		else
		{
			Debug::LogWarning("Object with id: " + std::to_string(entityId) + " was not found", typeid(ObjectCollection).name());
		}
	}
}
