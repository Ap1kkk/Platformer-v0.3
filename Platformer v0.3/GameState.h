#pragma once

#include "DataTypes.h"

class GameState
{
public:
	GameState() {}

	virtual void EnterState() = 0;
	virtual void Update() = 0;
	virtual void LeaveState() = 0;

	//TODO можно переместить в конструктор
	void SetStateType(GameStateType stateType) { this->stateType = stateType; }
	GameStateType GetStateType() { return stateType; }

private:
	GameStateType stateType;
};