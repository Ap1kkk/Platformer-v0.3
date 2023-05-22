#pragma once

#include <unordered_map>

#include "ITileManager.h"
#include "Tile.h"
#include "TileSet.h"

#include "EntityManager.h"
#include "ObjectCollection.h"

#include "Debug.h"

/// Содержит все созданные тайлсеты и хранит общие данные о всех существующих TileData
/// Также создает и удаляет Tile
/// 
/// TODO сделать статическим
class TileManager : public ITileManager
{
public:
	TileManager() {}

	static TileSet* CreateTileSet(Filename textureName, sf::Vector2i tileSize, DrawLayer tilesDrawLayer);

	static TileSet* GetTileSetById(TileSetId tileSetId);

	Tile* CreateTile(TileSet* fromTileSet, TileId tileId, sf::Vector2f position);

	void DestroyTile(EntityId entityId) override;
	
private:
	static std::unordered_map<EntityId, TileId> tileIdTable;
	static std::unordered_map<Filename, TileSetId> tileSetTable;
	static std::unordered_map<TileSetId, TileSet*> tileSets;

	static ObjectContext objectContext;
};

