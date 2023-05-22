#pragma once

#include "IScene.h"

#include "SceneManager.h"
#include "ObjectCollection.h"

#include "GameObject.h"
#include "UIButton.h"
#include "Input.h"

#include "Debug.h"

class PauseScene : public IScene
{
public:
	PauseScene(SharedContext context) : IScene(context) {}
	~PauseScene() {}

	void Initialize() override;

	void ProcessNotAwoken() override;

	void CaptureEvents() override;

	void EarlyUpdate() override;
	void Update() override;
	void LateUpdate() override;

	void UpdateUI() override;

private:
	UIButton* button;
};

