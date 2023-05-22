#pragma once

#include "IAnimationState.h"
#include "AnimationTypes.h"


class IAnimator
{
public:
	virtual ~IAnimator() {}
	virtual void ChangeState(AnimationType nextType) = 0;
};

