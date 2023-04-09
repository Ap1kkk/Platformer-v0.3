#include "TestChunk2.h"

TestChunk2::TestChunk2(SharedContext sharedContext, ObjectContext objectContext) : Chunk(sharedContext, objectContext)
{

}

void TestChunk2::Spawn(sf::Vector2f chunkPosition) 
{
	background = sharedContext.entityManger->CreateEntity<Background>(objectContext);
	background->SetPosition(chunkPosition);
	ObjectCollection::AddObject(background);

	smallObstacle2 = sharedContext.entityManger->CreateEntity<SmallObstacle>(objectContext);
	smallObstacle2->SetPosition(chunkPosition + smallObstacle2Offset);
	smallObstacle2->SetObstacleTexture(smallObstacle2Texture);
	ObjectCollection::AddObject(smallObstacle2);

}
