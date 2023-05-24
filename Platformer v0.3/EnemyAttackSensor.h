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

class EnemyAttackSensor : public IComponent, public ISensor/*, public EventListener*/
{
public:
	EnemyAttackSensor() : playerToAttack(nullptr) {}

	void SetPhysicComponent(PhysicComponent* physicComponent);

	void SetOffset(sf::Vector2f offset);

	void Awake() override;

	void Update()
	{
		if (isTriggeredToAttack)
		{
			attackTime += Time::DeltaTime();

			if (isFirstAttack)
			{
				if (attackTime >= firstAttackDelay)
				{
					Attack();
					isFirstAttack = false;
					attackTime = 0.f;
				}
			}
			else
			{
				if (attackTime >= attackCooldown)
				{
					Attack();
					isFirstAttack = false;
					attackTime = 0.f;
				}
			}
		}
	}

	void OnCollisionEnter(b2Contact* contact) override;
	void OnCollisionExit(b2Contact* contact) override;

	void OnDestroy() override;

	void Attack()
	{
		if (playerToAttack != nullptr)	
		{
			Debug::Log("ATTACK");
			DamageData data;
			data.value = damagePerHit;
			playerToAttack->TakeDamage(&data);
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

	Damageble* playerToAttack;

	bool isEnabledToJump;
	FixtureUserData* userData;

	b2Vec2 sizeLeft = { 50, 100 };
	b2Vec2 sizeRight = { 50, 100 };

	float attackTime = 0.f;

	float firstAttackDelay = 1.f;
	float attackCooldown = 1.5f;
	bool isTriggeredToAttack = false;
	bool isFirstAttack = false;

	unsigned int damagePerHit = 25;
};

