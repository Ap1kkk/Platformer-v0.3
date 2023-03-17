#pragma once

#include "Entity.h"
#include "Debug.h"
#include "PhysicComponent.h"
#include "RenderSystem.h"

class GameObject : public Entity
{
public:
	GameObject() : isDrawable(false),isEnabledToDraw(false), isPhysical(false)
	{
		transform = AddComponent<TransformComponent>();
		transform->SetPosition(0.f, 0.f);
	}

	virtual ~GameObject()
	{
		//Debug::LogWarning("Destructor", typeid(*this).name());
	}

	//����� �������� ���� ������ ���������� ��� ���� ������ � ���������� � drawable
	void SyncronizeDrawable() 
	{
		if (isPhysical)
		{
			transform->SetPosition(physicComponent->GetBodyPosition());
			if (isDrawable)
			{
				drawableComponent->SetWorldPosition(transform->GetPosition());
			}
		}
		else
		{
			Debug::LogWarning("Object is not physical, no need to call this method", typeid(*this).name());
		}
	}

	//TODO �������� ����������� �������� � ��������� ������� ������

	inline bool IsDrawable() { return isDrawable; }
	inline bool IsPhysical() { return isPhysical; }

	//����� ������ ������ ����� �������� ������� ��������
	DrawableComponent* MakeDrawable(bool isEnabledToDraw)
	{
		isDrawable = true;
		this->isEnabledToDraw = isEnabledToDraw;
		drawableComponent = AddComponent<DrawableComponent>();
		RenderSystem::AddDrawable(entityId, drawableComponent, isEnabledToDraw);
		return drawableComponent;
	}

	void EnableToDraw()
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

	void DisableToDraw()
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

protected:
	bool isDrawable;
	bool isEnabledToDraw;
	bool isPhysical;

	TransformComponent* transform;
	DrawableComponent* drawableComponent;
	PhysicComponent* physicComponent;

};