#pragma once

#include "GameObject.h"

class SmallObstacle : public GameObject
{
public:
	SmallObstacle();

	void Awake() override;

	void SetPosition(const sf::Vector2f& position);

	void SetObstacleTexture(Filename textureFilename);

private:
	DrawLayer drawLayer = -50;
	Filename textureFilename = "ship.png";
	b2Vec2 colliderOffset = { 0.f, 0.f };
};

