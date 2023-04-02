#include "Entity.h"

Entity::~Entity()
{
	if (components.size() > 0)
	{
		for (auto& component : components)
		{
			auto componentId = component.second->GetComponentId();
			GarbageCollector::DestroyComponent(componentId);
		}
	}
}

void Entity::DeleteComponent(ComponentId id)
{
	auto componentType = ComponentManager::GetComponentTypeById(id);
	auto itr = components.find(componentType);
	if (itr != components.end())
	{
		ComponentManager::DestroyComponent(id);
		//if (componentType == typeid(DrawableComponent).name())
		//{

		//}
		components.erase(itr);
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
	if (notAwokenComponents.size() > 0)
	{
		for (auto& component : notAwokenComponents)
		{
			component->Awake();
		}
	}
}

void Entity::ComponentsEarlyUpdate()
{
	for (auto& component : componentsOrder)
	{
		component->EarlyUpdate();
	}
}

void Entity::ComponentsUpdate()
{
	for (auto& component : componentsOrder)
	{
		component->Update();
	}
}

void Entity::ComponentsLateUpdate()
{
	for (auto& component : componentsOrder)
	{
		component->LateUpdate();
	}
}

void Entity::ComponentsUpdateUI()
{
	for (auto& component : componentsOrder)
	{
		component->UpdateUI();
	}
}

void Entity::Destroy()
{
	OnDestroy();

	for (auto& component : components)
	{

		auto componentId = component.second->GetComponentId();
		GarbageCollector::DestroyComponent(componentId);
	}
	components.clear();

	GarbageCollector::DestroyEntity(this->entityId);
}


