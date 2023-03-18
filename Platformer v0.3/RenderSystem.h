#pragma once

#include <unordered_map>

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
	static std::unordered_map<EntityId, DrawableComponent*> enabledDrawables;
	static std::unordered_map<EntityId, DrawableComponent*> disabledDrawables;

	Window* window;
};

