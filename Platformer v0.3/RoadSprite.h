#pragma once

#include "GameObject.h"
#include "DataTypes.h"
#include "Debug.h"

class RoadSprite : public GameObject
{
public:
	RoadSprite();

	void Awake() override;

	void SetTexture(const Filename& textureFilename);

private:
	DrawLayer drawLayer = 50;

	b2Vec2 colliderOffset = {0.f, 500.f};

	Filename textureFilename = "road.png";
};

