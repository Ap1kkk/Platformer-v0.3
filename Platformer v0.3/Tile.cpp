#include "Tile.h"

void Tile::Awake()
{
	ProcessTileData();
	transform->SetPosition(tileData.centerPosition);
	transform->SetAngleInDeg(0);
}

void Tile::OnDestroy()
{
	tileManager->DestroyTile(entityId);
}

void Tile::ProcessTileData()
{
	AddSpriteComponent(tileData.drawLayer);
	sf::IntRect tileBounds = { tileData.leftTopCornerPosition, tileData.size };
	SetTextureRect(tileData.textureFilename, tileBounds);
}
