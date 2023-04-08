#pragma once

#include "Chunk.h"

#include "SharedContext.h"
#include "ObjectContext.h"

#include "RoadSprite.h"
#include "Background.h"

class MainChunk : public Chunk
{
public:
	MainChunk(SharedContext sharedContext, ObjectContext objectContext) : Chunk(sharedContext, objectContext)
	{

	}

	void Spawn(sf::Vector2f chunkPosition) override
	{
		//for (int y = -100; y <= 200; y += 300)
		//{
		//	for (int x = -320 * 3; x < 320 * 3; x += 320 * 2)
		//	{
		road = sharedContext.entityManger->CreateEntity<RoadSprite>(objectContext);
		road->SetSpawnPosition(chunkPosition.x, chunkPosition.y + 100.f);
		road->SetTexture("floor.png");
		ObjectCollection::AddObject(road);

		background = sharedContext.entityManger->CreateEntity<Background>(objectContext);
		background->SetPosition(chunkPosition);
		ObjectCollection::AddObject(background);
		//	}
		//}


	}

	void Destroy() override
	{

	}

private:
	RoadSprite* road;
	Background* background;
};

