#pragma once

#include "DrawableSpriteComponent.h"
#include "Time.h"

#include "EventListener.h"
#include "PlayerTurnedFaceData.h"

#include "IAnimationState.h"

class Animation : public EventListener
{
public:
	Animation(bool isCyclic, float evaluationDelay, EntityId ownerId) : isCyclic(isCyclic), evaluationDelay(evaluationDelay), ownerId(ownerId), drawable(nullptr)
	{
		SubscribeOnEvent(EventType::OnPlayerTurnedFaceEvent);
		SubscribeOnEvent(EventType::OnEnemyTurnedFace);
	}
	~Animation()
	{
		UnsubscribeFromEvent(EventType::OnPlayerTurnedFaceEvent);
		UnsubscribeFromEvent(EventType::OnEnemyTurnedFace);
	}

	void Evaluate()
	{
		thisFrameTime += Time::DeltaTime();
		if (thisFrameTime >= evaluationDelay)
		{
			if (!isFinished)
			{
				SwitchFrame();
				thisFrameTime = 0.f;
			}
		}
	}

	void AddFrame(sf::IntRect frameArea)
	{
		frames.push_back(frameArea);
		framesItr = 0;
	}

	void SetIAnimStatePtr(IAnimationState* animState) 
	{ 
		this->animState = animState;
		animState->SetOwnerId(ownerId);
	}

	void SetDrawableSpriteComponent(DrawableSpriteComponent* drawable) { this->drawable = drawable; }
	void SetIsCyclic(bool isCyclic) { this->isCyclic = isCyclic; }
	void SetEvaluationDelay(float evaluationDelay) { this->evaluationDelay = evaluationDelay; }

	void OnEventHappened(EventData& data) override
	{
		if (data.eventType == EventType::OnPlayerTurnedFaceEvent)
		{
			if (data.id == ownerId)
			{
				auto userData = static_cast<PlayerTurnedFaceData*>(data.userData);
				if (userData->direction == FaceDirection::Left && !isHorizontallyMirrored)
				{
					isHorizontallyMirrored = !isHorizontallyMirrored;
				}
				else if (userData->direction == FaceDirection::Right && isHorizontallyMirrored)
				{
					isHorizontallyMirrored = !isHorizontallyMirrored;
				}
			}
		}

		if (data.eventType == EventType::OnEnemyTurnedFace)
		{
			if (data.id == ownerId)
			{
				isHorizontallyMirrored = !isHorizontallyMirrored;
			}
		}
	}

private:

	void SwitchFrame()
	{
		if (framesItr + 1 >= frames.size())
		{
			framesItr = 0;
			if (!isCyclic)
			{
				isFinished = true;
				animState->OnNonCyclicAnimEnded();
			}
		}
		else
		{
			++framesItr;
		}

		auto frameRect = frames[framesItr];
		if (isHorizontallyMirrored)
		{
			frameRect.left += frameRect.width;
			frameRect.width *= -1;
		}
		if (isVerticallyMirrored)
		{
			frameRect.top += frameRect.height;
			frameRect.height *= -1;
		}
		drawable->UpdateTextureRect(frameRect);
	}

	bool isCyclic;
	bool isFinished = false;
	float evaluationDelay = 0.f;
	float thisFrameTime = 0.f;

	DrawableSpriteComponent* drawable;

	std::vector<sf::IntRect> frames;
	unsigned framesItr;

	bool isHorizontallyMirrored;
	bool isVerticallyMirrored;

	IAnimationState* animState;
	EntityId ownerId;
};

