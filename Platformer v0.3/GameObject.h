#pragma once

#include "Entity.h"
#include "Debug.h"
#include "PhysicComponent.h"

class GameObject : public Entity
{
public:
	GameObject() : isDrawable(false), isPhysical(false)
	{
		transform = AddComponent<TransformComponent>();
		transform->SetPosition(0.f, 0.f);
	}

	~GameObject()
	{
		Debug::LogWarning("Destructor", typeid(*this).name());
	}

	void EarlyUpdate() override
	{
		if (isPhysical)
		{
			transform->SetPosition(physicComponent->GetBodyPosition());
		}
	}

	void Update() override {}

	void LateUpdate() override {}

	//TODO ����� ������ ������� pure virtual
	//virtual void Draw(Window* window) = 0;
	void Draw(Window* window)
	{
		drawableComponent->Draw(window, transform->GetPosition());
	}

	//TODO �������� ����������� �������� � ��������� ��������� � ����� ������� ������
	inline bool IsDrawable() { return isDrawable; }
	inline bool IsPhysical() { return isPhysical; }


	///������� ������ �������� ����� ��������� ����� TransformComponent � PhysicComponent

	//����� ������ ������ ����� �������� ������� ��������
	DrawableComponent* MakeDrawable()
	{
		isDrawable = true;
		drawableComponent = AddComponent<DrawableComponent>();
		return drawableComponent;
	}

	void SetTexture(const std::string& filename)
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

	/// ����� ���������� ����� ����� ������� ����� Initialize,
	/// ������� ������� � ������� ���������� ����
	PhysicComponent* MakePhysical()
	{
		isPhysical = true;
		physicComponent = AddComponent<PhysicComponent>();
		return physicComponent;
	}

	b2Vec2 GetSpriteBoxHalfSize()
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

private:
	bool isDrawable;
	bool isPhysical;

	TransformComponent* transform;
	DrawableComponent* drawableComponent;
	PhysicComponent* physicComponent;

};