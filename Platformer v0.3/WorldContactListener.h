#pragma once

#include <box2d/box2d.h>
#include <map>
#include <unordered_map>

#include "IEntity.h"
#include "IComponent.h"
#include "Bitmask.h"
#include "IBody.h"

#include "Debug.h"

class WorldContactListener : public b2ContactListener
{
public:

	void BeginContact(b2Contact* contact) override
	{
		auto fixtureA = static_cast<Fixture*>(contact->GetFixtureA());
		auto fixtureB = static_cast<Fixture*>(contact->GetFixtureB());

		uint16 collisionMask = fixtureA->GetFilterData().categoryBits | fixtureB->GetFilterData().categoryBits;

		Debug::Log(collisionMask);

		for (auto& pair : entityHandlers)
		{
			Debug::Log(pair.first.GetMask16());
			if (collisionMask == pair.first.GetMask16())
			{
				pair.second.second->OnCollisionEnter(contact);
			}
		}

		for (auto& pair : componentHandlers)
		{
			Debug::Log(pair.first.GetMask16());
			if (collisionMask == pair.first.GetMask16())
			{
				pair.second.second->OnCollisionEnter(contact);
			}
		}
	}

	void EndContact(b2Contact* contact) override
	{
		auto fixtureA = static_cast<Fixture*>(contact->GetFixtureA());
		auto fixtureB = static_cast<Fixture*>(contact->GetFixtureB());

		uint16 collisionMask = fixtureA->GetFilterData().categoryBits | fixtureB->GetFilterData().categoryBits;

		Debug::Log(collisionMask);

		for (auto& pair : entityHandlers)
		{
			Debug::Log(pair.first.GetMask16());
			if (collisionMask == pair.first.GetMask16())
			{
				pair.second.second->OnCollisionExit(contact);
			}
		}

		for (auto& pair : componentHandlers)
		{
			Debug::Log(pair.first.GetMask16());
			if (collisionMask == pair.first.GetMask())
			{
				pair.second.second->OnCollisionExit(contact);
			}
		}
	}

	void AddHandler(const Bitmask& bitmask, IEntity* entity)
	{
		entityHandlers.emplace(std::make_pair(bitmask, std::make_pair(entity->GetEntityId(), entity)));
	}
	void AddHandler(const Bitmask& bitmask, IComponent* component)
	{
		componentHandlers.emplace(std::make_pair(bitmask, std::make_pair(component->GetComponentId(), component)));
	}

	void DeleteEntityHandler(EntityId entityId)
	{
		bool isFounded = false;

		for (auto itr = entityHandlers.begin(); itr != entityHandlers.end(); ++itr)
		{
			if (entityId == itr->second.first)
			{
				entityHandlers.erase(itr);
				isFounded = true;
				break;
			}
		}

		if (!isFounded)
		{
			Debug::LogWarning("Can't delete handler\nObject with id: " + std::to_string(entityId) + " not founded");
		}
	}
	void DeleteComponentHandler(ComponentId componentId)
	{
		bool isFounded = false;

		for (auto itr = componentHandlers.begin(); itr != componentHandlers.end(); ++itr)
		{
			if (componentId == itr->second.first)
			{
				componentHandlers.erase(itr);
				isFounded = true;
				break;
			}
		}

		if (!isFounded)
		{
			Debug::LogWarning("Can't delete handler\Component with id: " + std::to_string(componentId) + " not founded");
		}
	}

private:
	std::multimap<Bitmask, std::pair<EntityId, IEntity*>> entityHandlers;
	std::multimap<Bitmask, std::pair<ComponentId, IComponent*>> componentHandlers;
};