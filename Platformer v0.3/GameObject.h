#pragma once

#include "Entity.h"
#include "Debug.h"
#include "PhysicComponent.h"
#include "RenderSystem.h"

#include "DrawableSpriteComponent.h"
#include "DrawableTextComponent.h"

class GameObject : public Entity
{
public:
	/// <summary>
	/// By default contains TransformComponent
	/// Also not drawable and not physical
	/// </summary>
	GameObject();

	virtual ~GameObject() {}

	inline bool IsDrawable() { return isDrawable; }
	inline bool IsPhysical() { return isPhysical; }

	DrawableSpriteComponent* AddSpriteComponent(DrawLayer drawLayer) 
	{
		isDrawable = true;

		drawableSpriteComponent = AddComponent<DrawableSpriteComponent>();
		drawableSpriteComponent->Initialize(transform);
		drawableSpriteComponent->SetDrawLayer(drawLayer);
		RenderSystem::AddDrawable(drawableSpriteComponent);
		return drawableSpriteComponent;
	}

	DrawableTextComponent* AddTextComponent(DrawLayer drawLayer)
	{
		isDrawable = true;

		drawableTextComponent = AddComponent<DrawableTextComponent>();
		drawableTextComponent->Initialize(transform);
		drawableTextComponent->SetDrawLayer(drawLayer);
		RenderSystem::AddDrawable(drawableTextComponent);
		drawableTextComponent->Disable();
		return drawableTextComponent;
	}

	virtual void SetTexture(const Filename& filename);
	virtual void SetTextureRect(const Filename& filename, const sf::IntRect& intRect);

	PhysicComponent* MakePhysical();

	/// <summary>
	/// Return a vector with a half sizes of an object's sprite
	/// </summary>
	/// <returns></returns>
	b2Vec2 GetSpriteBoxHalfSize();

	void SetSpawnPosition(const sf::Vector2f& spawnPosition);
	void SetSpawnPosition(const float x, const float y);

protected:
	bool isDrawable;
	bool isEnabledToDraw;
	bool isPhysical;

	sf::Vector2f spawnPosition;

	TransformComponent* transform;
	PhysicComponent* physicComponent;

	DrawableSpriteComponent* drawableSpriteComponent;
	DrawableTextComponent* drawableTextComponent;
};