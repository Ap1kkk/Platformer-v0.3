#pragma once

#include <unordered_map>
#include "IComponent.h"
#include "TransformComponent.h"

#include "EventListener.h"

/// <summary>
/// Static class which creates, destroys and finds Component by its id
/// </summary>
class ComponentManager : public EventListener
{
public:

	/// <summary>
	/// Creates the Component
	/// Component must inherit from IComponent
	/// </summary>
	/// <typeparam name="C"></typeparam>
	/// <returns>Pointer to created component</returns>
	template<class C>
	static C* const CreateComponent()
	{
		C* component = new C;
		ComponentId id = component->GetComponentId();
		ComponentType type = typeid(C).name();
		typeTable.insert(std::make_pair(id, type));
		//components.insert(std::make_pair(id, static_cast<IComponent*>(component)));
		components.insert(std::make_pair(id, component));
		Debug::LogInfo("Component with id: " + std::to_string(id) + " was created", typeid(ComponentManager).name());
		return component;
	}

	/// <summary>
	/// Destoys the component and clears the memory taken by it
	/// </summary>
	/// <param name="comonentId">Id of destroying component</param>
	static void DestroyComponent(ComponentId comonentId);

	/// <summary>
	/// Searches and returns the type of the component
	/// </summary>
	/// <param name="comonentId">Id of searching component</param>
	/// <returns>Type of component</returns>
	static ComponentType GetComponentTypeById(ComponentId comonentId);

	static IComponent* GetComponentById(ComponentId componentId)
	{
		auto itr = components.find(componentId);
		if (itr != components.end())
		{
			return itr->second;
		}
		else
		{
			return nullptr;
		}
	}

	void SubscribeOnEvents()
	{
		SubscribeOnEvent(EventType::OnComponentDestroyedEvent);
	}

	void OnEventHappened(EventData& data) override
	{
		if (data.eventType == EventType::OnComponentDestroyedEvent)
		{
			Debug::Log("Deleting entity with id: " + std::to_string(data.id), typeid(*this).name());
			DestroyComponent(data.id);
		}
	}

private:

	//TODO совместить в один и как second хранить пару
	static std::unordered_map<ComponentId, IComponent*> components;
	static std::unordered_map<ComponentId, ComponentType> typeTable;
};