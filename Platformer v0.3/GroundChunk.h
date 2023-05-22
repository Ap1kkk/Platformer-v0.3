#pragma once

#include "Chunk.h"

#include "SharedContext.h"
#include "ObjectContext.h"

#include "Background.h"
#include "SmallObstacle.h"

class GroundChunk : public Chunk
{
public:
	GroundChunk(SharedContext sharedContext, ObjectContext objectContext);

	void Spawn(sf::Vector2f chunkPosition) override;

	void SetBackgroundTexture(Filename backgroundTexture)
	{
		this->backgroundTexture = backgroundTexture;
	}

	virtual void SpawnExtraObjects() {}

	void Destroy() override
	{

	}

private:
	Background* background;

	//SmallObstacle* smallObstacle2;

	//Filename smallObstacle2Texture = "car1.png";
	Filename backgroundTexture = "First Level/part2.png";

	//sf::Vector2f smallObstacle2Offset = { 0.f, 240.f + 100 };
};

