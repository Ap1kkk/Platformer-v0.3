#pragma once

#include "Time.h"
#include "DataTypes.h"
#include "ObjectContext.h"
#include "Debug.h"

/// <summary>
/// Interface for any game objects
/// </summary>
class IEntity
{
public:
	IEntity() : entityId(entityIdCounter++) {}
	virtual ~IEntity();

	virtual void Awake() {}

	virtual void EarlyUpdate() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void Draw(Window* window) {}

	virtual void UpdateUI() {}
	virtual void UpdateViewCenter() {}

	virtual void ProcessNotAwokenComponents() = 0;

	virtual void ComponentsEarlyUpdate() = 0;
	virtual void ComponentsUpdate() = 0;
	virtual void ComponentsLateUpdate() = 0;
	virtual void ComponentsUpdateUI() = 0;

	virtual void OnCollisionEnter(b2Contact* contact) {}
	virtual void OnCollisionExit(b2Contact* contact) {}

	virtual void OnDestroy() {}

	virtual void Destroy() = 0;

	inline const EntityId GetEntityId() const { return entityId; }

	inline void SetObjectContext(ObjectContext context) { objectContext = context; }

protected:
	EntityId entityId;
	ObjectContext objectContext;

private:
	static EntityId entityIdCounter;
};


