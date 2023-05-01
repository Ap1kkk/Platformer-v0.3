#pragma once

#include <box2d/box2d.h>

#include "GameObject.h"
#include "AttackSensor.h"

#include "EventListener.h"
#include "OnTestEvent.h"

class Enemy : public GameObject
{
public:
	Enemy();

	void Awake() override;

private:
	b2Body* body;

	Filename enemyTexture = "hero.png";

	DrawLayer drawLayer = 100;

};

