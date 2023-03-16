#pragma once

#include <any>
#include <unordered_map>

#include "IEntity.h"
#include "Component.h"
#include "Debug.h"

#include "ComponentManager.h"

#include "GarbageCollector.h"

class Entity : public IEntity
{
public:
	Entity() {}
	virtual ~Entity() 
	{
		//Debug::LogWarning("Destructor", typeid(*this).name());
		if (components.size() > 0)
		{
			for (auto& component : components)
			{
				auto componentId = component.second->GetComponentId();
				GarbageCollector::DestroyComponent(componentId);
			}
		}
	}

	template<class C>
	C* AddComponent()
	{
		ComponentType compType = typeid(C).name();

		auto itr = components.find(compType);
		if (itr == components.end())
		{
			auto component = ComponentManager::CreateComponent<C>();
			component->SetOwner(entityId);
			components.insert(std::make_pair(compType, static_cast<IComponent*>(component)));
			return component;
		}
		else
		{
			Debug::LogError("Component with type " + compType + " was already attached");
			return nullptr;
		}
	}

	template<class C>
	C* GetComponent() const
	{
		ComponentType componentType = typeid(C).name();
		auto itr = components.find(componentType);
		if (itr != components.end())
		{
			for (auto& component : components)
			{
				if (component.first == componentType)
				{
					return static_cast<C*>(component.second);
				}
			}
		}
		else
		{
			Debug::LogError("Component wasn't found");
			return nullptr;
		}
	}
	
	void DeleteComponent(ComponentId id)
	{
		auto itr = components.find(ComponentManager::GetComponentTypeById(id));
		if (itr != components.end())
		{
			ComponentManager::DestroyComponent(id);
			components.erase(itr);
		}
	}
	
	// TODO если дважды вызвать этот метод до будет выбрасываться исключение в list.h которое нельзя поймать 
	// Поэтому я хз как это фиксить :)
	void Destroy() override
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

private:
	std::unordered_map<ComponentType, IComponent*> components;
};