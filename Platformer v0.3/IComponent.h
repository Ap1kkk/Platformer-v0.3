#pragma once

#include "DataTypes.h"
//typedef unsigned int ComponentTypeId;
#include "Debug.h"
#include "EntityManager2.h"

class IComponent
{
public:
	IComponent() : componentId(componentIdCounter++) {}
	virtual ~IComponent()
	{
		Debug::LogWarning("Destructor", typeid(*this).name());
	}

	//virtual void EarlyUpdate(float deltaTime) = 0;
	//virtual void Update(float deltaTime) = 0;
	//virtual void LateUpdate(float deltaTime) = 0;
	virtual void EarlyUpdate() {}
	virtual void Update() {}
	virtual void LateUpdate() {}

	//virtual void Draw(Window* window) {}

	inline const ComponentId GetComponentId() const { return componentId; }

	inline void SetOwner(EntityId id) 
	{
		ownerId = id;
	}
	inline EntityId GetOwner() const { return ownerId; }

protected:
	ComponentId componentId;
	EntityId ownerId;
	//IEntity* ownerPtr;

private:
	static ComponentId componentIdCounter;
};

