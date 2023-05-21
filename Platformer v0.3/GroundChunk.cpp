#include "GroundChunk.h"

GroundChunk::GroundChunk(SharedContext sharedContext, ObjectContext objectContext) : Chunk(sharedContext, objectContext)
{

}

void GroundChunk::Spawn(sf::Vector2f chunkPosition) 
{
	background = sharedContext.entityManger->CreateEntity<Background>(objectContext);
	background->SetPosition(chunkPosition);
	background->SetBackgroundTexture(backgroundTexture);
	ObjectCollection::AddObject(background);

}
