#include "SceneManager.h"

namespace it {
	Scene& SceneManager::createScene() {
		scenes.emplace_back();
		return scenes.back();
	}
	void SceneManager::destroyScene(Scene& scene) {
		auto it = std::find_if(scenes.begin(), scenes.end(),
			[&scene](const Scene& s) { return &s == &scene; });
		if (it != scenes.end()) {
			scenes.erase(it);
		}
	}
}