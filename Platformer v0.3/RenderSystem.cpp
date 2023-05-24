#include "RenderSystem.h"

std::map<DrawLayer, std::map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>>*> RenderSystem::drawMap = {};
std::map<DrawLayer, std::map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>>*> RenderSystem::drawPauseBuffer = {};

RenderSystem::RenderSystem(Window* window) : window(window)
{}

void RenderSystem::Draw()
{
	for (auto& layer : drawMap)
	{
		for (auto itr = layer.second->begin(); itr != layer.second->end(); ++itr)
		{
			if (itr->second.first != nullptr)
			{
				itr->second.first->Draw(window);
			}
			if (itr->second.second != nullptr)
			{
				itr->second.second->Draw(window);
			}
		}
	}

}

void RenderSystem::AddDrawable(DrawableSpriteComponent* drawable)
{
	AddToDrawMap(drawable);
}

void RenderSystem::AddDrawable(DrawableTextComponent* drawable)
{
	AddToDrawMap(drawable);
}

void RenderSystem::DeleteDrawable(DrawableSpriteComponent* drawable)
{
	if (drawable->IsEnabled())
	{
		DeleteFromDrawMap(drawable);
	}
	else
	{
		Debug::LogWarning("Sprite Drawable with EntityId: " + std::to_string(drawable->GetOwnerId()) + " is already disabled", typeid(RenderSystem).name());
	}
}
void RenderSystem::DeleteDrawable(DrawableTextComponent* drawable)
{
	if (drawable->IsEnabled())
	{
		DeleteFromDrawMap(drawable);
	}
	else
	{
		Debug::LogWarning("Text Drawable with EntityId: " + std::to_string(drawable->GetOwnerId()) + " is already disabled", typeid(RenderSystem).name());
	}
}

void RenderSystem::MoveActiveToPauseBuffer()
{
	for (auto& drawPair : drawMap)
	{
		drawPauseBuffer.emplace(drawPair);
	}
	drawMap.clear();
}

void RenderSystem::RetrieveActiveFromPauseBuffer()
{
	//TODO баг, если есть что-то с таким же слоем, то оно не извлечется
	for (auto& drawPair : drawPauseBuffer)
	{
		drawMap.emplace(drawPair);
	}
	drawPauseBuffer.clear();
}

void RenderSystem::AddToDrawMap(DrawableSpriteComponent* drawable)
{
	auto ownerId = drawable->GetOwnerId();
	auto layer = drawMap.find(drawable->GetDrawLayer());
	if (layer != drawMap.end())
	{
		auto itr = layer->second->find(ownerId);
		if (itr != layer->second->end())
		{
			itr->second.first = drawable;
		}
		else
		{
			layer->second->emplace(std::make_pair(ownerId, std::make_pair(drawable, nullptr)));
		}
	}
	else
	{
		auto newMap = new std::map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>>;
		newMap->emplace(std::make_pair(ownerId, std::make_pair(drawable, nullptr)));

		drawMap.emplace(std::make_pair(drawable->GetDrawLayer(), newMap));
	}
}

void RenderSystem::AddToDrawMap(DrawableTextComponent* drawable)
{
	auto ownerId = drawable->GetOwnerId();
	auto layer = drawMap.find(drawable->GetDrawLayer());
	if (layer != drawMap.end())
	{
		auto itr = layer->second->find(ownerId);
		if (itr != layer->second->end())
		{
			itr->second.second = drawable;
		}
		else
		{
			layer->second->emplace(std::make_pair(ownerId, std::make_pair(nullptr, drawable)));
		}
	}
	else
	{
		auto newMap = new std::map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>>;
		newMap->emplace(std::make_pair(ownerId, std::make_pair(nullptr, drawable)));

		drawMap.emplace(std::make_pair(drawable->GetDrawLayer(), newMap));
	}
}

void RenderSystem::DeleteFromDrawMap(DrawableSpriteComponent* drawable)
{
	auto drawLayer = drawable->GetDrawLayer();
	auto ownerId = drawable->GetOwnerId();

	auto map = drawMap.find(drawLayer);
	if (map != drawMap.end())
	{
		auto itr = map->second->find(ownerId);
		if (itr != map->second->end())
		{
			itr->second.first = nullptr;
		}
		else
		{
			Debug::LogWarning("Can't delete Sprite Drawable\nOwner with id:" + std::to_string(ownerId) + " not found", typeid(RenderSystem).name());
		}
	}
	else
	{
		Debug::LogWarning("Can't delete Sprite Drawable\nDrawLayer:" + std::to_string(drawLayer) + " not found", typeid(RenderSystem).name());
	}
}

void RenderSystem::DeleteFromDrawMap(DrawableTextComponent* drawable)
{
	auto drawLayer = drawable->GetDrawLayer();
	auto ownerId = drawable->GetOwnerId();

	auto map = drawMap.find(drawLayer);
	if (map != drawMap.end())
	{
		auto itr = map->second->find(ownerId);
		if (itr != map->second->end())
		{
			itr->second.second = nullptr;
		}
		else
		{
			Debug::LogWarning("Can't delete Text Drawable\nOwner with id:" + std::to_string(ownerId) + " not found");
		}
	}
	else
	{
		Debug::LogWarning("Can't delete Text Drawable\nDrawLayer:" + std::to_string(drawLayer) + " not found");
	}
}