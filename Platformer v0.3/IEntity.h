#pragma once

#include "DataTypes.h"
#include "Debug.h"
//typedef unsigned int EntityTypeId;

class IEntity
{
public:
	IEntity() : entityId(entityIdCounter++) {}
	virtual ~IEntity()
	{
		Debug::LogWarning("Destructor", typeid(*this).name());
	}
	//virtual void EarlyUpdate(float deltaTime) = 0;
	//virtual void Update(float deltaTime) = 0;
	//virtual void LateUpdate(float deltaTime) = 0;
	virtual void EarlyUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	//virtual void Draw(Window* window) = 0;

	inline const EntityId GetEntityId() const { return entityId; }

protected:
	EntityId entityId;

	static EntityId entityIdCounter;
};


