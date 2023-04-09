#include "TestChunk1.h"

TestChunk1::TestChunk1(SharedContext sharedContext, ObjectContext objectContext) : Chunk(sharedContext, objectContext)
{

}

void TestChunk1::Spawn(sf::Vector2f chunkPosition) 
{
	background = sharedContext.entityManger->CreateEntity<Background>(objectContext);
	background->SetPosition(chunkPosition);
	ObjectCollection::AddObject(background);

	smallObstacle1 = sharedContext.entityManger->CreateEntity<SmallObstacle>(objectContext);
	smallObstacle1->SetPosition(chunkPosition + smallObstacle1Offset);
	smallObstacle1->SetObstacleTexture(smallObstacle1Texture);
	ObjectCollection::AddObject(smallObstacle1);

}
