#pragma once

#include "DataTypes.h"
#include "Window.h"

class ISceneManager
{
public:
	virtual void Initialize(SceneId startSceneId) = 0;

	virtual void ProcessNotAwoken() = 0;
	virtual void CaptureEvents() = 0;
	virtual void EarlyUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void UpdateUI() = 0;

	virtual void Draw(Window* window) = 0;

};
