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

	levelLabel = sharedContext.entityManger->CreateEntity<LevelLabel>(objectContext);
	levelLabel->SetPosition(chunkPosition);
	levelLabel->SetLabel(levelName);
	ObjectCollection::AddObject(levelLabel);

	levelSwitcher = sharedContext.entityManger->CreateEntity<LevelSwitcher>(objectContext);
	levelSwitcher->SetPosition(sf::Vector2f(chunkPosition.x + 0.f, chunkPosition.y + 200.f));
	levelSwitcher->SetLevelTotransit(nextLevel);
	ObjectCollection::AddObject(levelSwitcher);
}
