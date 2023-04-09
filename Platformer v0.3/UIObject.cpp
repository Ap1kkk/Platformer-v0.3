#include "UIObject.h"

UIObject::UIObject()
{
	Debug::LogInfo("Created with id: " + std::to_string(entityId), typeid(*this).name());
}

void UIObject::Initialize(bool isEnabledToDraw, DrawLayer drawLayer)
{
	transformUI = AddComponent<TransformUIComponent>();

	transformUI->SetPosition(position);

	this->drawLayer = drawLayer;
	this->isEnabledToDraw = isEnabledToDraw;
	drawableComponent = AddComponent<DrawableComponent>();
	drawableComponent->Initialize(transformUI);
	drawableComponent->SetDrawLayer(drawLayer);
	RenderSystem::AddDrawable(entityId, drawableComponent, isEnabledToDraw);
}

void UIObject::SetTexture(const std::string& filename)
{
	drawableComponent->SetTexture(filename);
}

void UIObject::SetTextureRect(const std::string& filename, sf::IntRect intRect)
{
	drawableComponent->SetTextureRect(filename, intRect);
}

void UIObject::SetUIPosition(sf::Vector2f position)
{
	this->position = position;
	transformUI->SetPosition(position);
}
