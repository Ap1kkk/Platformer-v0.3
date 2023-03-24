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
	TileSet(Filename textureName, sf::Vector2i tileSize) : tileSetFilename(textureName), tileSize(tileSize), tileSetId(staticTileSetId++)
	{
		ReadTileSet();
	}

	void ReadTileSet()
	{
		tileSetTexture = AssetAllocator::GetTexture(AssetAllocator::GetPath() + tileSetFilename);
		tileSetSize = tileSetTexture.getSize();

		for (unsigned int height = 0; height < tileSetSize.y; height += tileSize.y + 1)
		{
			for (unsigned int width = 0; width < tileSetSize.x; width += tileSize.x + 1)
			{
				TileData tileData;
				tileData.id = staticTileId++;
				tileData.size = tileSize;
				tileData.textureFilename = tileSetFilename;
				tileData.leftTopCornerPosition = sf::Vector2i(width, height);
				tileData.centerPosition = sf::Vector2f(0, 0);

				tilesData.emplace(tileData.id, tileData);
			}
		}
	}

	TilesDataMap GetTilesData() const
	{
		return tilesData;
	}

	TileData GetTileData(TileId tileId) const 
	{
		auto itr = tilesData.find(tileId);
		if (itr != tilesData.end())
		{
			return itr->second;
		}
		else
		{
			Debug::LogWarning("Tile with id:" + std::to_string(itr->first) + " not found", typeid(*this).name());
		}
	}

	TileSetId GetTileSetId() const { return tileSetId; }

	Filename GetTileSetFilename() const { return tileSetFilename; }

private:
	sf::Texture tileSetTexture;
	Filename tileSetFilename;
	sf::Vector2u tileSetSize;
	sf::Vector2i tileSize;
	TilesDataMap tilesData;

	TileSetId tileSetId;

	static TileId staticTileId;
	static TileSetId staticTileSetId;
};

