// Dependencies | std
#include <vector>

// Dependencies | in_time_engine
#include <in_time_engine/InTimeEngine.h>

namespace it {
	// Forward declarations
	class GameObject;
	class Transform;

	class HierarchyUI {
		// Friends
		friend class InTimeEditor;

		// Object
		private:
			// Properties
			bool isOpen{ true };

		public:
			// Properties
			std::vector<Transform*> transforms{};
			GameObject* selectedGameObject{ nullptr };

			// Functions
			void update(std::list<GameObject>& gameObjects);

		private:
			// Functions
			void processHiararchy(Transform* transform);
	};
}
