#pragma once

#include "GameObject.h"
#include "DataTypes.h"

#include "TunnelCollidersData.h"

struct TunnelCollidersTEmpData
{
	std::vector<ColliderData> colliders;
};


class TunnelBackground : public GameObject
{
public:
	TunnelBackground() {}

	void Awake() override 
	{
		MakeDrawable(true, drawLayer);
		SetTexture(CalculateTextureFilename(tunnelNumber));

		physicComponent = MakePhysical();

		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position = b2Vec2(spawnPosition.x, spawnPosition.y);

		physicComponent->SetBodyDef(bodyDef);
		physicComponent->InitializeBody();

		for (auto& collider : collidersData)
		{
			//b2PolygonShape boxShape;
			//b2Vec2 size = collider.shape;
			//boxShape.SetAsBox(size.x, size.y, collider.centerPosition, 0.f);


			b2FixtureDef boxFixtureDef;
			//boxFixtureDef.shape = &boxShape;
			boxFixtureDef.shape = &collider.shape;
			boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::Ground));

			physicComponent->AddFixture(boxFixtureDef);
		}
		//for (auto collider = collidersData.colliders.begin(); collider != collidersData.colliders.end(); ++collider)
		//{
		//	b2PolygonShape boxShape;
		//	b2Vec2 size = collider->shape;
		//	boxShape.SetAsBox(size.x, size.y, collider->centerPosition, 0.f);


		//	b2FixtureDef boxFixtureDef;
		//	boxFixtureDef.shape = &boxShape;
		//	boxFixtureDef.filter.categoryBits = (1 << ((uint16)CollisionLayers::Ground));

		//	physicComponent->AddFixture(boxFixtureDef);
		//}
	}

	/// номер от 1 до 16
	void SetTunnelNumber(int tunnelNumber)
	{
		this->tunnelNumber = tunnelNumber;
		collidersData = TunnelCollidersData::GetCollidersData(tunnelNumber);
	}
	/// вектор с информацией с коллайдерами
	void SetCollidersData(CollidersDataVector collidersData)
	{
		this->collidersData = collidersData;
	}

	void SetPosition(const sf::Vector2f& position)
	{
		transform->SetPosition(sf::Vector2f(position.x, position.y));
		SetSpawnPosition(position);
	}

private:

	Filename CalculateTextureFilename(int tunnelNumber)
	{
		return textureFilename + std::to_string(tunnelNumber) + ".png";
	}

	DrawLayer drawLayer = -100;
	Filename textureFilename = "tunnel_textures/background/tunnel_background_";
	int tunnelNumber = 1;

	CollidersDataVector collidersData;
};

