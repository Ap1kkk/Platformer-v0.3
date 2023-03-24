#pragma once

#include "SFML/Graphics.hpp"
#include "IComponent.h"
#include "AssetAllocator.h"
#include "EntityManager.h"
#include "TransformComponent.h"


/// <summary>
/// Responsible for drawing objects on the screen
/// </summary>
class DrawableComponent : public IComponent
{
public:
	//TODO сменить стандартную текстуру
	DrawableComponent();
	~DrawableComponent() {}

	void Initialize(TransformComponent* transform);

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

	
private:
	sf::Sprite sprite;
	std::string textureFilename;

	TransformComponent* ownerTransform;
};