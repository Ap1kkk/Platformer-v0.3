#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"

#include "Health.h"
#include "Damageble.h"

#include "EnemyAttackSensor.h"

class Enemy : public GameObject, public Damageble
{
public:
	Enemy();

	void Awake() override;

	void TakeDamage(DamageData* damageData)
	{
		health->TakeDamage(damageData);
	}

	void OnEntityDied() override
	{
		Destroy();
	}

private:
	b2Body* body;

	Filename enemyTexture = "Characters/enemy.png";

	sf::Vector2f hpOffset = {0.f, -120.f};

	DrawLayer drawLayer = 100;
	Health* health;
	FixtureUserData* userData;

	EnemyAttackSensor* attackSensor;

	sf::Vector2f colliderSize = { 80.f / 2, 180.f / 2 };
	sf::Vector2f attackSensorOffset = { -50.f, 0.f };
};

