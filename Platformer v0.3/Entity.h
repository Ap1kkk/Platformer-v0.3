#pragma once

#include <algorithm>
#include <vector>
#include <unordered_map>

#include "IEntity.h"
#include "IComponent.h"
#include "Debug.h"

#include "ComponentManager.h"
#include "ObjectCollection.h"
#include "GarbageCollector.h"

#include "OnEntityDestroyedEvent.h"
#include "OnComponentDestroyedEvent.h"

#include "OnEntityEnabledEvent.h"
#include "OnEntityDisabledEvent.h"
#include "OnComponentEnabledEvent.h"
#include "OnComponentDisabledEvent.h"

#include "EventListener.h"

/// <summary>
/// Represents main functionality of an object and contains its attached components
/// </summary>
class Entity : public IEntity, public EventListener
{
public:
	Entity() 
	{
		SubscribeOnEvent<OnComponentEnabledEvent>();
	}
	virtual ~Entity();

	void OnEventHappened(EventData& eventData) override
	{
		if (eventData.eventType == OnComponentEnabledEvent::GetType())
		{
			Debug::Log("-------------Enabled");
		}
	}


	/// <summary>
	/// Creates and attaches component of specified type to an object
	/// </summary>
	/// <typeparam name="C">Type of Component must be inherited from IComponent</typeparam>
	/// <returns>Pointer to attached component</returns>
	template<class C>
	C* AddComponent()
	{
		ComponentType compType = typeid(C).name();

		auto itr = components.find(compType);
		if (itr == components.end())
		{
			auto component = ComponentManager::CreateComponent<C>();
			component->SetOwnerId(entityId);
			component->SetObjectContext(objectContext);
			components.insert(std::make_pair(compType, static_cast<IComponent*>(component)));
			componentsOrder.emplace_back(component);
			//enabledComponents.emplace(std::make_pair(component->GetComponentLayer(), component));
			notAwokenComponents.emplace_back(component);
			RecalculateComponentsOrder();
			//TODO заменить на событие
			ObjectCollection::HasNotAwokenComponents(entityId);
			return component;
		}
		else
		{
			Debug::LogError("Component with type " + compType + " was already attached");
			return nullptr;
		}
	}

	/// <summary>
	/// Returns an attached component if it is exists
	/// </summary>
	/// <typeparam name="C"></typeparam>
	/// <returns></returns>
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
	
	//TODO проверить на работоспособность
	void DeleteComponent(ComponentId id)
	{
		auto componentType = ComponentManager::GetComponentTypeById(id);
		auto itr = components.find(componentType);
		if (itr != components.end())
		{
			ComponentManager::DestroyComponent(id);
			components.erase(itr);
		}
	}


	// ¬ызывать при изменении сло€ выполнени€ у компонента
	void RecalculateComponentsOrder();

	void ProcessNotAwokenComponents() override;

	void ComponentsEarlyUpdate() override;
	void ComponentsUpdate() override;
	void ComponentsLateUpdate() override;
	void ComponentsUpdateUI() override;

	/// <summary>
	/// Destroys an object and clears the memory after it
	/// Can't be called twice or more
	/// </summary>
	void Destroy() override;

	void Enable() override
	{
		OnEnable();

		for (auto& component : components)
		{
			component.second->Enable();
		}

		EventData data(OnEntityEnabledEvent::GetType());
		data.id = entityId;

		OnEntityEnabledEvent::Invoke(data);
	}
	void Disable() override
	{
		OnDisable();

		for (auto& component : components)
		{
			component.second->Disable();
		}

		EventData data(OnEntityDisabledEvent::GetType());
		data.id = entityId;

		OnEntityDisabledEvent::Invoke(data);
	}

private:
	std::unordered_map<ComponentType, IComponent*> components;
	//TODO заменить на miltimap

	std::multimap<ComponentLayer, IComponent*> enabledComponents;

	std::vector<IComponent*> componentsOrder;
	std::vector<IComponent*> notAwokenComponents;

	std::vector<IComponent*> disabledComponents;
};