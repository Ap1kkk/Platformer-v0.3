#include "GameObject.h"

GameObject::GameObject() : isDrawable(false), isEnabledToDraw(false), isPhysical(false)
{
	transform = AddComponent<TransformComponent>();
	transform->SetPosition(0.f, 0.f);
}

DrawableComponent* GameObject::MakeDrawable(bool isEnabledToDraw)
{
	isDrawable = true;
	this->isEnabledToDraw = isEnabledToDraw;
	drawableComponent = AddComponent<DrawableComponent>();
	drawableComponent->Initialize(transform);
	RenderSystem::AddDrawable(entityId, drawableComponent, isEnabledToDraw);
	return drawableComponent;
}

void GameObject::EnableToDraw()
{
	if (isDrawable)
	{
		if (!isEnabledToDraw)
		{
			isEnabledToDraw = true;
			RenderSystem::EnableDrawable(entityId);
		}
		else
		{
			Debug::LogWarning("Object is already enabled to draw");
		}
	}
	else
	{
		Debug::LogWarning("Object with id: " + std::to_string(entityId) + " is not drawable");
	}
}

void GameObject::DisableToDraw()
{
	if (isDrawable)
	{
		if (isEnabledToDraw)
		{
			isEnabledToDraw = false;
			RenderSystem::DisableDrawable(entityId);
		}
		else
		{
			Debug::LogWarning("Object is already disabled to draw");
		}
	}
	else
	{
		Debug::LogWarning("Object with id: " + std::to_string(entityId) + " is not drawable");
	}
}

void GameObject::SetTexture(const std::string& filename)
{
	if (isDrawable)
	{
		drawableComponent->SetTexture(filename);
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
		auto spriteRect = drawableComponent->GetSpriteBounds();
		return b2Vec2(spriteRect.width / 2, spriteRect.height / 2);
	}
	else
	{
		Debug::LogWarning("Can't get sprite size because object must me drawable and physical");
	}
}