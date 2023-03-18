#pragma once

#include "Time.h"
#include "DataTypes.h"
#include "EntityManager.h"
#include "ObjectContext.h"
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

	virtual void Awake() {}

	virtual void EarlyUpdate() {}
	virtual void Update() {}
	virtual void LateUpdate() {}

	virtual void Draw(Window* window) {}

	/// <summary>
	/// Called before destroying component
	/// </summary>
	virtual void OnDestroy() {}

	void Destroy()
	{
		OnDestroy();
		delete this;
	}

	inline const ComponentId GetComponentId() const { return componentId; }

	inline void SetOwner(EntityId id) {	ownerId = id; }
	inline EntityId GetOwner() const { return ownerId; }

	inline void SetLayer(ComponentLayer layer) { componentLayer = layer; }
	inline ComponentLayer GetLayer() const { return componentLayer; }

	inline void SetObjectContext(ObjectContext context) { objectContext = context; }

protected:
	ComponentId componentId;
	ComponentLayer componentLayer;
	EntityId ownerId;
	ObjectContext objectContext;

private:
	static ComponentId componentIdCounter;
};

