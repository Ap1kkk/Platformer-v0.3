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

	OnPlayerAttack,

	OnPlayerLanded,
	OnJumpSensorLeftCollisions,

	OnEnemyStartedRunning,
	OnEnemyStoppedRunning,
	OnEnemyAttacked,
	OnEnemyTurnedFace,

	OnGameSaved,

	OnPlayerDataRequest,
	OnPlayerDataCallback,

	OnEnemyDamaged,

	OnPlayerMovementRequest,
	OnPlayerMovementCallback,

	OnEnemyMovementRequest,
	OnEnemyMovementCallback,
};