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

/// <summary>
/// Represents main functionality of an object and contains its attached components
/// </summary>
class Entity : public IEntity
{
public:
	Entity() {}
	virtual ~Entity();

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
			component->SetOwner(entityId);
			component->SetObjectContext(objectContext);
			components.insert(std::make_pair(compType, static_cast<IComponent*>(component)));
			componentsOrder.emplace_back(component);
			notAwokenComponents.emplace_back(component);
			RecalculateComponentsOrder();
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
	
	/// <summary>
	/// Destroys attached component
	/// </summary>
	/// <param name="id"></param>
	void DeleteComponent(ComponentId id);

	// Вызывать при изменении слоя выполнения у компонента
	void RecalculateComponentsOrder();

	void ProcessNotAwokenComponents() override;

	void ComponentsEarlyUpdate() override;
	void ComponentsUpdate() override;
	void ComponentsLateUpdate() override;

	/// <summary>
	/// Destroys an object and clears the memory after it
	/// Can't be called twice or more
	/// </summary>
	void Destroy() override;

private:
	std::unordered_map<ComponentType, IComponent*> components;
	std::vector<IComponent*> componentsOrder;
	std::vector<IComponent*> notAwokenComponents;
};