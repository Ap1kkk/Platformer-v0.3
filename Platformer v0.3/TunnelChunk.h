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
		

		background->SetTunnelNumber(tunnelChunkNumber);
		background->SetPosition(chunkPosition);
		ObjectCollection::AddObject(background);

		EnemySpawnPositions enemyPositions;
		if (!SaveManager::IsGameLoaded())
		{
			enemyPositions = TunnelCollidersData::GetEnemySpawnData(tunnelChunkNumber);
		}
		else
		{
			enemyPositions = SaveManager::GetEnemySpawnData(tunnelChunkNumber);

		}

		for (auto& position : enemyPositions)
		{
			auto enemy = sharedContext.entityManger->CreateEntity<Enemy>(objectContext);
			enemy->SetSpawnPosition(chunkPosition + position);
			enemy->SetChunkData(chunkSpawnId, position);
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
};

