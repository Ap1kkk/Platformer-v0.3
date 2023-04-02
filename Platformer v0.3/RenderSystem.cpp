#include "RenderSystem.h"

std::multimap<DrawLayer, std::pair< EntityId, DrawableComponent*>> RenderSystem::drawMap = {};
std::multimap<DrawLayer, std::pair< EntityId, DrawableComponent*>> RenderSystem::drawPauseBuffer = {};

std::unordered_map<EntityId, DrawableComponent*> RenderSystem::enabledDrawables = {};
std::unordered_map<EntityId, DrawableComponent*> RenderSystem::disabledDrawables = {};

std::unordered_map<EntityId, DrawableComponent*> RenderSystem::pauseBuffer = {};

RenderSystem::RenderSystem(Window* window) : window(window)
{}

void RenderSystem::Draw()
{
	for (auto& drawable : drawMap)
	{
		drawable.second.second->Draw(window);
	}
}

void RenderSystem::AddDrawable(EntityId entityId, DrawableComponent* drawable, bool isEnabled)
{
	auto itr1 = enabledDrawables.find(entityId);
	auto itr2 = disabledDrawables.find(entityId);

	if (itr1 != enabledDrawables.end() || itr2 != disabledDrawables.end())
	{
		Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " is already added", typeid(RenderSystem).name());
	}
	else
	{
		if (isEnabled)
		{
			enabledDrawables.emplace(entityId, drawable);
			AddToDrawMap(entityId, drawable);
		}
		else
		{
			disabledDrawables.emplace(entityId, drawable);
		}
	}
}

void RenderSystem::DeleteDrawable(EntityId entityId)
{
	auto itr1 = enabledDrawables.find(entityId);
	auto itr2 = disabledDrawables.find(entityId);

	if (itr1 != enabledDrawables.end() || itr2 != disabledDrawables.end())
	{
		if (itr1 != enabledDrawables.end())
		{
			enabledDrawables.erase(itr1);
			DeleteFromDrawMap(entityId);
		}
		else
		{
			disabledDrawables.erase(itr2);
		}
		Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " was deleted", typeid(RenderSystem).name());
	}
	else
	{
		Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " is already deleted", typeid(RenderSystem).name());
	}
}

void RenderSystem::EnableDrawable(EntityId entityId)
{
	auto itr = disabledDrawables.find(entityId);
	if (itr != disabledDrawables.end())
	{
		auto drawable = disabledDrawables.at(entityId);
		disabledDrawables.erase(itr);
		enabledDrawables.emplace(entityId, drawable);
		AddToDrawMap(entityId, drawable);

		Debug::LogInfo("Drawable with EntityId: " + std::to_string(entityId) + " was enabled", typeid(RenderSystem).name());
	}
	else
	{
		Debug::LogWarning("Can't enable drawable with EntityId( " + std::to_string(entityId) + " ) : drawable not found", typeid(RenderSystem).name());
	}
}

void RenderSystem::DisableDrawable(EntityId entityId)
{
	auto itr = enabledDrawables.find(entityId);
	if (itr != enabledDrawables.end())
	{
		auto drawable = enabledDrawables.at(entityId);
		enabledDrawables.erase(itr);
		DeleteFromDrawMap(entityId);
		disabledDrawables.emplace(entityId, drawable);

		Debug::LogInfo("Drawable with EntityId: " + std::to_string(entityId) + " was disabled", typeid(RenderSystem).name());
	}
	else
	{
		Debug::LogWarning("Can't disable drawable with EntityId( " + std::to_string(entityId) + " ) : drawable not found", typeid(RenderSystem).name());
	}
}

void RenderSystem::MoveActiveToPauseBuffer()
{
	for (auto& drawPair : drawMap)
	{
		drawPauseBuffer.emplace(drawPair);
	}
	drawMap.clear();

	for (auto& drawable : enabledDrawables)
	{
		pauseBuffer.emplace(drawable);
	}
	enabledDrawables.clear();
}

void RenderSystem::RetrieveActiveFromPauseBuffer()
{
	for (auto& drawPair : drawPauseBuffer)
	{
		drawMap.emplace(drawPair);
	}
	drawPauseBuffer.clear();

	for (auto& drawable : pauseBuffer)
	{
		enabledDrawables.emplace(drawable);
	}
	pauseBuffer.clear();
}
