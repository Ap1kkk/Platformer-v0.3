#pragma once

#include "SFML/Graphics.hpp"
#include "Component.h"
#include "AssetAllocator.h"
#include "EntityManager.h"

class DrawableComponent : public Component
{
public:
	//TODO сменить стандартную текстуру
	DrawableComponent() : textureFilename("viking.png")
	{
		//auto owner = EntityManager::GetEntityById<GameObject>(ownerId);
		//ownerTransform = owner->GetComponent<TransformComponent>();
		Debug::LogInfo("Created with id: " + std::to_string(componentId), typeid(*this).name());
	}
	~DrawableComponent()
	{
		//Debug::LogWarning("Destructor", typeid(*this).name());
	}

	//void Draw(Window* window, sf::Vector2f& centerPosition)
	//{
	//	SetWorldPosition(centerPosition);
	//	window->Draw(sprite);
	//}

	void Draw(Window* window)
	{
		window->Draw(sprite);
	}

	//void EnableToDraw()
	//{

	//}

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

	inline sf::FloatRect GetSpriteBounds() const { return sprite.getGlobalBounds(); }

	
private:
	sf::Sprite sprite;
	std::string textureFilename;

	//TransformComponent* ownerTransform;
};