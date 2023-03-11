#pragma once

#include "SFML/Graphics.hpp"
#include "Component.h"
#include "AssetAllocator.h"
#include "EntityManager2.h"

class DrawableComponent : public Component
{
public:
	DrawableComponent() : textureFilename("viking.png") 
	{
		//auto owner = EntityManager2::GetEntityById<GameObject>(ownerId);
		//ownerTransform = owner->GetComponent<TransformComponent>();
	}
	~DrawableComponent() {}

	void LateUpdate() override
	{

	}

	void Draw(Window* window, sf::Vector2f& centerPosition)
	{
		SetWorldPosition(centerPosition);
		window->Draw(sprite);
	}

	void SetTexture(const std::string& filename)
	{
		sprite.setTexture(AssetAllocator::GetTexture(AssetAllocator::GetPath() + filename));
		textureFilename = filename;
	}

	void SetWorldPosition(sf::Vector2f& centerPosition)
	{
		const sf::IntRect& spriteBounds = sprite.getTextureRect();
		const sf::Vector2f& spriteScale = sprite.getScale();
		sprite.setPosition(
			centerPosition.x - ((abs(spriteBounds.width) * 0.5f) * spriteScale.x),
			centerPosition.y - ((abs(spriteBounds.height) * 0.5f) * spriteScale.y)
		);
	}

	
private:
	sf::Sprite sprite;
	std::string textureFilename;

	//TransformComponent* ownerTransform;
};