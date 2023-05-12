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

	levelSwitcher = sharedContext.entityManger->CreateEntity<LevelSwitcher>(objectContext);
	levelSwitcher->SetPosition(sf::Vector2f(100.f, 0.f));
	levelSwitcher->SetLevelTotransit(GameLevels::SecondLevel);
	ObjectCollection::AddObject(levelSwitcher);
}
