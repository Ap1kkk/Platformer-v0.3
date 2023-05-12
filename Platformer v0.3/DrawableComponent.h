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
	//TODO ������� ����������� ��������
	DrawableComponent();
	~DrawableComponent() {}

	void Initialize(ITransform* transform);

	//void Draw(Window* window) override;

	void SynchronizeTransform()
	{
		SetWorldPosition(ownerTransform->GetPosition());
		SetRotation(ownerTransform->GetAngle());
	}

	////TODO ��������� � ����������
	//void SetTexture(const std::string& filename);
	//void SetTextureRect(const std::string& filename, sf::IntRect intRect);


	////TODO ������� ����� ������������ 
	//void SetWorldSpritePosition(sf::Vector2f& centerPosition);
	//void SetSpriteRotation(float angleInDeg);

	virtual void SetWorldPosition(sf::Vector2f& centerPosition) = 0;
	virtual void SetRotation(float angleInDeg) = 0;

	////TODO ��������� � ����������
	//inline sf::FloatRect GetSpriteBounds() { return sprite.getGlobalBounds(); }

	inline void SetDrawLayer(DrawLayer layer) { drawLayer = layer; }
	inline DrawLayer GetDrawLayer() { return drawLayer; }
	
	////TODO ��������� � ����������
	//void SetTextPosition(sf::Vector2f position)
	//{

	//}
	////TODO ��������� � ����������
	//void SetFont(sf::Font& font)
	//{
	//	text.setFont(font);
	//}
	////TODO ��������� � ����������
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
	////TODO ������ � �����������
	//sf::Sprite sprite;
	//sf::Text text;
	//std::string textureFilename;

	//TransformComponent* ownerTransform;
	ITransform* ownerTransform;

	DrawLayer drawLayer;
};