#include "TestChunk3.h"

TestChunk3::TestChunk3(SharedContext sharedContext, ObjectContext objectContext) : Chunk(sharedContext, objectContext)
{

}

void TestChunk3::Spawn(sf::Vector2f chunkPosition)
{
	background = sharedContext.entityManger->CreateEntity<Background>(objectContext);
	background->SetPosition(chunkPosition);
	ObjectCollection::AddObject(background);

	smallObstacle3 = sharedContext.entityManger->CreateEntity<SmallObstacle>(objectContext);
	smallObstacle3->SetPosition(chunkPosition + smallObstacle3Offset);
	smallObstacle3->SetObstacleTexture(smallObstacle3Texture);
	ObjectCollection::AddObject(smallObstacle3);

}