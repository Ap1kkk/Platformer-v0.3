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
		for (auto& item : drawMap)
		{
			delete item.second;
		}
	}

	void SubscribeOnEvents()
	{
		//SubscribeOnEvent(EventType::OnEntityDestroyedEvent);

		SubscribeOnEvent(EventType::OnSpriteDrawableEnabled);
		SubscribeOnEvent(EventType::OnSpriteDrawableDisabled);
		SubscribeOnEvent(EventType::OnSpriteDrawableDestroyed);
		SubscribeOnEvent(EventType::OnTextDrawableEnabled);
		SubscribeOnEvent(EventType::OnTextDrawableDisabled);
		SubscribeOnEvent(EventType::OnTextDrawableDestroyed);
	}

	void Draw();

	static void AddDrawable(DrawableSpriteComponent* drawable);
	static void AddDrawable(DrawableTextComponent* drawable);

	static void DeleteDrawable(DrawableSpriteComponent* drawable);
	static void DeleteDrawable(DrawableTextComponent* drawable);

	static void MoveActiveToPauseBuffer();
	static void RetrieveActiveFromPauseBuffer();

	void OnEventHappened(EventData& data) override
	{
		switch (data.eventType)
		{
			case EventType::OnSpriteDrawableDestroyed:
			{
				Debug::LogWarning("Deleting Sprite Drawable with ownerId: " + std::to_string(data.id), typeid(*this).name());
				auto userData = static_cast<ComponentUserData*>(data.userData);
				DeleteDrawable(static_cast<DrawableSpriteComponent*>(userData->component)); 
				break;
			}
			case EventType::OnTextDrawableDestroyed:
			{
				Debug::LogWarning("Deleting Text Drawable with ownerId: " + std::to_string(data.id), typeid(*this).name());
				auto userData = static_cast<ComponentUserData*>(data.userData);
				DeleteDrawable(static_cast<DrawableTextComponent*>(userData->component));
				break;
			}
			case EventType::OnSpriteDrawableEnabled:
			{
				auto userData = static_cast<ComponentUserData*>(data.userData);
				AddDrawable(static_cast<DrawableSpriteComponent*>(userData->component));
				break;
			}
			case EventType::OnSpriteDrawableDisabled:
			{
				auto userData = static_cast<ComponentUserData*>(data.userData);
				DeleteDrawable(static_cast<DrawableSpriteComponent*>(userData->component));
				break;
			}
			case EventType::OnTextDrawableEnabled:
			{
				auto userData = static_cast<ComponentUserData*>(data.userData);
				AddDrawable(static_cast<DrawableTextComponent*>(userData->component));
				break;
			}
			case EventType::OnTextDrawableDisabled:
			{
				auto userData = static_cast<ComponentUserData*>(data.userData);
				DeleteDrawable(static_cast<DrawableTextComponent*>(userData->component));
				break;
			}
		}
	}

private:

	static void AddToDrawMap(DrawableSpriteComponent* drawable);
	static void AddToDrawMap(DrawableTextComponent* drawable);

	static void DeleteFromDrawMap(DrawableSpriteComponent* drawable);
	static void DeleteFromDrawMap(DrawableTextComponent* drawable);

	static std::map<DrawLayer, std::map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>>*> drawMap;
	static std::map<DrawLayer, std::map<EntityId, std::pair<DrawableSpriteComponent*, DrawableTextComponent*>>*> drawPauseBuffer;

	Window* window;
};

