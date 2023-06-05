#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"

#include "Health.h"
#include "Damageble.h"

#include "Animator.h"

#include "IdleEnemyAnimState.h"
#include "RunEnemyAnimState.h"
#include "AttackEnemyAnimState.h"

#include "EnemyAttackSensor.h"

#include "SaveManager.h"

class Enemy : public GameObject, public Damageble
{
public:
	Enemy();

	void Awake() override;

	void Update() override;

	void SetChunkData(ChunkId chunkId, sf::Vector2f spawnOffset) 
	{
		this->spawnChunkId = chunkId;
		this->spawnOffset = spawnOffset;
	}

	void TakeDamage(DamageData* damageData)
	{
		health->TakeDamage(damageData);
	}

	void OnEntityDied() override
	{
		Destroy();
	}

	//void OnEventHappened(EventData& eventData) override
	//{
	//	if (eventData.eventType == EventType::OnGameSaved)
	//	{
	//		//SaveManager
	//	}
	//}

private:
	b2Body* body;

	Filename enemyTexture = "Characters/enemy.png";

	sf::Vector2f hpOffset = {0.f, -120.f};

	DrawLayer drawLayer = 100;
	Health* health;
	FixtureUserData* userData;

	Animator* animator;

	const short FRAME_WIDTH = 126;
	const short FRAME_HEIGHT = 155;

	EnemyAttackSensor* attackSensor;

	sf::Vector2f colliderSize = { 80.f / 2, 180.f / 2 };
	sf::Vector2f attackSensorOffset = { -50.f, 0.f };

	bool isMoving = true;
	float movingTime = 1.5f;
	float idleTime = 1.f;

	float enemyVelocity = 500.f;

	float curentTime = 0.f;
	FaceDirection faceDirection = FaceDirection::Right;

	ChunkId spawnChunkId;
	sf::Vector2f spawnOffset;
};

