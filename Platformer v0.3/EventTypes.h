#pragma once

//typedef std::string EventType;

enum class EventType
{
	OnComponentDestroyedEvent,
	OnComponentDisabledEvent,
	OnComponentEnabledEvent,

	OnEntityDestroyedEvent,
	OnEntityDiedEvent,
	OnEntityDisabledEvent,
	OnEntityEnabledEvent,

	OnLevelSwitchEvent,
	OnPlayerTurnedFaceEvent,

	OnSpriteDrawableEnabled,
	OnSpriteDrawableDisabled,

	OnTextDrawableEnabled,
	OnTextDrawableDisabled,

};