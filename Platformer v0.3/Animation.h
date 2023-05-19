#pragma once

#include "DrawableSpriteComponent.h"
#include "Time.h"

#include "EventListener.h"
#include "PlayerTurnedFaceData.h"

class Animation : public EventListener
{
public:
	Animation(bool isCyclic, float evaluationDelay) : isCyclic(isCyclic), evaluationDelay(evaluationDelay), drawable(nullptr) 
	{
		SubscribeOnEvent(EventType::OnPlayerTurnedFaceEvent);
	}
	~Animation()
	{
		UnsubscribeFromEvent(EventType::OnPlayerTurnedFaceEvent);
	}

	void Evaluate()
	{
		thisFrameTime += Time::DeltaTime();
		if (thisFrameTime >= evaluationDelay)
		{
			SwitchFrame();
			thisFrameTime = 0.f;
		}
	}

	void AddFrame(sf::IntRect frameArea)
	{
		frames.push_back(frameArea);
		framesItr = 0;
	}

	void SetDrawableSpriteComponent(DrawableSpriteComponent* drawable) { this->drawable = drawable; }
	void SetIsCyclic(bool isCyclic) { this->isCyclic = isCyclic; }
	void SetEvaluationDelay(float evaluationDelay) { this->evaluationDelay = evaluationDelay; }

	void OnEventHappened(EventData& data) override
	{
		if (data.eventType == EventType::OnPlayerTurnedFaceEvent)
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

private:

	void SwitchFrame()
	{
		if (framesItr + 1 >= frames.size())
		{
			if (isCyclic)
			{
				framesItr = 0;
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
	float evaluationDelay = 0.f;
	float thisFrameTime = 0.f;

	DrawableSpriteComponent* drawable;

	std::vector<sf::IntRect> frames;
	unsigned framesItr;

	bool isHorizontallyMirrored;
	bool isVerticallyMirrored;
};

