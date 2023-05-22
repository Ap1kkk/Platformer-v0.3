#pragma once

#include "Chunk.h"

#include "SharedContext.h"
#include "ObjectContext.h"

#include "TunnelBackground.h"
#include "SmallObstacle.h"

#include "Enemy.h"

class TunnelChunk : public Chunk
{
public:
	TunnelChunk(SharedContext sharedContext, ObjectContext objectContext);

	void Spawn(sf::Vector2f chunkPosition) override
	{
		background = sharedContext.entityManger->CreateEntity<TunnelBackground>(objectContext);
		
		TunnelCollidersData data;

		background->SetTunnelNumber(tunnelChunkNumber);
		background->SetPosition(chunkPosition);
		ObjectCollection::AddObject(background);

		auto enemyPositions = TunnelCollidersData::GetEnemySpawnData(tunnelChunkNumber);

		for (auto& position : enemyPositions)
		{
			auto enemy = sharedContext.entityManger->CreateEntity<Enemy>(objectContext);
			enemy->SetSpawnPosition(chunkPosition + position);
			ObjectCollection::AddObject(enemy);
		}
	}

	void SetTunnelChunkNumber(int number)
	{
		tunnelChunkNumber = number;
	}

	void Destroy() override
	{

	}

private:
	TunnelBackground* background;

	TunnelCollidersData collidersData;

	int tunnelChunkNumber;
	//SmallObstacle* smallObstacle1;

	//Filename smallObstacle1Texture = "car2.png";

	//sf::Vector2f smallObstacle1Offset = { 500.f, 220.f + 100 };
};

