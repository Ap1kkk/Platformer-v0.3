#pragma once

#include "Time.h"
#include "DataTypes.h"
#include "EntityManager.h"
#include "ObjectContext.h"
#include "Debug.h"

#include "OnComponentUserData.h"

class IComponent
{
public:
	IComponent() : componentId(componentIdCounter++), isEnabled(true)
	{}
	virtual ~IComponent()
	{
		Debug::LogWarning("Deleted with id: " + std::to_string(componentId), typeid(*this).name());
	}

	virtual void Awake() {}

	void Enable() 
	{
		OnEnable();

		EventData data(EventType::OnComponentEnabledEvent);
		auto userData = new ComponentUserData;
		userData->component = this;

		data.id = ownerId;
		data.userData = userData;

		Event::Invoke(data);
		isEnabled = true;

	}
	void Disable() 
	{
		OnDisable();

		EventData data(EventType::OnComponentDisabledEvent);

		auto userData = new ComponentUserData;
		userData->component = this;

		data.id = ownerId;
		data.userData = userData;

		Event::Invoke(data);
		isEnabled = false;

	}

	bool IsEnabled() const { return isEnabled; }

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

	virtual void OnEnable() {}
	virtual void OnDisable() {}

	void Destroy()
	{
		EventData data(EventType::OnComponentDestroyedEvent);
		data.id = componentId;

		OnDestroy();
		Event::Invoke(data);
		delete this;
	}

	inline const ComponentId GetComponentId() const { return componentId; }

	inline void SetOwnerId(EntityId id) {	ownerId = id; }
	inline EntityId GetOwnerId() const { return ownerId; }

	inline void SetComponentLayer(ComponentLayer layer) { componentLayer = layer; }
	inline ComponentLayer GetComponentLayer() const { return componentLayer; }

	inline void SetObjectContext(ObjectContext context) { objectContext = context; }

protected:
	bool isEnabled;
	const ComponentId componentId;
	ComponentLayer componentLayer;
	EntityId ownerId;
	ObjectContext objectContext;

private:
	static ComponentId componentIdCounter;
};

