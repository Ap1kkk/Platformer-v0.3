#pragma once

#include "Chunk.h"

#include "SharedContext.h"
#include "ObjectContext.h"

#include "RoadSprite.h"
#include "Background.h"
#include "SmallObstacle.h"

#include "LevelSwitcher.h"
#include "LevelLabel.h"

class MainChunk : public Chunk
{
public:
	MainChunk(SharedContext sharedContext, ObjectContext objectContext);

	void Spawn(sf::Vector2f chunkPosition) override;

	void SetLevelName(std::string name)
	{
		levelName = name;
	}

	void SetLevelToSwitch(GameLevels nextLevel)
	{
		this->nextLevel = nextLevel;
	}

	void SetBackgroundTexture(Filename textureFilename)
	{
		backgroundFilename = textureFilename;
	}

	void Destroy() override
	{
	}

private:
	RoadSprite* road;
	Background* background;

	LevelLabel* levelLabel;
	std::string levelName;

	LevelSwitcher* levelSwitcher;
	GameLevels nextLevel;

	Filename backgroundFilename = "Krill_House.png";
};

