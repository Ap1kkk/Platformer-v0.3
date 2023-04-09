#include "TileManager.h"

std::unordered_map<EntityId, TileId> TileManager::tileIdTable = {};
std::unordered_map<Filename, TileSetId> TileManager::tileSetTable = {};
std::unordered_map<TileSetId, TileSet*> TileManager::tileSets = {};

ObjectContext TileManager::objectContext;

TileSet* TileManager::CreateTileSet(Filename textureName, sf::Vector2i tileSize, DrawLayer tilesDrawLayer)
{
	auto itr = tileSetTable.find(textureName);
	if (itr == tileSetTable.end())
	{
		TileSet* tileSet = new TileSet(textureName, tileSize, tilesDrawLayer);
		auto tileSetId = tileSet->GetTileSetId();
		tileSetTable.emplace(std::make_pair(textureName, tileSetId));
		tileSets.emplace(std::make_pair(tileSetId, tileSet));
		return tileSet;
	}
	else
	{
		Debug::LogWarning("TileSet with texture filename: " + textureName + " has already created", typeid(TileManager).name());
		Debug::LogWarning("Returning existing TileSet", typeid(TileManager).name());
		return GetTileSetById(itr->second);
	}
}

TileSet* TileManager::GetTileSetById(TileSetId tileSetId)
{
	auto itr = tileSets.find(tileSetId);
	if (itr != tileSets.end())
	{
		return itr->second;
	}
	else
	{
		Debug::LogWarning("TileSet with TileSetId: " + std::to_string(tileSetId) + " not found", typeid(TileManager).name());
	}
}

Tile* TileManager::CreateTile(TileSet* fromTileSet, TileId tileId, sf::Vector2f position)
{
	TilesDataMap tilesData = fromTileSet->GetTilesData();
	auto itr = tilesData.find(tileId);
	if (itr != tilesData.end())
	{
		auto tile = EntityManager::CreateEntity<Tile>(objectContext);
		itr->second.centerPosition = position;
		tile->SetTileData(itr->second);
		tile->SetTileManager(this);

		ObjectCollection::AddObject(tile);

		tileIdTable.emplace(std::make_pair(tile->GetEntityId(), tileId));
		return tile;
	}
	else
	{
		Debug::LogWarning("TileData with TileId: " + std::to_string(tileId) + " not found in TileSet with id: " + std::to_string(fromTileSet->GetTileSetId()), typeid(TileManager).name());
	}
}

void TileManager::DestroyTile(EntityId entityId)
{
	auto itr = tileIdTable.find(entityId);
	if (itr != tileIdTable.end())
	{
		tileIdTable.erase(itr);
		Debug::LogWarning("Tile with EntityId: " + std::to_string(entityId) + " was deleted from TileIdTable", typeid(TileManager).name());
	}
	else
	{
		Debug::LogWarning("Tile with EntityId: " + std::to_string(entityId) + " not found", typeid(TileManager).name());
	}
}
