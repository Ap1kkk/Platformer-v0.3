#include "TileManager.h"

std::unordered_map<EntityId, TileId> TileManager::tileIdTable = {};
std::unordered_map<Filename, TileSetId> TileManager::tileSetTable = {};
std::unordered_map<TileSetId, TileSet*> TileManager::tileSets = {};

ObjectContext TileManager::objectContext;