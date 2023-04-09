#pragma once

#include <map>

#include <SFML/Graphics.hpp>

#include "DataTypes.h"
#include "AssetAllocator.h"
#include "Tile.h"

#include "Debug.h"

using TilesDataMap = std::map<TileId, TileData>;

class TileSet
{
public:
	TileSet(Filename textureName, sf::Vector2i tileSize, DrawLayer tilesDrawLayer);

	void ReadTileSet();

	TilesDataMap GetTilesData() const;

	TileData GetTileData(TileId tileId) const;

	TileSetId GetTileSetId() const { return tileSetId; }

	Filename GetTileSetFilename() const { return tileSetFilename; }

private:
	sf::Texture tileSetTexture;
	Filename tileSetFilename;
	sf::Vector2u tileSetSize;
	sf::Vector2i tileSize;
	TilesDataMap tilesData;

	TileSetId tileSetId;
	DrawLayer tilesDrawLayer;

	static TileId staticTileId;
	static TileSetId staticTileSetId;
};

