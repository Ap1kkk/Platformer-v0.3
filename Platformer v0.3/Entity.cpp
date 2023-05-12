#include "Entity.h"

Entity::~Entity()
{
	UnsubscribeFromEvent(EventType::OnComponentEnabledEvent);

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

void Entity::RecalculateComponentsOrder()
{
	std::sort(componentsOrder.begin(), componentsOrder.end(),
		[](IComponent* a, IComponent* b)
		{
			ComponentLayer aLayer = a->GetComponentLayer();
			ComponentLayer bLayer = b->GetComponentLayer();
			return aLayer < bLayer;
		});
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
	//for (auto& component : componentsOrder)
	//{
	//	component->EarlyUpdate();
	//}

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
	//for (auto& component : componentsOrder)
	//{
	//	component->Update();
	//}

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
	//for (auto& component : componentsOrder)
	//{
	//	component->LateUpdate();
	//}

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
	//for (auto& component : componentsOrder)
	//{
	//	component->UpdateUI();
	//}

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

	//GarbageCollector::DestroyEntity(this->entityId);
	Event::Invoke(entityData);
}


