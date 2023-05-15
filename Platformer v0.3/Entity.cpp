#include "Entity.h"

Entity::~Entity()
{
	UnsubscribeFromEvent(EventType::OnComponentEnabledEvent);
	UnsubscribeFromEvent(EventType::OnComponentDisabledEvent);

	if (components.size() > 0)
	{
		for (auto& component : components)
		{
			auto componentId = component.second->GetComponentId();
			GarbageCollector::DestroyComponent(componentId);
		}
	}

	for (auto& map : enabledComponents)
	{
		delete map.second;
	}
}

void Entity::ProcessNotAwokenComponents()
{
	//TODO вызывать после события
	if (notAwokenComponents.size() > 0)
	{
		for (auto& component : notAwokenComponents)
		{
			component->Awake();
		}
		notAwokenComponents.clear();
	}
}

void Entity::ComponentsEarlyUpdate()
{
	for (auto& componentsMap : enabledComponents)
	{
		for (auto& pair : *componentsMap.second)
		{
			pair.second->EarlyUpdate();
		}
	}
}

void Entity::ComponentsUpdate()
{
	for (auto& componentsMap : enabledComponents)
	{
		for (auto& pair : *componentsMap.second)
		{
			pair.second->Update();
		}
	}
}

void Entity::ComponentsLateUpdate()
{
	for (auto& componentsMap : enabledComponents)
	{
		for (auto& pair : *componentsMap.second)
		{
			pair.second->LateUpdate();
		}
	}
}

void Entity::ComponentsUpdateUI()
{
	for (auto& componentsMap : enabledComponents)
	{
		for (auto& pair : *componentsMap.second)
		{
			pair.second->UpdateUI();
		}
	}
}

void Entity::Destroy()
{
	EventData entityData(EventType::OnEntityDestroyedEvent);
	entityData.id = entityId;

	OnDestroy();

	for (auto& component : components)
	{
		component.second->Destroy();
	}
	components.clear();

	Event::Invoke(entityData);
}


