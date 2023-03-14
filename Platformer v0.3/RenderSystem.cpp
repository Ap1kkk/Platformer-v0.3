#include "RenderSystem.h"

RenderSystem::RenderSystem(Window* window) : window(window)
{}

void RenderSystem::Draw()
{
	for (auto& drawable : enabledDrawables)
	{
		/*drawable.second->Draw(window);*/
	}
}

void RenderSystem::AddDrawable(Entity* entity)
{
	//auto id = entity->
}

void RenderSystem::DeleteDrawable(EntityId id)
{
}
