#pragma once

#include "IComponent.h"
#include "ISensor.h"

#include "PhysicComponent.h"
#include "WorldContactListener.h"
#include "Bitmask.h"

#include "Debug.h"

#include "Input.h"

#include "Damageble.h"

#include "EventListener.h"

#include "PlayerTurnedFaceData.h"
#include "OnEntityDiedData.h"

//#include "FixtureManager.h" 

class AttackSensor : public IComponent, public ISensor, public EventListener
{
public:
	AttackSensor() {}

	void SetPhysicComponent(PhysicComponent* physicComponent);

	void SetOffset(sf::Vector2f offset);

	void Awake() override;

	void Update()
	{
		if (Input::IsKeyDown(Input::Key::LMouseButton))
		{
			Debug::Log("lmb click");

			if (actualDirection == FaceDirection::Left)
			{
				if (attackBufferLeft.size() > 0)
				{
					auto damageData = new DamageData;
					damageData->value = 50;

					for (auto& enemy : attackBufferLeft)
					{
						enemy.second->TakeDamage(damageData);
					}

					delete damageData;
				}
			}
			else
			{
				if (attackBufferRight.size() > 0)
				{
					auto damageData = new DamageData;
					damageData->value = 50;

					for (auto& enemy : attackBufferRight)
					{
						enemy.second->TakeDamage(damageData);
					}

					delete damageData;
				}
			}

		}
		ClearAttackBufferRemovablesLeft();
		ClearAttackBufferRemovablesRight();
	}

	void OnCollisionEnter(b2Contact* contact) override;
	void OnCollisionExit(b2Contact* contact) override;

	void OnDestroy() override;

	void OnEventHappened(EventData& eventData) override
	{
		if (eventData.eventType == EventType::OnPlayerTurnedFaceEvent)
		{
			auto data = static_cast<PlayerTurnedFaceData*>(eventData.userData);
			Debug::Log(std::to_string((short)data->direction));
			actualDirection = data->direction;
		}
		if (eventData.eventType == EventType::OnEntityDiedEvent)
		{
			auto data = static_cast<OnEntityDiedData*>(eventData.userData);
			
			RemoveFromAttackBufferLeft(data->entityId);
			RemoveFromAttackBufferRight(data->entityId);
		}
	}

	//TODO оптимизировать и засунуть в меньшее количество методов
	void AddToAttackBufferLeft(EntityId ownerId, Damageble* damageble)
	{
		auto itr = attackBufferLeft.find(ownerId);
		if (itr == attackBufferLeft.end())
		{
			attackBufferLeft.emplace(std::make_pair(ownerId, damageble));
			Debug::Log("Added to attack buffer");
		}
	}
	void RemoveFromAttackBufferLeft(EntityId ownerId)
	{
		auto itr = attackBufferLeft.find(ownerId);
		if (itr != attackBufferLeft.end())
		{
			attackBufferRemovablesLeft.push_back(itr->first);
			Debug::Log("Removed from attack buffer");
		}
	}
	void ClearAttackBufferRemovablesLeft()
	{
		if (!attackBufferRemovablesLeft.empty())
		{
			for (auto& itr : attackBufferRemovablesLeft)
			{
				attackBufferLeft.erase(itr);
			}
			attackBufferRemovablesLeft.clear();
		}
	}

	void AddToAttackBufferRight(EntityId ownerId, Damageble* damageble)
	{
		auto itr = attackBufferRight.find(ownerId);
		if (itr == attackBufferRight.end())
		{
			attackBufferRight.emplace(std::make_pair(ownerId, damageble));
			Debug::Log("Added to attack buffer");
		}
	}
	void RemoveFromAttackBufferRight(EntityId ownerId)
	{
		auto itr = attackBufferRight.find(ownerId);
		if (itr != attackBufferRight.end())
		{
			attackBufferRemovablesRight.push_back(itr->first);
			Debug::Log("Removed from attack buffer");
		}
	}
	void ClearAttackBufferRemovablesRight()
	{
		if (!attackBufferRemovablesRight.empty())
		{
			for (auto& itr : attackBufferRemovablesRight)
			{
				attackBufferRight.erase(itr);
			}
			attackBufferRemovablesRight.clear();
		}
	}

private:
	b2Body* body;
	b2Vec2 ownerBodyOffsetLeft;
	b2Vec2 ownerBodyOffsetRight;
	Sensor* sensorLeft;
	Sensor* sensorRight;
	PhysicComponent* physicComponent;
	Bitmask collisionMask;

	FaceDirection actualDirection;

	std::map<EntityId, Damageble*> attackBufferLeft;
	std::map<EntityId, Damageble*> attackBufferRight;
	//std::vector<std::map<EntityId, Damageble*>::iterator> attackBufferRemovablesLeft;
	//std::vector<std::map<EntityId, Damageble*>::iterator> attackBufferRemovablesRight;
	std::vector<EntityId> attackBufferRemovablesLeft;
	std::vector<EntityId> attackBufferRemovablesRight;

	bool isEnabledToJump;
	FixtureUserData* userData;

	b2Vec2 sizeLeft = { 50, 100 };
	b2Vec2 sizeRight = { 50, 100 };
};

