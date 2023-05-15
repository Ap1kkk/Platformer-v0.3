#include "GameObject.h"

GameObject::GameObject() : isDrawable(false), isEnabledToDraw(false), isPhysical(false)
{
	transform = AddComponent<TransformComponent>();
	transform->SetPosition(0.f, 0.f);
}

void GameObject::SetTexture(const Filename& filename)
{
	if (isDrawable)
	{
		drawableSpriteComponent->SetTexture(filename);
	}
	else
	{
		Debug::LogWarning("Can't attach texture to not drawable object");
	}
}

void GameObject::SetTextureRect(const Filename& filename, const sf::IntRect& intRect)
{
	if (isDrawable)
	{
		drawableSpriteComponent->SetTextureRect(filename, intRect);
	}
	else
	{
		Debug::LogWarning("Can't attach texture to not drawable object");
	}
}

PhysicComponent* GameObject::MakePhysical()
{
	isPhysical = true;
	physicComponent = AddComponent<PhysicComponent>();
	physicComponent->Initialize(transform);
	return physicComponent;
}

b2Vec2 GameObject::GetSpriteBoxHalfSize()
{
	if (isDrawable && isPhysical)
	{
		auto spriteRect = drawableSpriteComponent->GetSpriteBounds();
		return b2Vec2(spriteRect.width / 2, spriteRect.height / 2);
	}
	else
	{
		Debug::LogWarning("Can't get sprite size because object must me drawable and physical");
	}
}

void GameObject::SetSpawnPosition(const sf::Vector2f& spawnPosition)
{
	this->spawnPosition = spawnPosition;
}

void GameObject::SetSpawnPosition(const float x, const float y)
{
	spawnPosition.x = x;
	spawnPosition.y = y;

	Debug::Log(spawnPosition);
}
