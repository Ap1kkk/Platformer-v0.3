#pragma once

#include <unordered_map>
#include <map>
#include <vector>

#include "Window.h"
#include "DrawableSpriteComponent.h"
#include "DrawableTextComponent.h"

#include "EventListener.h"

/// <summary>
/// Responsible for rendering objects to the window
/// </summary>
class RenderSystem : public EventListener
{
public:
	RenderSystem(Window* window);
	~RenderSystem()
	{
		//TODO добавить логику для очистки всех списков
		for (auto& item : drawMapNew)
		{
			delete item.second;
		}
	}

	void SubscribeOnEvents()
	{
		SubscribeOnEvent(EventType::OnEntityDestroyedEvent);

		SubscribeOnEvent(EventType::OnSpriteDrawableEnabled); 
		SubscribeOnEvent(EventType::OnSpriteDrawableDisabled); 
		SubscribeOnEvent(EventType::OnTextDrawableEnabled); 
		SubscribeOnEvent(EventType::OnTextDrawableDisabled);
	}

	void Draw();

	static void AddDrawable(EntityId entityId, DrawableSpriteComponent* drawable, bool isEnabled);
	static void AddDrawable(EntityId entityId, DrawableTextComponent* drawable, bool isEnabled);

	static void DeleteDrawable(EntityId entityId);

	static void EnableDrawable(EntityId entityId);
	static void DisableDrawable(EntityId entityId);

	static void MoveActiveToPauseBuffer();
	static void RetrieveActiveFromPauseBuffer();

	void OnEventHappened(EventData& data) override
	{
		if (data.eventType == EventType::OnEntityDestroyedEvent)
		{
			Debug::Log("Deleting entity with id: " + std::to_string(data.id), typeid(*this).name());
			DeleteDrawable(data.id);
		}
		//TODO добавить обработку и новые методы включения и выключения отдельных методов
	}

private:

	//static void AddToDrawMap(EntityId entityId, DrawableComponent* drawable);

	static void AddToDrawMap(EntityId entityId, DrawableSpriteComponent* drawable);
	static void AddToDrawMap(EntityId entityId, DrawableTextComponent* drawable);

	static void DeleteFromDrawMap(EntityId entityId);

	static void UpdateDrawMap(EntityId entityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent* > pair)
	{
		auto itr = drawMapNew.find(-10000);
		if (pair.first != nullptr)
		{
			itr = drawMapNew.find(pair.first->GetDrawLayer());
		}
		else
		{
			itr = drawMapNew.find(pair.first->GetDrawLayer());
		}

		if (itr != drawMapNew.end())
		{
			auto pairFound = itr->second->find(entityId);
			if (pairFound != itr->second->end())
			{
				pairFound->second = pair;
			}
			else
			{
				Debug::LogWarning("Can't update drawable map\nDrawable with EntityId: " + std::to_string(entityId) + " not found", typeid(RenderSystem).name());
			}
		}
		else
		{
			Debug::LogWarning("Can't update drawable map", typeid(RenderSystem).name());
		}
	}


	//TODO заменить DrawableComponent на map с ComponentId и DrawableComponent
	//static std::multimap<DrawLayer, std::pair< EntityId, DrawableComponent*>> drawMap;
	static std::map<DrawLayer, std::map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>>*> drawMapNew;
	
	//TODO совместить все в один буфер
	//static std::multimap<DrawLayer, std::pair< EntityId, DrawableComponent*>> drawPauseBuffer;
	static std::map<DrawLayer, std::map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>>*> drawPauseBufferNew;

	//static std::unordered_map<EntityId, DrawableComponent*> enabledDrawables;
	//static std::unordered_map<EntityId, DrawableComponent*> disabledDrawables;
	//static std::unordered_map<EntityId, DrawableComponent*> pauseBuffer;


	//TODO переработать и разделить на отдельные контейнеры
	static std::unordered_map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>> enabledDrawablesNew;
	static std::unordered_map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>> disabledDrawablesNew;
	static std::unordered_map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>> pauseBufferNew;

	Window* window;
};

