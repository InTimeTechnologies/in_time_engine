#pragma once

// Dependencies | std
#include <cassert>

// Dependencies | in_time_engine
#include "InTimeEngine.h"

namespace it {
	inline void destroy(GameObject& gameObject) {
		InTimeEngine* engine = InTimeEngine::s_getSingleton();
		assert(engine != nullptr && "InTimeEngine singleton == nullptr");
		engine->gameObjectManager.destroy(gameObject);
	}
	inline void destroyImmediately(GameObject& gameObject) {
		InTimeEngine* engine = InTimeEngine::s_getSingleton();
		assert(engine != nullptr && "InTimeEngine singleton == nullptr");
		engine->gameObjectManager.destroyImmediately(gameObject);
	}
	inline void destroy(Component& component) {
		InTimeEngine* engine = InTimeEngine::s_getSingleton();
		assert(engine != nullptr && "InTimeEngine singleton == nullptr");
		engine->gameObjectManager.componentManager.destroy(component);
	}
	inline void destroyImmediately(Component& component) {
		InTimeEngine* engine = InTimeEngine::s_getSingleton();
		assert(engine != nullptr && "InTimeEngine singleton == nullptr");
		engine->gameObjectManager.componentManager.destroyImmediately(component);
	}
}
