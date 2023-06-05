#pragma once

#include "DataTypes.h"

struct OnEntityDiedData : public UserEventData
{
	EntityId entityId;
	ChunkId chunkId = 0;
	sf::Vector2f spawnPosition = {0.f, 0.f};
	bool isPlayer = false;
};