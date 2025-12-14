#pragma once

// Dependencies | std
#include <vector>

// Dependencies | in_time_engine
#include "Scene.h"

namespace it {
	class SceneManager {
		// Object
		public:
			// Properties
			std::vector<Scene> scenes{};

			// Functions
			Scene& createScene();
			void destroyScene(Scene& scene);
	};
}
