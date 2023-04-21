#pragma once

#include <unordered_map>

#include "IEntity.h"
#include "Debug.h"

#include "EventListener.h"
#include "OnEntityDestroyedEvent.h"

/// <summary>
/// Static class responsible for storing and processing existing objects on scene
/// </summary>
class ObjectCollection : public EventListener
{
public:
	ObjectCollection() {}

	void SubscribeOnEvents()
	{
		SubscribeOnEvent<OnEntityDestroyedEvent>();
	}

	void OnEventHappened(const EventData& data)
	{
		if (data.eventType == OnEntityDestroyedEvent::GetType())
		{
			Debug::Log("Deleting entity with id: " + std::to_string(data.id), typeid(*this).name());
			DeleteObject(data.id);
		}
	}

	static void AddObject(IEntity* newObject);
	static void AddUiObject(IEntity* newObject);

	/// <summary>
	/// Delete an object from the storage
	/// But does not call the Destroy method
	/// </summary>
	/// <param name="entityId"></param>
	static void DeleteObject(EntityId entityId);

	/// <summary>
	/// Destroy all existing objects
	/// </summary>
	static void Clear();

	static void ClearNotBuffured();

	static void ProcessNotAwoken();

	/// ���� ��������������
	static void ProcessNotAwokenComponents();

	static void EarlyUpdate();
	static void Update();
	static void LateUpdate();

	static void UpdateUI();

	static void HasNotAwokenComponents(EntityId entityId);

	static void MoveAllToPauseBuffer();
	static void RetrieveAllFromPauseBuffer();


private:
	static std::unordered_map<EntityId, IEntity*> allObjects;
	static std::unordered_map<EntityId, IEntity*> pausedObjects;
	static std::unordered_map<EntityId, IEntity*> unpausedObjects;

	static std::unordered_map<EntityId, IEntity*> uiObjects;
	static std::unordered_map<EntityId, IEntity*> uiObjectsBuffer;

	//TODO ���� ���������� �� multimap
	static std::vector<IEntity*> notAwokenObjects;
	static std::vector<IEntity*> withNotAwokenComponents;
	static bool hasNotAwokenComponents;

	static bool isEnabledToUpdate;
};

