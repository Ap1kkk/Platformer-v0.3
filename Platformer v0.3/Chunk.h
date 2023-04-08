#pragma once

#include <SFML/Graphics.hpp>

#include "DataTypes.h"
#include "SharedContext.h"
#include "ObjectContext.h"

class Chunk
{
public:
	Chunk(SharedContext sharedContext, ObjectContext objectContext) : sharedContext(sharedContext), objectContext(objectContext), chunkId(staticIdCounter++)
	{

	}

	virtual ~Chunk() {}

	virtual void Spawn(sf::Vector2f chunkPosition) = 0;

	virtual void Destroy() = 0;

protected:
	SharedContext sharedContext;
	ObjectContext objectContext;

	ChunkId chunkId;

private:
	static ChunkId staticIdCounter;
};

