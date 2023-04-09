#pragma once

#include <unordered_map>
#include <map>
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

	static void MoveActiveToPauseBuffer();
	static void RetrieveActiveFromPauseBuffer();

private:

	static void AddToDrawMap(EntityId entityId, DrawableComponent* drawable);

	static void DeleteFromDrawMap(EntityId entityId);

	static std::multimap<DrawLayer, std::pair< EntityId, DrawableComponent*>> drawMap;
	//TODO совместить все в один буфер
	static std::multimap<DrawLayer, std::pair< EntityId, DrawableComponent*>> drawPauseBuffer;

	static std::unordered_map<EntityId, DrawableComponent*> enabledDrawables;
	static std::unordered_map<EntityId, DrawableComponent*> disabledDrawables;
	static std::unordered_map<EntityId, DrawableComponent*> pauseBuffer;

	Window* window;
};

