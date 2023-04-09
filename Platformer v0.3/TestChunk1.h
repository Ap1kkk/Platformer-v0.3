#pragma once

#include "Chunk.h"

#include "SharedContext.h"
#include "ObjectContext.h"

#include "RoadSprite.h"
#include "Background.h"
#include "SmallObstacle.h"

class TestChunk1 : public Chunk
{
public:
	TestChunk1(SharedContext sharedContext, ObjectContext objectContext) : Chunk(sharedContext, objectContext)
	{

	}

	void Spawn(sf::Vector2f chunkPosition) override
	{
		background = sharedContext.entityManger->CreateEntity<Background>(objectContext);
		background->SetPosition(chunkPosition);
		ObjectCollection::AddObject(background);

		smallObstacle1 = sharedContext.entityManger->CreateEntity<SmallObstacle>(objectContext);
		smallObstacle1->SetPosition(chunkPosition + smallObstacle1Offset);
		smallObstacle1->SetObstacleTexture(smallObstacle1Texture);
		ObjectCollection::AddObject(smallObstacle1);

	}

	void Destroy() override
	{

	}

private:
	RoadSprite* road;
	Background* background;

	SmallObstacle* smallObstacle1;

	Filename smallObstacle1Texture = "car2.png";

	sf::Vector2f smallObstacle1Offset = { 500.f, 220.f + 100 };
};

