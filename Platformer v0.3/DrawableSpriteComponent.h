#pragma once

#include "DrawableComponent.h"

class DrawableSpriteComponent : public DrawableComponent
{
public:

	void Draw(Window* window) override
	{
		SynchronizeTransform();
		window->Draw(sprite);
	}

	void SetWorldPosition(sf::Vector2f& centerPosition) override
	{
		//const sf::IntRect& spriteBounds = sprite.getTextureRect();
		//const sf::Vector2f& spriteScale = sprite.getScale();
		//sprite.setPosition(
		//	centerPosition.x - ((abs(spriteBounds.width) * 0.5f) * spriteScale.x),
		//	centerPosition.y - ((abs(spriteBounds.height) * 0.5f) * spriteScale.y)
		//);
		sprite.setPosition(centerPosition);
	}
	void SetRotation(float angleInDeg) override
	{
		sprite.setRotation(angleInDeg);
	}

	void SetTexture(const std::string& filename)
	{
		sprite.setTexture(AssetAllocator::GetTexture(AssetAllocator::GetPath() + filename));
		textureFilename = filename;
		auto size = sprite.getGlobalBounds();
		sprite.setOrigin(size.width / 2, size.height / 2);
	}
	void SetTextureRect(const std::string& filename, sf::IntRect intRect)
	{
		SetTexture(filename);
		sprite.setTextureRect(intRect);
		auto size = sprite.getGlobalBounds();
		sprite.setOrigin(size.width / 2, size.height / 2);
	}

	inline sf::FloatRect GetSpriteBounds() const { return sprite.getGlobalBounds(); }


	void OnEnable() override
	{
		EventData data(EventType::OnSpriteDrawableEnabled);
		data.id = componentId;

		Event::Invoke(data);
	}

	void OnDisable() override
	{
		EventData data(EventType::OnSpriteDrawableDisabled);
		data.id = componentId;

		Event::Invoke(data);
	}

private:
	sf::Sprite sprite;
	std::string textureFilename;

};

