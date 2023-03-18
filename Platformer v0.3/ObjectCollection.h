#pragma once

#include <unordered_map>

#include "IEntity.h"
#include "Debug.h"

/// <summary>
/// Static class responsible for storing and processing existing objects on scene
/// </summary>
class ObjectCollection
{
public:
	ObjectCollection() {}

	static void AddObject(IEntity* newObject);

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

	static void ProcessNotAwoken();

	/// надо оптимизировать
	static void ProcessNotAwokenComponents();

	static void EarlyUpdate();
	static void Update();
	static void LateUpdate();

	static void HasNotAwokenComponents(EntityId entityId);

private:
	static std::unordered_map<EntityId, IEntity*> objects;
	static std::vector<IEntity*> notAwokenObjects;
	static std::vector<IEntity*> withNotAwokenComponents;
	static bool hasNotAwokenComponents;
};

