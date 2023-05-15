#include "UIObject.h"

UIObject::UIObject()
{
	Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
}

void UIObject::Initialize(DrawLayer drawLayer)
{
	transformUI = AddComponent<TransformUIComponent>();

	transformUI->SetPosition(position);

	this->drawLayer = drawLayer;
	this->isEnabledToDraw = isEnabledToDraw;

	drawableSpriteComponent = AddComponent<DrawableSpriteComponent>();
	drawableSpriteComponent->Initialize(transformUI);
	drawableSpriteComponent->SetDrawLayer(drawLayer);
	RenderSystem::AddDrawable(drawableSpriteComponent);

	drawableTextComponent = AddComponent<DrawableTextComponent>();
	drawableTextComponent->Initialize(transformUI);
	drawableTextComponent->SetDrawLayer(drawLayer);
	RenderSystem::AddDrawable(drawableTextComponent);
}

void UIObject::SetTexture(const std::string& filename)
{
	drawableSpriteComponent->SetTexture(filename);
}

void UIObject::SetTextureRect(const std::string& filename, sf::IntRect intRect)
{
	drawableSpriteComponent->SetTextureRect(filename, intRect);
}

void UIObject::SetUIPosition(sf::Vector2f position)
{
	this->position = position;
	transformUI->SetPosition(position);
}
