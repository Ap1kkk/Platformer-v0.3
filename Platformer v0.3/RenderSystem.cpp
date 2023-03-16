#include "RenderSystem.h"

std::unordered_map<EntityId, DrawableComponent*> RenderSystem::enabledDrawables = {};
std::unordered_map<EntityId, DrawableComponent*> RenderSystem::disabledDrawables = {};

RenderSystem::RenderSystem(Window* window) : window(window)
{}

void RenderSystem::Draw()
{
	for (auto& drawable : enabledDrawables)
	{
		drawable.second->Draw(window);
	}
}
