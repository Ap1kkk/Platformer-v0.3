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
	TestChunk1(SharedContext sharedContext, ObjectContext objectContext);

	void Spawn(sf::Vector2f chunkPosition) override;

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
