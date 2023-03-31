#pragma once

#include "Entity.h"
#include "Debug.h"
#include "PhysicComponent.h"
#include "RenderSystem.h"

class GameObject : public Entity
{
public:
	/// <summary>
	/// By default contains TransformComponent
	/// Also not drawable and not physical
	/// </summary>
	GameObject();

	virtual ~GameObject() {}

	//TODO добавить возможность включать и выключать просчет физики

	inline bool IsDrawable() { return isDrawable; }
	inline bool IsPhysical() { return isPhysical; }

	/// <summary>
	/// Makes object drawable
	/// Requires call of SetTexture method
	/// </summary>
	/// <param name="isEnabledToDraw"></param>
	/// <returns>Ponter to added DrawableComponent</returns>
	DrawableComponent* MakeDrawable(bool isEnabledToDraw, DrawLayer drawLayer);

	void EnableToDraw();
	void DisableToDraw();

	void SetTexture(const std::string& filename);
	void SetTextureRect(const std::string& filename, sf::IntRect intRect);

	PhysicComponent* MakePhysical();

	/// <summary>
	/// Return a vector with a half sizes of an object's sprite
	/// </summary>
	/// <returns></returns>
	b2Vec2 GetSpriteBoxHalfSize();

protected:
	bool isDrawable;
	bool isEnabledToDraw;
	bool isPhysical;

	TransformComponent* transform;
	DrawableComponent* drawableComponent;
	PhysicComponent* physicComponent;

};