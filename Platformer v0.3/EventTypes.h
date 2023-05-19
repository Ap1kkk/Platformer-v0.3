#pragma once

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
	OnSpriteDrawableDestroyed,

	OnTextDrawableEnabled,
	OnTextDrawableDisabled,
	OnTextDrawableDestroyed,

	OnPlayerStartedRunning,
	OnPlayerStoppedRunning,

	OnPlayerStartedSprinting,
	OnPlayerStoppedSprinting,

	OnPlayerJumpRaise,
	OnPlayerJumpFall,

	OnPlayerLanded,
	OnJumpSensorLeftCollisions
};