#pragma once

#include "Entity2.h"
#include "Debug.h"

class GameObject : public Entity2
{
public:
	GameObject() : isDrawable(false), isPhysics(false)
	{
		transform = AddComponent<TransformComponent>();
		transform->SetPosition(0.f, 0.f);
	}
	//GameObject(bool isDrawable, bool isPhysics) : isDrawable(isDrawable), isPhysics(isPhysics)
	//{
	//	AddComponent<TransformComponent>();

	//	if (isDrawable)
	//	{
	//		//TODO добавлять компонент Drawable
	//	}
	//	
	//	if (isPhysics)
	//	{
	//		//TODO добавлять физический компонент
	//	}
	//}

	~GameObject()
	{
		Debug::LogWarning("Destructor", typeid(*this).name());
	}

	void EarlyUpdate() override {}

	void Update() override {}

	void LateUpdate() override {}

	//TODO после тестов сделать pure virtual
	//virtual void Draw(Window* window) = 0;
	void Draw(Window* window)
	{
		drawableComponent->Draw(window, transform->GetPosition());
	}

	inline bool IsDrawable() { return isDrawable; }
	inline bool IsPhysics() { return isPhysics; }

	void MakeDrawable()
	{
		isDrawable = true;
		drawableComponent = AddComponent<DrawableComponent>();
		drawableComponent->SetTexture("viking.png");
	}

private:
	bool isDrawable;
	bool isPhysics;

	TransformComponent* transform;
	DrawableComponent* drawableComponent;
	//TODO добавить физический компонент
};