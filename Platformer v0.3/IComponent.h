#pragma once

#include "DataTypes.h"
#include "EntityManager.h"
#include "Debug.h"

class IComponent
{
public:
	IComponent() : componentId(componentIdCounter++) 
	{}
	virtual ~IComponent()
	{
		Debug::LogWarning("Deleted with id: " + std::to_string(componentId), typeid(*this).name());
	}

	virtual void EarlyUpdate(float deltaTime) {}
	virtual void Update(float deltaTime) {}
	virtual void LateUpdate(float deltaTime) {}

	virtual void Draw(Window* window) {}

	virtual void OnDestroy() {}

	void Destroy()
	{
		OnDestroy();
		delete this;
	}

	inline const ComponentId GetComponentId() const { return componentId; }

	inline void SetOwner(EntityId id) {	ownerId = id; }
	inline EntityId GetOwner() const { return ownerId; }

protected:
	ComponentId componentId;
	EntityId ownerId;

private:
	static ComponentId componentIdCounter;
};

