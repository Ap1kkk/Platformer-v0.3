#include "MainChunk.h"

MainChunk::MainChunk(SharedContext sharedContext, ObjectContext objectContext) : Chunk(sharedContext, objectContext)
{

}

void MainChunk::Spawn(sf::Vector2f chunkPosition)
{
	background = sharedContext.entityManger->CreateEntity<Background>(objectContext);
	background->SetPosition(chunkPosition);
	background->SetBackgroundTexture(backgroundFilename);
	ObjectCollection::AddObject(background);


}
