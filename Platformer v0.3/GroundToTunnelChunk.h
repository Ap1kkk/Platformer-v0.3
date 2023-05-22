#pragma once

#include "Chunk.h"

#include "SharedContext.h"
#include "ObjectContext.h"

#include "GroundToTunnel.h"

class GroundToTunnelChunk : public Chunk
{
public:
	GroundToTunnelChunk(SharedContext sharedContext, ObjectContext objectContext);

	void Spawn(sf::Vector2f chunkPosition) override;

	void SetBackgroundTexture(Filename backgroundTexture)
	{
		this->backgroundTexture = backgroundTexture;
	}

	void Destroy() override
	{
		
	}

private:
	GroundToTunnel* background;

	Filename backgroundTexture = "First Level/part3.png";

	sf::Vector2f smallObstacle3Offset = { -500.f, 240.f + 100 };
};

