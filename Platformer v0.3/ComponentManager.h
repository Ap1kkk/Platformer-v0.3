#pragma once

#include <unordered_map>
#include "Component.h"
#include "TransformComponent.h"
#include "DrawableComponent.h"

class ComponentManager
{
public:

	template<class C>
	static C* const CreateComponent()
	{
		C* component = new C;
		ComponentId id = component->GetComponentId();
		ComponentType type = typeid(C).name();
		typeTable.insert(std::make_pair(id, type));
		components.insert(std::make_pair(id, static_cast<IComponent*>(component)));
		return component;
	}

	static void DestroyComponent(ComponentId comonentId)
	{
		auto itr = components.find(comonentId);
		if (itr != components.end())
		{
			auto component = (*itr).second;
			delete component;
			components.erase(itr);
			Debug::LogWarning("Component with id: " + std::to_string(comonentId) + " was deleted", typeid(ComponentManager).name());
		}
		else
		{
			Debug::LogError("Component with id: " + std::to_string(comonentId) + " was not found", typeid(ComponentManager).name());
		}
	}

	static ComponentType GetComponentTypeById(ComponentId comonentId)
	{
		auto itr = typeTable.find(comonentId);
		if (itr != typeTable.end())
		{
			return (*itr).second;
		}
		else
		{
			Debug::LogWarning("Component with id: " + std::to_string(comonentId) + " was not found", typeid(ComponentManager).name());
			return ComponentType();
		}
	}

private:
	static std::unordered_map<ComponentId, IComponent*> components;
	static std::unordered_map<ComponentId, ComponentType> typeTable;
};