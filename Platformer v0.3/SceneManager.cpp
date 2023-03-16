#include "SceneManager.h"

std::unordered_map<SceneId, IScene*> SceneManager::scenes = {};
IScene* SceneManager::activeScene = nullptr;