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

	void Initialize(ITransform* transform);

	//void Draw(Window* window) override;

	void SynchronizeTransform()
	{
		SetWorldPosition(ownerTransform->GetPosition());
		SetRotation(ownerTransform->GetAngle());
	}

	////TODO перенести в наследника
	//void SetTexture(const std::string& filename);
	//void SetTextureRect(const std::string& filename, sf::IntRect intRect);


	////TODO сделать чисто виртуальными 
	//void SetWorldSpritePosition(sf::Vector2f& centerPosition);
	//void SetSpriteRotation(float angleInDeg);

	virtual void SetWorldPosition(sf::Vector2f& centerPosition) = 0;
	virtual void SetRotation(float angleInDeg) = 0;

	////TODO перенести в наследника
	//inline sf::FloatRect GetSpriteBounds() { return sprite.getGlobalBounds(); }

	inline void SetDrawLayer(DrawLayer layer) { drawLayer = layer; }
	inline DrawLayer GetDrawLayer() { return drawLayer; }
	
	////TODO перенести в наследника
	//void SetTextPosition(sf::Vector2f position)
	//{

	//}
	////TODO перенести в наследника
	//void SetFont(sf::Font& font)
	//{
	//	text.setFont(font);
	//}
	////TODO перенести в наследника
	//void SetText(std::string string)
	//{
	//	text.setCharacterSize(24);
	//	//text.setPosition(100.f, 100.f);
	//	text.setFillColor(sf::Color::Red);
	//	text.setString(string);

	//	auto rect = text.getGlobalBounds();
	//	text.setOrigin(rect.width / 2, rect.height / 2);
	//}

protected:
	////TODO убрать в наследников
	//sf::Sprite sprite;
	//sf::Text text;
	//std::string textureFilename;

	//TransformComponent* ownerTransform;
	ITransform* ownerTransform;

	DrawLayer drawLayer;
};