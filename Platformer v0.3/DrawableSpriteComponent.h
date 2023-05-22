#pragma once

#include "DrawableComponent.h"

#include "OnComponentUserData.h"

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

	void UpdateTextureRect(sf::IntRect intRect)
	{
		sprite.setTextureRect(intRect);
		auto size = sprite.getGlobalBounds();
		sprite.setOrigin(size.width / 2, size.height / 2);
	}

	inline sf::FloatRect GetSpriteBounds() const { return sprite.getGlobalBounds(); }


	void OnEnable() override
	{
		EventData data(EventType::OnSpriteDrawableEnabled);

		auto userData = new ComponentUserData;
		userData->component = this;

		data.id = componentId;
		data.userData = userData;

		Event::Invoke(data);
	}

	void OnDisable() override
	{
		EventData data(EventType::OnSpriteDrawableDisabled);

		auto userData = new ComponentUserData;
		userData->component = this;

		data.id = componentId;
		data.userData = userData;

		Event::Invoke(data);
	}

	void OnDestroy() override
	{
		EventData data(EventType::OnSpriteDrawableDestroyed);

		auto userData = new ComponentUserData;
		userData->component = this;

		data.id = ownerId;
		data.userData = userData;

		Event::Invoke(data);
	}
private:
	sf::Sprite sprite;
	std::string textureFilename;

};

