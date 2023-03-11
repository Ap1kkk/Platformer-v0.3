#pragma once

#include <unordered_map>
#include "Window.h"
#include "Entity2.h"

class RenderSystem
{
public:
	RenderSystem(Window* window);

	void Draw();

	void AddDrawable(Entity2* entity);
	void DeleteDrawable(EntityId id);

	void EnableDrawable();
	void DisableDrawable();

private:
	//TODO возможно лучше хранить ид компонента
	std::unordered_map<EntityId, IComponent*> enabledDrawables;
	std::unordered_map<EntityId, IComponent*> disabledDrawables;

	Window* window;
};

