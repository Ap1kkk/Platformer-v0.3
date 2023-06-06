#pragma once

#include "AnimationTypes.h"
#include "IAnimator.h"
#include "IAnimationState.h"
#include "Animation.h"

class AnimationState : public IAnimationState
{
public:
	AnimationState(AnimationType type) : type(type) {}
	virtual ~AnimationState() 
	{
		delete animation;
	}

	AnimationType GetAnimationType() { return type; }

	void SetIAnimator(IAnimator* animator) { this->animator = animator; }
	void SetAnimation(Animation* animation) { this->animation = animation; }

	void ChangeState(AnimationType nextType) { animator->ChangeState(nextType); }

	void Update() override { animation->Evaluate(); }

	void RefreshNonCyclicAnim() { animation->RefreshNonCyclicAnim(); }

private:
	AnimationType type;
	IAnimator* animator;
	Animation* animation;
};

