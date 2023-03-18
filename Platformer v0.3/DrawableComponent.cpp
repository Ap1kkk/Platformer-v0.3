#include "DrawableComponent.h"

DrawableComponent::DrawableComponent() : textureFilename("viking.png")
{
	Debug::LogInfo("Created with id: " + std::to_string(componentId), typeid(*this).name());
}

void DrawableComponent::Initialize(TransformComponent* transform)
{
	ownerTransform = transform;
}

void DrawableComponent::Draw(Window* window)
{
	SetWorldPosition(ownerTransform->GetPosition());
	window->Draw(sprite);
}

void DrawableComponent::SetTexture(const std::string& filename)
{
	sprite.setTexture(AssetAllocator::GetTexture(AssetAllocator::GetPath() + filename));
	textureFilename = filename;
}

void DrawableComponent::SetWorldPosition(sf::Vector2f& centerPosition)
{
	const sf::IntRect& spriteBounds = sprite.getTextureRect();
	const sf::Vector2f& spriteScale = sprite.getScale();
	sprite.setPosition(
		centerPosition.x - ((abs(spriteBounds.width) * 0.5f) * spriteScale.x),
		centerPosition.y - ((abs(spriteBounds.height) * 0.5f) * spriteScale.y)
	);
}

