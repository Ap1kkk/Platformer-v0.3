#pragma once

#include <box2d/box2d.h>
#include <map>

#include "IEntity.h"
#include "IComponent.h"
#include "Bitmask.h"
#include "IBody.h"

#include "Debug.h"

class WorldContactListener : public b2ContactListener
{
public:

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

	static void AddHandler(const Bitmask& bitmask, IEntity* entity);
	static void AddHandler(const Bitmask& bitmask, IComponent* component);

	static void DeleteEntityHandler(EntityId entityId);
	static void DeleteComponentHandler(ComponentId componentId);

	static void ClearRemovables()
	{
		if (!entityHandlersRemovables.empty())
		{
			for (auto& itr : entityHandlersRemovables)
			{
				entityHandlers.erase(itr);
			}
			entityHandlersRemovables.clear();
		}

		if (!componentHandlersRemovables.empty())
		{
			for (auto& itr : componentHandlersRemovables)
			{
				componentHandlers.erase(itr);
			}
			componentHandlersRemovables.clear();
		}
	}

private:
	static std::multimap<Bitmask, std::pair<EntityId, IEntity*>> entityHandlers;
	static std::multimap<Bitmask, std::pair<ComponentId, IComponent*>> componentHandlers;

	static std::vector<std::multimap<Bitmask, std::pair<EntityId, IEntity*>>::iterator> entityHandlersRemovables;
	static std::vector<std::multimap<Bitmask, std::pair<ComponentId, IComponent*>>::iterator> componentHandlersRemovables;
};