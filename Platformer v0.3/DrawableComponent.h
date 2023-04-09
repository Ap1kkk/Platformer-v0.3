#pragma once

#include "SFML/Graphics.hpp"
#include "IComponent.h"
#include "AssetAllocator.h"
#include "EntityManager.h"
#include "ITransform.h"

/// <summary>
/// Responsible for drawing objects on the screen
/// </summary>
class DrawableComponent : public IComponent
{
public:
	//TODO сменить стандартную текстуру
	DrawableComponent();
	~DrawableComponent() {}

	//TODO переделать в Awake
	void Initialize(ITransform* transform);

	void Draw(Window* window) override;

	void SetTexture(const std::string& filename);
	void SetTextureRect(const std::string& filename, sf::IntRect intRect);

	/// <summary>
	/// Set the sprite's world position to draw corectly
	/// </summary>
	/// <param name="centerPosition">Vector2f must contain sprite center point</param>
	void SetWorldPosition(sf::Vector2f& centerPosition);

	void SetRotation(float angleInDeg);

	inline sf::FloatRect GetSpriteBounds() const { return sprite.getGlobalBounds(); }

	inline void SetDrawLayer(DrawLayer layer) { drawLayer = layer; }
	inline DrawLayer GetDrawLayer() const { return drawLayer; }
	
private:
	sf::Sprite sprite;
	std::string textureFilename;

	//TransformComponent* ownerTransform;
	ITransform* ownerTransform;

	DrawLayer drawLayer;
};