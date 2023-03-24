#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ITileManager.h"

struct TileData
{
	TileId id;

	sf::Vector2f centerPosition;
	/// <summary>
	/// Set in pixels
	/// </summary>
	sf::Vector2i leftTopCornerPosition;
	/// <summary>
	/// Set in pixels
	/// </summary>
	sf::Vector2i size;
	Filename textureFilename;

	bool isEnabled = true;
	//TODO добавить слой отрисовки
};

class Tile : public GameObject
{
public:
	Tile() {}

	void SetTileData(TileData& data) { tileData = data; }
	void SetTileManager(ITileManager* tileManager) { this->tileManager = tileManager; }

	void Awake() override;

	void OnDestroy() override;

private:
	void ProcessTileData();

	sf::Sprite sprite;
	TileData tileData;
	ITileManager* tileManager;
};

