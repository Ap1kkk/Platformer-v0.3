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
	MainChunk(SharedContext sharedContext, ObjectContext objectContext) : Chunk(sharedContext, objectContext)
	{

	}

	void Spawn(sf::Vector2f chunkPosition) override
	{
		background = sharedContext.entityManger->CreateEntity<Background>(objectContext);
		background->SetPosition(chunkPosition);
		background->SetBackgroundTexture(backgroundFilename);
		ObjectCollection::AddObject(background);

	}

	void Destroy() override
	{

	}

private:
	RoadSprite* road;
	Background* background;

	Filename backgroundFilename = "Krill_House.png";
};

