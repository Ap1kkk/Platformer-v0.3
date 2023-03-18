#include "ComponentManager.h"

//std::unordered_map<ComponentId, std::any> ComponentManager::components = {};
std::unordered_map<ComponentId, IComponent*> ComponentManager::components = {};
std::unordered_map<ComponentId, ComponentType> ComponentManager::typeTable = {};

void ComponentManager::DestroyComponent(ComponentId comonentId)
{
	auto itr = components.find(comonentId);
	if (itr != components.end())
	{
		auto component = (*itr).second;
		component->Destroy();
		components.erase(itr);
		Debug::LogWarning("Component with id: " + std::to_string(comonentId) + " was deleted", typeid(ComponentManager).name());
	}
	else
	{
		Debug::LogError("Component with id: " + std::to_string(comonentId) + " was not found", typeid(ComponentManager).name());
	}
}

ComponentType ComponentManager::GetComponentTypeById(ComponentId comonentId)
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
