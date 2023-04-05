#include "DrawableComponent.h"

DrawableComponent::DrawableComponent() : textureFilename("viking.png")
{
	SetComponentLayer(100);
	Debug::LogInfo("Created with id: " + std::to_string(componentId), typeid(*this).name());
}

void DrawableComponent::Initialize(ITransform* transform)
{
	ownerTransform = transform;
}

void DrawableComponent::Draw(Window* window)
{
	SetWorldPosition(ownerTransform->GetPosition());
	SetRotation(ownerTransform->GetAngle());
	window->Draw(sprite);
}

void DrawableComponent::SetTexture(const std::string& filename)
{
	sprite.setTexture(AssetAllocator::GetTexture(AssetAllocator::GetPath() + filename));
	textureFilename = filename;
	auto size = sprite.getTexture()->getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
}

void DrawableComponent::SetTextureRect(const std::string& filename, sf::IntRect intRect)
{
	SetTexture(filename);
	sprite.setTextureRect(intRect);
	auto size = sprite.getTextureRect();
	sprite.setOrigin(size.width / 2, size.height / 2);
}

void DrawableComponent::SetWorldPosition(sf::Vector2f& centerPosition)
{
	const sf::IntRect& spriteBounds = sprite.getTextureRect();
	const sf::Vector2f& spriteScale = sprite.getScale();
	//sprite.setPosition(
	//	centerPosition.x - ((abs(spriteBounds.width) * 0.5f) * spriteScale.x),
	//	centerPosition.y - ((abs(spriteBounds.height) * 0.5f) * spriteScale.y)
	//);
	sprite.setPosition(centerPosition);
}
void DrawableComponent::SetRotation(float angleInDeg)
{
	sprite.setRotation(angleInDeg);
}

