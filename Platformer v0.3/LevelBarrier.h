#pragma once

#include "GameObject.h"
#include "DataTypes.h"

class LevelBarrier : public GameObject
{
public:
	LevelBarrier();

	void Awake() override;

	void SetPosition(const sf::Vector2f& position);

private:

	float colliderHeight = 1080.f / 2;
	float colliderWidth = 20.f;
};

