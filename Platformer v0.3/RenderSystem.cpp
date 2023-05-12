#include "RenderSystem.h"

//std::multimap<DrawLayer, std::pair< EntityId, DrawableComponent*>> RenderSystem::drawMap = {};
//std::multimap<DrawLayer, std::pair< EntityId, DrawableComponent*>> RenderSystem::drawPauseBuffer = {};
//
//std::unordered_map<EntityId, DrawableComponent*> RenderSystem::enabledDrawables = {};
//std::unordered_map<EntityId, DrawableComponent*> RenderSystem::disabledDrawables = {};
//
//std::unordered_map<EntityId, DrawableComponent*> RenderSystem::pauseBuffer = {};

std::map<DrawLayer, std::map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>>*> RenderSystem::drawMapNew = {};
std::map<DrawLayer, std::map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>>*> RenderSystem::drawPauseBufferNew = {};
std::unordered_map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>> RenderSystem::enabledDrawablesNew = {};
std::unordered_map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>> RenderSystem::disabledDrawablesNew = {};
std::unordered_map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>> RenderSystem::pauseBufferNew = {};

RenderSystem::RenderSystem(Window* window) : window(window)
{}

void RenderSystem::Draw()
{
	//for (auto& drawable : drawMap)
	//{
	//	drawable.second.second->Draw(window);
	//}

	//новый вариант
	for (auto& layer : drawMapNew)
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

//void RenderSystem::AddDrawable(EntityId entityId, DrawableComponent* drawable, bool isEnabled)
//{
//	auto itr1 = enabledDrawables.find(entityId);
//	auto itr2 = disabledDrawables.find(entityId);
//
//	if (itr1 != enabledDrawables.end() || itr2 != disabledDrawables.end())
//	{
//		Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " is already added", typeid(RenderSystem).name());
//	}
//	else
//	{
//		if (isEnabled)
//		{
//			enabledDrawables.emplace(entityId, drawable);
//			AddToDrawMap(entityId, drawable);
//		}
//		else
//		{
//			disabledDrawables.emplace(entityId, drawable);
//		}
//	}
//}

void RenderSystem::AddDrawable(EntityId entityId, DrawableSpriteComponent* drawable, bool isEnabled)
{
	{
		auto itr = enabledDrawablesNew.find(entityId);

		if (itr != enabledDrawablesNew.end())
		{
			if (itr->second.first != nullptr)
			{
				Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " is already added", typeid(RenderSystem).name());
				return;
			}
			else
			{
				itr->second.first = drawable;
				//TODO Добавить обновление пары
				UpdateDrawMap(entityId, itr->second);
				return;
			}
		}
	}

	{
		auto itr = disabledDrawablesNew.find(entityId);

		if (itr != disabledDrawablesNew.end())
		{
			if (itr->second.first != nullptr)
			{
				Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " is already added", typeid(RenderSystem).name());
				return;
			}
			else
			{
				itr->second.first = drawable;
				return;
			}
		}
	}

	if (isEnabled)
	{
		enabledDrawablesNew.emplace(std::make_pair(entityId, std::make_pair(drawable, nullptr)));
		AddToDrawMap(entityId, drawable);
	}
	else
	{
		disabledDrawablesNew.emplace(std::make_pair(entityId, std::make_pair(drawable, nullptr)));
	}
	
}

void RenderSystem::AddDrawable(EntityId entityId, DrawableTextComponent* drawable, bool isEnabled)
{
	{
		auto itr = enabledDrawablesNew.find(entityId);

		if (itr != enabledDrawablesNew.end())
		{
			if (itr->second.second != nullptr)
			{
				Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " is already added", typeid(RenderSystem).name());
				return;
			}
			else
			{
				itr->second.second = drawable;
				//TODO Добавить обновление пары
				UpdateDrawMap(entityId, itr->second);
				return;
			}
		}
	}

	{
		auto itr = disabledDrawablesNew.find(entityId);

		if (itr != disabledDrawablesNew.end())
		{
			if (itr->second.second != nullptr)
			{
				Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " is already added", typeid(RenderSystem).name());
				return;
			}
			else
			{
				itr->second.second = drawable;
				return;
			}
		}
	}

	if (isEnabled)
	{
		enabledDrawablesNew.emplace(std::make_pair(entityId, std::make_pair(nullptr, drawable)));
		AddToDrawMap(entityId, drawable);
	}
	else
	{
		disabledDrawablesNew.emplace(std::make_pair(entityId, std::make_pair(nullptr, drawable)));
	}
}

void RenderSystem::DeleteDrawable(EntityId entityId)
{
	//auto itr1 = enabledDrawables.find(entityId);
	//auto itr2 = disabledDrawables.find(entityId);

	//if (itr1 != enabledDrawables.end() || itr2 != disabledDrawables.end())
	//{
	//	if (itr1 != enabledDrawables.end())
	//	{
	//		enabledDrawables.erase(itr1);
	//		DeleteFromDrawMap(entityId);
	//	}
	//	else
	//	{
	//		disabledDrawables.erase(itr2);
	//	}
	//	Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " was deleted", typeid(RenderSystem).name());
	//}
	//else
	//{
	//	Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " is already deleted", typeid(RenderSystem).name());
	//}


	//новый вариант
	{
		auto itr = enabledDrawablesNew.find(entityId);

		if (itr != enabledDrawablesNew.end())
		{
			enabledDrawablesNew.erase(itr);
			DeleteFromDrawMap(entityId);
			Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " was deleted", typeid(RenderSystem).name());
			return;
		}
	}

	{
		auto itr = disabledDrawablesNew.find(entityId);

		if (itr != disabledDrawablesNew.end())
		{
			disabledDrawablesNew.erase(itr);
			DeleteFromDrawMap(entityId);
			Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " was deleted", typeid(RenderSystem).name());
			return;
		}
	}

	Debug::LogWarning("Drawable with EntityId: " + std::to_string(entityId) + " is already deleted", typeid(RenderSystem).name());
}

void RenderSystem::EnableDrawable(EntityId entityId)
{
	//auto itr = disabledDrawables.find(entityId);
	//if (itr != disabledDrawables.end())
	//{
	//	auto drawable = disabledDrawables.at(entityId);
	//	disabledDrawables.erase(itr);
	//	enabledDrawables.emplace(entityId, drawable);
	//	AddToDrawMap(entityId, drawable);

	//	Debug::LogInfo("Drawable with EntityId: " + std::to_string(entityId) + " was enabled", typeid(RenderSystem).name());
	//}
	//else
	//{
	//	Debug::LogWarning("Can't enable drawable with EntityId( " + std::to_string(entityId) + " ) : drawable not found", typeid(RenderSystem).name());
	//}

	//новый вариант
	{
		auto itr = disabledDrawablesNew.find(entityId);
		if (itr != disabledDrawablesNew.end())
		{
			auto& pair = disabledDrawablesNew.at(entityId);
			enabledDrawablesNew.emplace(std::make_pair(entityId, std::make_pair(pair.first, pair.second)));
			
			if (pair.first != nullptr)
			{
				AddToDrawMap(entityId, pair.first);
			}
			if (pair.second != nullptr)
			{
				AddToDrawMap(entityId, pair.second);
			}
			disabledDrawablesNew.erase(itr);
		}
		else
		{
			Debug::LogWarning("Can't enable drawable with EntityId( " + std::to_string(entityId) + " ) : drawable not found", typeid(RenderSystem).name());
		}
	}
}

void RenderSystem::DisableDrawable(EntityId entityId)
{
	//auto itr = enabledDrawables.find(entityId);
	//if (itr != enabledDrawables.end())
	//{
	//	auto drawable = enabledDrawables.at(entityId);
	//	enabledDrawables.erase(itr);
	//	DeleteFromDrawMap(entityId);
	//	disabledDrawables.emplace(entityId, drawable);

	//	Debug::LogInfo("Drawable with EntityId: " + std::to_string(entityId) + " was disabled", typeid(RenderSystem).name());
	//}
	//else
	//{
	//	Debug::LogWarning("Can't disable drawable with EntityId( " + std::to_string(entityId) + " ) : drawable not found", typeid(RenderSystem).name());
	//}

	//новый вариант
	{
		auto itr = enabledDrawablesNew.find(entityId);
		if (itr != enabledDrawablesNew.end())
		{
			auto pair = enabledDrawablesNew.at(entityId);
			disabledDrawablesNew.emplace(std::make_pair(entityId, std::make_pair(pair.first, pair.second)));

			DeleteFromDrawMap(entityId);
			enabledDrawablesNew.erase(itr);
		}
		else
		{
			Debug::LogWarning("Can't disable drawable with EntityId( " + std::to_string(entityId) + " ) : drawable not found", typeid(RenderSystem).name());
		}
	}
}

void RenderSystem::MoveActiveToPauseBuffer()
{
	//for (auto& drawPair : drawMap)
	//{
	//	drawPauseBuffer.emplace(drawPair);
	//}
	//drawMap.clear();

	//for (auto& drawable : enabledDrawables)
	//{
	//	pauseBuffer.emplace(drawable);
	//}
	//enabledDrawables.clear();

	//новый вариант
	for (auto& drawPair : drawMapNew)
	{
		drawPauseBufferNew.emplace(drawPair);
	}
	drawMapNew.clear();

	for (auto& drawPair : enabledDrawablesNew)
	{
		pauseBufferNew.emplace(drawPair);
	}
	enabledDrawablesNew.clear();
}

void RenderSystem::RetrieveActiveFromPauseBuffer()
{
	//for (auto& drawPair : drawPauseBuffer)
	//{
	//	drawMap.emplace(drawPair);
	//}
	//drawPauseBuffer.clear();

	//for (auto& drawable : pauseBuffer)
	//{
	//	enabledDrawables.emplace(drawable);
	//}
	//pauseBuffer.clear();

	//новый вариант
	for (auto& drawPair : drawPauseBufferNew)
	{
		drawMapNew.emplace(drawPair);
	}
	drawPauseBufferNew.clear();

	for (auto& drawPair : pauseBufferNew)
	{
		enabledDrawablesNew.emplace(drawPair);
	}
	pauseBufferNew.clear();
}

//void RenderSystem::AddToDrawMap(EntityId entityId, DrawableComponent* drawable)
//{
//	drawMap.emplace(std::make_pair(drawable->GetDrawLayer(), std::make_pair(entityId, drawable)));
//
//}

void RenderSystem::AddToDrawMap(EntityId entityId, DrawableSpriteComponent* drawable)
{
	auto layer = drawMapNew.find(drawable->GetDrawLayer());
	if (layer != drawMapNew.end())
	{
		auto itr = layer->second->find(entityId);
		if (itr != layer->second->end())
		{
			itr->second.first = drawable;
		}
		else
		{
			layer->second->emplace(std::make_pair(entityId, std::make_pair(drawable, nullptr)));
		}
	}
	else
	{
		auto newMap = new std::map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>>;
		newMap->emplace(std::make_pair(entityId, std::make_pair(drawable, nullptr)));

		drawMapNew.emplace(std::make_pair(drawable->GetDrawLayer(), newMap));
	}
}

void RenderSystem::AddToDrawMap(EntityId entityId, DrawableTextComponent* drawable)
{
	auto layer = drawMapNew.find(drawable->GetDrawLayer());
	if (layer != drawMapNew.end())
	{
		auto itr = layer->second->find(entityId);
		if (itr != layer->second->end())
		{
			itr->second.second = drawable;
		}
		else
		{
			layer->second->emplace(std::make_pair(entityId, std::make_pair(nullptr, drawable)));
		}
	}
	else
	{
		auto newMap = new std::map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>>;
		newMap->emplace(std::make_pair(entityId, std::make_pair(nullptr, drawable)));

		drawMapNew.emplace(std::make_pair(drawable->GetDrawLayer(), newMap));
	}
}

void RenderSystem::DeleteFromDrawMap(EntityId entityId)
{
	//for (auto itr = drawMap.begin(); itr != drawMap.end(); ++itr)
	//{
	//	if (itr->second.first == entityId)
	//	{
	//		drawMap.erase(itr);
	//		break;
	//	}
	//}

	// новый вариант
	for (auto itr = drawMapNew.begin(); itr != drawMapNew.end(); ++itr)
	{
		auto drawable = itr->second->find(entityId);
		if (drawable != itr->second->end())
		{
			itr->second->erase(drawable);
			break;
		}

	}
}
