#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"

#include "Health.h"
#include "Damageble.h"


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

	Filename enemyTexture = "hero.png";

	DrawLayer drawLayer = 100;
	Health* health;
	FixtureUserData* userData;
};

