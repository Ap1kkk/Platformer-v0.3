#pragma once

#include <any>
#include <unordered_map>

#include "IEntity.h"
#include "Component.h"
#include "Debug.h"

#include "ComponentManager.h"

#include "GarbageCollector.h"

class Entity2 : public IEntity
{
public:
	Entity2() {}
	virtual ~Entity2() 
	{
		Debug::LogWarning("Destructor", typeid(*this).name());
		if (components.size() > 0)
		{
			for (auto& component : components)
			{
				auto componentId = component.second->GetComponentId();
				GarbageCollector::DestroyComponent(componentId);
			}
		}
	}

	//void EarlyUpdate() override {}

	//void Update() override {}

	//void LateUpdate() override {}

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
	
	// TODO ���� ������ ������� ���� ����� �� ����� ������������� ���������� � list.h ������� ������ ������� 
	// ������� � �� ��� ��� ������� :)
	void Destroy()
	{
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