#pragma once

#include "Chunk.h"

#include "SharedContext.h"
#include "ObjectContext.h"

#include "RoadSprite.h"
#include "Background.h"
#include "SmallObstacle.h"

class TestChunk2 : public Chunk
{
public:
	TestChunk2(SharedContext sharedContext, ObjectContext objectContext) : Chunk(sharedContext, objectContext)
	{

	}

	void Spawn(sf::Vector2f chunkPosition) override
	{
		background = sharedContext.entityManger->CreateEntity<Background>(objectContext);
		background->SetPosition(chunkPosition);
		ObjectCollection::AddObject(background);

		smallObstacle2 = sharedContext.entityManger->CreateEntity<SmallObstacle>(objectContext);
		smallObstacle2->SetPosition(chunkPosition + smallObstacle2Offset);
		smallObstacle2->SetObstacleTexture(smallObstacle2Texture);
		ObjectCollection::AddObject(smallObstacle2);

	}

	void Destroy() override
	{

	}

private:
	RoadSprite* road;
	Background* background;

	SmallObstacle* smallObstacle2;

	Filename smallObstacle2Texture = "car1.png";

	sf::Vector2f smallObstacle2Offset = { 0.f, 240.f + 100 };
};

