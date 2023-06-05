#pragma once

#include <SFML/Graphics.hpp>

#include "DataTypes.h"
#include "SharedContext.h"
#include "ObjectContext.h"

#include "SaveManager.h"

class Chunk
{
public:
	Chunk(SharedContext sharedContext, ObjectContext objectContext);

	virtual ~Chunk() {}

	virtual void Spawn(sf::Vector2f chunkPosition) = 0;

	virtual void Destroy() = 0;

	static void RefreshIdCounter() { staticIdCounter = 0; }
	void SetChunkSpawnId(ChunkSpawnId spawnId) { chunkSpawnId = spawnId; }
	ChunkSpawnId GetChunkSpawnId() { return chunkSpawnId; }
protected:
	SharedContext sharedContext;
	ObjectContext objectContext;

	ChunkId chunkId;
	ChunkSpawnId chunkSpawnId;
private:
	static ChunkId staticIdCounter;
};

