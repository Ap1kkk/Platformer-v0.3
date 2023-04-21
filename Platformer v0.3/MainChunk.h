#pragma once

#include "Chunk.h"

#include "SharedContext.h"
#include "ObjectContext.h"

#include "RoadSprite.h"
#include "Background.h"
#include "SmallObstacle.h"

class MainChunk : public Chunk
{
public:
	MainChunk(SharedContext sharedContext, ObjectContext objectContext);

	void Spawn(sf::Vector2f chunkPosition) override;

	void Destroy() override
	{
	}

private:
	RoadSprite* road;
	Background* background;

	Filename backgroundFilename = "Krill_House.png";
};
