#pragma once

#include "GameObject.h"
#include "DataTypes.h"

class Background : public GameObject
{
public:
	Background();

	void Awake() override;

	void SetPosition(const sf::Vector2f& position);

	void SetBackgroundTexture(Filename textureFilename);

private:
	DrawLayer drawLayer = -100;
	Filename textureFilename = "forest.png";

	float colliderHeight = 40.f;
	b2Vec2 colliderOffset = {0.f, 400.f};
};

