#pragma once

#include "IScene.h"

#include "SceneManager.h"
#include "ObjectCollection.h"

#include "GameObject.h"
#include "UIButton.h"
#include "Input.h"

#include "Debug.h"

#include "ContinueGameButton.h"
#include "SaveAndExitButton.h"
#include "SaveGameButton.h"
#include "LoadAndContinueGameButton.h"

#include "PauseBackground.h"
#include "PauseLogo.h"

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
	ContinueGameButton* continueButton;
	SaveAndExitButton* saveAndExitButton;
	LoadAndContinueGameButton* loadAndContinueButton;
	SaveGameButton* saveButton;

	PauseBackground* pauseBackground;
	PauseLogo* pauseLogo;
};

