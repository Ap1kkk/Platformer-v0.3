#pragma once

class IAnimationState
{
public:
	virtual ~IAnimationState() {}

	virtual void Update() = 0;

	virtual void OnStateEnter() = 0;
	virtual void OnStateExit() = 0;
};

