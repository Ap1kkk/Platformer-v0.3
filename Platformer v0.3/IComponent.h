#pragma once

#include "Time.h"
#include "DataTypes.h"
#include "EntityManager.h"
#include "ObjectContext.h"
#include "Debug.h"

#include "OnComponentDestroyedEvent.h"

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
	virtual void UpdateUI() {}

	virtual void Draw(Window* window) {}

	virtual void OnCollisionEnter(b2Contact* contact) {}
	virtual void OnCollisionExit(b2Contact* contact) {}

	/// <summary>
	/// Called before destroying component
	/// </summary>
	virtual void OnDestroy() {}

	void Destroy()
	{
		EventData data(OnComponentDestroyedEvent::GetType());
		data.id = componentId;

		OnDestroy();
		OnComponentDestroyedEvent::Invoke(data);
		delete this;
	}

	inline const ComponentId GetComponentId() const { return componentId; }

	inline void SetOwnerId(EntityId id) {	ownerId = id; }
	inline EntityId GetOwnerId() const { return ownerId; }

	inline void SetComponentLayer(ComponentLayer layer) { componentLayer = layer; }
	inline ComponentLayer GetComponentLayer() const { return componentLayer; }

	inline void SetObjectContext(ObjectContext context) { objectContext = context; }

protected:
	ComponentId componentId;
	ComponentLayer componentLayer;
	EntityId ownerId;
	ObjectContext objectContext;

private:
	static ComponentId componentIdCounter;
};

