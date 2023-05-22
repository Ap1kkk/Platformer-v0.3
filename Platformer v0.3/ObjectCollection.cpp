#include "ObjectCollection.h"

std::unordered_map<EntityId, IEntity*> ObjectCollection::allObjects = {};
std::unordered_map<EntityId, IEntity*> ObjectCollection::unpausedObjects = {};
std::unordered_map<EntityId, IEntity*> ObjectCollection::pausedObjects = {};

std::unordered_map<EntityId, IEntity*> ObjectCollection::uiObjects = {};
std::unordered_map<EntityId, IEntity*> ObjectCollection::uiObjectsBuffer = {};

std::vector<IEntity*> ObjectCollection::notAwokenObjects = {};
std::vector<IEntity*> ObjectCollection::withNotAwokenComponents = {};

bool ObjectCollection::hasNotAwokenComponents = false;
bool ObjectCollection::isEnabledToUpdate = true;

void ObjectCollection::AddObject(IEntity* newObject)
{
	EntityId entityId = newObject->GetEntityId();
	auto itr = allObjects.find(entityId);
	if (itr == allObjects.end())
	{
		allObjects.emplace(entityId, newObject);
		unpausedObjects.emplace(entityId, newObject);
		notAwokenObjects.emplace_back(newObject);
	}
	else
	{
		Debug::LogWarning("Object with id: " + std::to_string(entityId) + " has already added", typeid(ObjectCollection).name());
	}
}

void ObjectCollection::AddUiObject(IEntity* newObject)
{
	EntityId entityId = newObject->GetEntityId();
	auto itr = allObjects.find(entityId);
	if (itr == allObjects.end())
	{
		allObjects.emplace(entityId, newObject);
		uiObjects.emplace(entityId, newObject);
		notAwokenObjects.emplace_back(newObject);
	}
	else
	{
		Debug::LogWarning("UI object with id: " + std::to_string(entityId) + " has already added", typeid(ObjectCollection).name());
	}
}

void ObjectCollection::DeleteObject(EntityId entityId)
{
	auto itr = allObjects.find(entityId);
	if (itr != allObjects.end())
	{
		allObjects.erase(itr);
		auto itr2 = unpausedObjects.find(entityId);
		if (itr2 != unpausedObjects.end())
		{
			unpausedObjects.erase(itr2);
			return;
		}
		auto itr3 = pausedObjects.find(entityId);
		if (itr3 != pausedObjects.end())
		{
			pausedObjects.erase(itr3);
			return;
		}

		auto itr4 = uiObjects.find(entityId);
		if (itr4 != uiObjects.end())
		{
			uiObjects.erase(itr4);
			return;
		}
		auto itr5 = uiObjects.find(entityId);
		if (itr5 != uiObjects.end())
		{
			uiObjects.erase(itr5);
			return;
		}
	}
	else
	{
		Debug::LogWarning("Object with id: " + std::to_string(entityId) + " was not found", typeid(ObjectCollection).name());
	}
}

void ObjectCollection::Clear()
{
	if (allObjects.size() > 0)
	{
		auto itr = allObjects.end();
		itr--;
		while (itr != allObjects.end())
		{
			if (allObjects.size() > 1)
			{
				(itr--)->second->Destroy();
			}
			else
			{
				itr = allObjects.begin();
				itr->second->Destroy();
				break;
			}
		}
	}

	//// не работает, ошибка памяти
	//for (auto& object : allObjects)
	//{
	//	object.second->Destroy();
	//}
	//allObjects.clear();
}

void ObjectCollection::ClearNotBuffured()
{
	if (unpausedObjects.size() > 0)
	{
		auto itr = unpausedObjects.end();
		itr--;
		while (itr != unpausedObjects.end())
		{
			if (unpausedObjects.size() > 1)
			{
				(itr--)->second->Destroy();
			}
			else
			{
				itr = unpausedObjects.begin();
				itr->second->Destroy();
				break;
			}
		}
	}

	if (uiObjects.size() > 0)
	{
		auto itr = uiObjects.end();
		itr--;
		while (itr != uiObjects.end())
		{
			if (uiObjects.size() > 1)
			{
				(itr--)->second->Destroy();
			}
			else
			{
				itr = uiObjects.begin();
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
	for (auto& object : unpausedObjects)
	{
		object.second->ComponentsEarlyUpdate();
		object.second->EarlyUpdate();
	}
	for (auto& object : uiObjects)
	{
		object.second->ComponentsEarlyUpdate();
		object.second->EarlyUpdate();
	}
}

void ObjectCollection::Update()
{
	for (auto& object : unpausedObjects)
	{
		object.second->ComponentsUpdate();
		object.second->Update();
	}
	for (auto& object : uiObjects)
	{
		object.second->ComponentsUpdate();
		object.second->Update();
	}
}

void ObjectCollection::LateUpdate()
{
	for (auto& object : unpausedObjects)
	{
		object.second->ComponentsLateUpdate();
		object.second->LateUpdate();
	}
	for (auto& object : uiObjects)
	{
		object.second->ComponentsLateUpdate();
		object.second->LateUpdate();
	}
}

void ObjectCollection::UpdateUI()
{
	for (auto& object : uiObjects)
	{
		object.second->UpdateViewCenter();
		object.second->UpdateUI();
		object.second->ComponentsUpdateUI();
	}
}

void ObjectCollection::HasNotAwokenComponents(EntityId entityId)
{
	hasNotAwokenComponents = true;
	auto itr = allObjects.find(entityId);
	if (itr != allObjects.end())
	{

		withNotAwokenComponents.emplace_back(itr->second);
	}
	else
	{
		Debug::LogWarning("Object with id: " + std::to_string(entityId) + " was not found", typeid(ObjectCollection).name());
	}

}

void ObjectCollection::MoveAllToPauseBuffer()
{
	for (auto& object : unpausedObjects)
	{
		pausedObjects.emplace(object);
		//object.first, object.second
	}
	unpausedObjects.clear();

	for (auto& object : uiObjects)
	{
		uiObjectsBuffer.emplace(object);
	}
	uiObjects.clear();

	Debug::LogInfo("All objects moved to pause buffer", typeid(ObjectCollection).name());
}

void ObjectCollection::RetrieveAllFromPauseBuffer()
{
	for (auto& object : pausedObjects)
	{
		unpausedObjects.emplace(object);
		//object.first, object.second
	}
	pausedObjects.clear();

	for (auto& object : uiObjectsBuffer)
	{
		uiObjects.emplace(object);
	}
	uiObjectsBuffer.clear();

	Debug::LogInfo("All objects removed from pause buffer", typeid(ObjectCollection).name());
}
