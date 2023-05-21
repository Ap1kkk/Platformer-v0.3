#pragma once

#include "DataTypes.h"
#include "GameObject.h"

class GroundToTunnel : public GameObject
{
public:
	GroundToTunnel();

	void Awake() override;

	void SetPosition(const sf::Vector2f& position);

	void SetBackgroundTexture(Filename textureFilename);

private:
	DrawLayer drawLayer = -100;
	//Filename textureFilename = "tunnel_textures/background/tunnel_background_1.png";
	Filename textureFilename = "forest.png";

	float colliderHeight = 40.f;

	float colliderWidth1 = 444.f / 2;
	float colliderWidth2 = 1028.f / 2;
	b2Vec2 colliderOffset1 = { -738.f, 400.f };
	b2Vec2 colliderOffset2 = { 446.f, 400.f };
};

