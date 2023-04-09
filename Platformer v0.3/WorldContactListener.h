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

	void BeginContact(b2Contact* contact) override
	{
		auto fixtureA = static_cast<Fixture*>(contact->GetFixtureA());
		auto fixtureB = static_cast<Fixture*>(contact->GetFixtureB());

		uint16 collisionMask = fixtureA->GetFilterData().categoryBits | fixtureB->GetFilterData().categoryBits;
		//Debug::Log(collisionMask);

		for (auto& pair : entityHandlers)
		{
			if ((collisionMask | pair.first.GetMask16()) == pair.first.GetMask16())
			{
				pair.second.second->OnCollisionEnter(contact);
			}
		}

		for (auto& pair : componentHandlers)
		{
			//Debug::Log("Comparing..");
			//Debug::Log(collisionMask);
			//Debug::Log(pair.first.GetMask());
			//Debug::Log("...");
			//Debug::Log((collisionMask | pair.first.GetMask16()));

			if ((collisionMask | pair.first.GetMask16()) == pair.first.GetMask16())
			{
				//Debug::Log((collisionMask | pair.first.GetMask16()));
				pair.second.second->OnCollisionEnter(contact);
			}
		}
	}

	void EndContact(b2Contact* contact) override
	{
		auto fixtureA = static_cast<Fixture*>(contact->GetFixtureA());
		auto fixtureB = static_cast<Fixture*>(contact->GetFixtureB());

		uint16 collisionMask = fixtureA->GetFilterData().categoryBits | fixtureB->GetFilterData().categoryBits;
		//Debug::Log(collisionMask);

		for (auto& pair : entityHandlers)
		{
			if ((collisionMask | pair.first.GetMask16()) == pair.first.GetMask16())
			{
				pair.second.second->OnCollisionExit(contact);
			}
		}

		for (auto& pair : componentHandlers)
		{
			if ((collisionMask | pair.first.GetMask16()) == pair.first.GetMask16())
			{
				pair.second.second->OnCollisionExit(contact);
			}
		}
	}

	static void AddHandler(const Bitmask& bitmask, IEntity* entity)
	{
		auto entityId = entity->GetEntityId();

		for (auto itr = entityHandlers.begin(); itr != entityHandlers.end(); ++itr)
		{
			if (entityId == itr->second.first)
			{
				entityHandlers.erase(itr);
				Debug::LogError("Can't add handler\\nObject handler with id: " + std::to_string(entityId) + " already added", typeid(WorldContactListener).name());
				return;
			}
		}

		entityHandlers.emplace(std::make_pair(bitmask, std::make_pair(entity->GetEntityId(), entity)));
	}
	static void AddHandler(const Bitmask& bitmask, IComponent* component)
	{
		auto componentId = component->GetComponentId();
		for (auto itr = componentHandlers.begin(); itr != componentHandlers.end(); ++itr)
		{
			if (componentId == itr->second.first)
			{
				componentHandlers.erase(itr);
				Debug::LogError("Can't add handler\\nComponent handler with id: " + std::to_string(componentId) + " already added", typeid(WorldContactListener).name());
				return;
			}
		}
		componentHandlers.emplace(std::make_pair(bitmask, std::make_pair(component->GetComponentId(), component)));
	}

	static void DeleteEntityHandler(EntityId entityId)
	{
		for (auto itr = entityHandlers.begin(); itr != entityHandlers.end(); ++itr)
		{
			if (entityId == itr->second.first)
			{
				entityHandlers.erase(itr);
				Debug::LogWarning("Object handler with ObjectId: " + std::to_string(entityId) + " was deleted", typeid(WorldContactListener).name());
				return;
			}
		}

		Debug::LogError("Can't delete handler\\nObject handler with id: " + std::to_string(entityId) + " not founded", typeid(WorldContactListener).name());
	}
	static void DeleteComponentHandler(ComponentId componentId)
	{
		for (auto itr = componentHandlers.begin(); itr != componentHandlers.end(); ++itr)
		{
			if (componentId == itr->second.first)
			{
				componentHandlers.erase(itr);
				Debug::LogWarning("Component handler with ComponentId: " + std::to_string(componentId) + " was deleted", typeid(WorldContactListener).name());
				return;
			}
		}

		Debug::LogError("Can't delete handler\\nComponent handler with id: " + std::to_string(componentId) + " not founded", typeid(WorldContactListener).name());
	}

private:
	static std::multimap<Bitmask, std::pair<EntityId, IEntity*>> entityHandlers;
	static std::multimap<Bitmask, std::pair<ComponentId, IComponent*>> componentHandlers;
};