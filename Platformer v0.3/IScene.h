#pragma once

#include "DataTypes.h"
#include "Window.h"
#include "SharedContext.h"
#include "ObjectCollection.h"
#include "Debug.h"

#include "SaveManager.h"

class IScene
{
public:
	IScene(SharedContext sharedContext);
	virtual ~IScene();

	virtual void Initialize() = 0;
	
	virtual void ProcessNotAwoken() = 0;
	virtual void CaptureEvents() = 0;
	virtual void EarlyUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;

	virtual void UpdateUI() = 0;

	// Вызывается для специальной отрисовки того, что не попало в систему рендера
	virtual void Draw(Window* window) {}

	// Вызывается перед уничтожением сцены
	virtual void OnDestroy() {}
	// Вызывается перед перезагрузкой сцены
	virtual void OnReload() {}

	virtual void Reload();

	void Destroy(bool shouldClearMemory, bool clearNotBufferedOnly);

	inline const SceneId GetSceneId() const { return sceneId; }

protected:
	SceneId sceneId;
	SharedContext sharedContext;
	ObjectContext objectContext;

private:
	static SceneId sceneIdCounter;
};