#include "TileSet.h"

TileId TileSet::staticTileId = 0;
TileSetId TileSet::staticTileSetId = 0;

TileSet::TileSet(Filename textureName, sf::Vector2i tileSize, DrawLayer tilesDrawLayer) :
	tileSetFilename(textureName),
	tileSize(tileSize),
	tileSetId(staticTileSetId++),
	tilesDrawLayer(tilesDrawLayer)
{
	ReadTileSet();
}

void TileSet::ReadTileSet()
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
			tileData.drawLayer = tilesDrawLayer;

			tilesData.emplace(tileData.id, tileData);
		}
	}
}

TilesDataMap TileSet::GetTilesData() const
{
	return tilesData;
}

TileData TileSet::GetTileData(TileId tileId) const
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