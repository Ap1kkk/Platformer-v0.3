#pragma once

#include "Chunk.h"

#include "SharedContext.h"
#include "ObjectContext.h"

#include "TunnelBackground.h"
#include "SmallObstacle.h"

class TunnelChunk : public Chunk
{
public:
	TunnelChunk(SharedContext sharedContext, ObjectContext objectContext);

	void Spawn(sf::Vector2f chunkPosition) override
	{
		background = sharedContext.entityManger->CreateEntity<TunnelBackground>(objectContext);
		
		TunnelCollidersData data;

		background->SetTunnelNumber(tunnelChunkNumber);
		background->SetPosition(chunkPosition);
		ObjectCollection::AddObject(background);
	}

	void SetTunnelChunkNumber(int number)
	{
		tunnelChunkNumber = number;
	}

	void Destroy() override
	{

	}

private:
	TunnelBackground* background;

	TunnelCollidersData collidersData;

	int tunnelChunkNumber;
	//SmallObstacle* smallObstacle1;

	//Filename smallObstacle1Texture = "car2.png";

	//sf::Vector2f smallObstacle1Offset = { 500.f, 220.f + 100 };
};

