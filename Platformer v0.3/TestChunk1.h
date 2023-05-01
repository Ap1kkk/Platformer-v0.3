#pragma once

#include "Chunk.h"

#include "SharedContext.h"
#include "ObjectContext.h"

#include "TunnelBackground.h"
#include "SmallObstacle.h"

class TestChunk1 : public Chunk
{
public:
	TestChunk1(SharedContext sharedContext, ObjectContext objectContext);

	void Spawn(sf::Vector2f chunkPosition) override
	{
		background = sharedContext.entityManger->CreateEntity<TunnelBackground>(objectContext);
		
		TunnelCollidersData data;

		background->SetTunnelNumber(TUNNEL_CHUNK_NUMBER);
		background->SetPosition(chunkPosition);
		ObjectCollection::AddObject(background);
	}

	void Destroy() override
	{

	}

private:
	TunnelBackground* background;

	TunnelCollidersData collidersData;
	//SmallObstacle* smallObstacle1;

	//Filename smallObstacle1Texture = "car2.png";

	//sf::Vector2f smallObstacle1Offset = { 500.f, 220.f + 100 };
};

