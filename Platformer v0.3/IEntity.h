#pragma once

#include "DataTypes.h"
#include "Debug.h"

class IEntity
{
public:
	IEntity() : entityId(entityIdCounter++) {}
	virtual ~IEntity()
	{
		//Debug::LogWarning("Destructor", typeid(*this).name());
		Debug::LogWarning("Deleted with id: " + std::to_string(entityId), typeid(*this).name());
	}
	virtual void EarlyUpdate(float deltaTime) {}
	virtual void Update(float deltaTime) {}
	virtual void LateUpdate(float deltaTime) {}

	virtual void Draw(Window* window) {}

	virtual void OnDestroy() {}

	virtual void Destroy() = 0;

	inline const EntityId GetEntityId() const { return entityId; }

protected:
	EntityId entityId;

private:
	static EntityId entityIdCounter;
};


