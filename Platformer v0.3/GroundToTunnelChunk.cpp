#include "GroundToTunnelChunk.h"

GroundToTunnelChunk::GroundToTunnelChunk(SharedContext sharedContext, ObjectContext objectContext) : Chunk(sharedContext, objectContext)
{

}

void GroundToTunnelChunk::Spawn(sf::Vector2f chunkPosition)
{
	background = sharedContext.entityManger->CreateEntity<GroundToTunnel>(objectContext);
	background->SetPosition(chunkPosition);
	background->SetBackgroundTexture(backgroundTexture);
	ObjectCollection::AddObject(background);

}