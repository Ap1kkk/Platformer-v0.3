#pragma once

class IGameStateMachine
{
public:
	virtual void Create() = 0;
	virtual void Initialize() = 0;
	virtual void Run() = 0;
	virtual void Pause() = 0;
	virtual void Contintue() = 0;
};

