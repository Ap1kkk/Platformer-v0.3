#pragma once

#include <unordered_map>
#include <vector>

#include "Window.h"
#include "DrawableComponent.h"

/// <summary>
/// Responsible for rendering objects to the window
/// </summary>
class RenderSystem
{
public:
	RenderSystem(Window* window);
	~RenderSystem()
	{
		//TODO добавить логику для очистки всех списков
	}

	void Draw();

	static void AddDrawable(EntityId entityId, DrawableComponent* drawable, bool isEnabled);

	static void DeleteDrawable(EntityId entityId);

	static void EnableDrawable(EntityId entityId);
	static void DisableDrawable(EntityId entityId);

private:

	static void SortDrawVector()
	{
		std::sort(drawVector.begin(), drawVector.end(),
			[](DrawableComponent* a, DrawableComponent* b)
			{
				DrawLayer aLayer = a->GetDrawLayer();
				DrawLayer bLayer = b->GetDrawLayer();
				return aLayer < bLayer;
			});
	}

	static void AddToDrawVector(DrawableComponent* drawable)
	{
		drawVector.push_back(drawable);
		SortDrawVector();
	}

	static void DeleteInDrawVector(EntityId ownerId)
	{
		for (auto itr = drawVector.begin(); itr != drawVector.end(); ++itr)
		{
			if ((*itr)->GetOwnerId() == ownerId)
			{
				drawVector.erase(itr);
				break;
			}
		}
	}

	static std::vector<DrawableComponent*> drawVector;
	static std::unordered_map<EntityId, DrawableComponent*> enabledDrawables;
	static std::unordered_map<EntityId, DrawableComponent*> disabledDrawables;

	Window* window;
};

