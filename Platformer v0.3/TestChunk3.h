#pragma once

#include "Chunk.h"

#include "SharedContext.h"
#include "ObjectContext.h"

#include "RoadSprite.h"
#include "Background.h"
#include "SmallObstacle.h"

class TestChunk3 : public Chunk
{
public:
	TestChunk3(SharedContext sharedContext, ObjectContext objectContext);

	void Spawn(sf::Vector2f chunkPosition) override;

	void Destroy() override
	{
		
	}

private:
	RoadSprite* road;
	Background* background;

	SmallObstacle* smallObstacle3;

	Filename smallObstacle3Texture = "car3.png";

	sf::Vector2f smallObstacle3Offset = { -500.f, 240.f + 100 };
};
