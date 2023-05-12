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

#include "OnComponentUserData.h"

#include "EventListener.h"

/// <summary>
/// Represents main functionality of an object and contains its attached components
/// </summary>
class Entity : public IEntity, public EventListener
{
public:
	Entity() 
	{
		SubscribeOnEvent(EventType::OnComponentEnabledEvent);
	}
	virtual ~Entity();

	void OnEventHappened(EventData& eventData) override
	{
		if (eventData.eventType == EventType::OnComponentEnabledEvent)
		{
			if (eventData.id == entityId)
			{
				auto userData = static_cast<ComponentUserData*>(eventData.userData);
				auto component = userData->component;
				EnableComponent(component);
			}
		}
		if (eventData.eventType == EventType::OnComponentDisabledEvent)
		{
			if (eventData.id == entityId)
			{
				auto userData = static_cast<ComponentUserData*>(eventData.userData);
				auto component = userData->component;
				DisableComponent(component);
			}
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
			AddToEnabledComponents(component);


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
		//auto componentType = ComponentManager::GetComponentTypeById(id);
		//auto itr = components.find(componentType);
		//if (itr != components.end())
		//{
		//	//TODO убирать из всех списков
		//	ComponentManager::DestroyComponent(id);
		//	components.erase(itr);
		//}

		//новый вариант

		auto component = ComponentManager::GetComponentById(id);
		if (component != nullptr)
		{
			if (component->IsEnabled())
			{
				RemoveFromEnabledComponents(component);
			}
			else
			{
				RemoveFromDisabledComponents(component);
			}
			ComponentManager::DestroyComponent(id);
		}
	}

	//TODO убрать 
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

		for (auto& pair : enabledComponentsBuffer)
		{
			for (auto& component : *pair.second)
			{
				component.second->Enable();
			}
		}
		RetrieveAllComponentsFromBuffer();

		EventData data(EventType::OnEntityEnabledEvent);
		data.id = entityId;

		Event::Invoke(data);
	}
	void Disable() override
	{
		OnDisable();

		for (auto& pair : enabledComponents)
		{
			for (auto& component : *pair.second)
			{
				component.second->Disable();
			}
		}
		BufferEnabledComponents();

		EventData data(EventType::OnEntityDisabledEvent);
		data.id = entityId;

		Event::Invoke(data);
	}

private:

	void AddToEnabledComponents(IComponent* component)
	{
		ComponentLayer componentLayer = component->GetComponentLayer();
		ComponentId componentId = component->GetComponentId();
		auto componentsMap = enabledComponents.find(componentLayer);
		if (componentsMap != enabledComponents.end())
		{
			auto itr = componentsMap->second->find(componentId);
			if (itr != componentsMap->second->end())
			{
				Debug::LogWarning("Component with ComponentId: " + std::to_string(componentId) + " is already Enabled");
			}
			else
			{
				componentsMap->second->emplace(std::make_pair(componentId, component));
			}
		}
		else
		{
			auto newMap = new std::map<ComponentId, IComponent*>;
			newMap->emplace(componentId, component);
			enabledComponents.emplace(componentLayer, newMap);
		}
	}

	void AddToDisabledComponents(IComponent* component)
	{
		auto componentId = component->GetComponentId();
		auto itr = disabledComponents.find(componentId);
		if (itr != disabledComponents.end())
		{
			Debug::LogWarning("Component with ComponentId : " + std::to_string(componentId) + " is already Disabled");
		}
		else
		{
			disabledComponents.emplace(componentId, component);
		}
	}

	void RemoveFromEnabledComponents(IComponent* component)
	{
		ComponentLayer componentLayer = component->GetComponentLayer();
		ComponentId componentId = component->GetComponentId();

		auto componentsMap = enabledComponents.find(componentLayer);
		if (componentsMap != enabledComponents.end())
		{
			auto itr = componentsMap->second->find(componentId);
			if (itr != componentsMap->second->end())
			{
				componentsMap->second->erase(itr);
				//if (componentsMap->second->empty())
				//{
				//	delete componentsMap->second;
				//	enabledComponents.erase(componentsMap);
				//}
			}
			else
			{
				Debug::LogWarning("Component with ComponentId: " + std::to_string(componentId) + " is not Enabled");
			}
		}
		else
		{
			Debug::LogWarning("Component with ComponentId: " + std::to_string(componentId) + " is not Enabled");
		}
	}

	void RemoveFromDisabledComponents(IComponent* component)
	{
		ComponentId componentId = component->GetComponentId();
		auto itr = disabledComponents.find(componentId);
		if (itr != disabledComponents.end())
		{
			disabledComponents.erase(itr);
		}
		else
		{
			Debug::LogWarning("Component with ComponentId: " + std::to_string(componentId) + " is not Disabled");
		}
	}

	void EnableComponent(IComponent* component)
	{
		if (component->IsEnabled())
		{
			Debug::LogWarning("Component with ComponentId: " + std::to_string(component->GetComponentId()) + " is already Enabled");
		}
		else
		{
			RemoveFromDisabledComponents(component);
			AddToEnabledComponents(component);
		}
	}

	void DisableComponent(IComponent* component)
	{
		if (component->IsEnabled())
		{
			RemoveFromEnabledComponents(component);
			AddToDisabledComponents(component);
		}
		else
		{
			Debug::LogWarning("Component with ComponentId : " + std::to_string(component->GetComponentId()) + " is already Disabled");
		}

	}

	void BufferEnabledComponents()
	{
		for (auto& pair : enabledComponents)
		{
			enabledComponentsBuffer.emplace(pair);
		}
		enabledComponents.clear();
	}

	void RetrieveAllComponentsFromBuffer()
	{
		for (auto& pair : enabledComponentsBuffer)
		{
			enabledComponents.emplace(pair);
		}
		enabledComponentsBuffer.clear();
	}

	std::unordered_map<ComponentType, IComponent*> components;

	std::map<ComponentLayer, std::map<ComponentId, IComponent*>*> enabledComponents;
	//TODO перемещать туда все включенные компоненты
	std::map<ComponentLayer, std::map<ComponentId, IComponent*>*> enabledComponentsBuffer;

	std::vector<IComponent*> componentsOrder;
	std::vector<IComponent*> notAwokenComponents;

	std::map<ComponentId, IComponent*> disabledComponents;
};