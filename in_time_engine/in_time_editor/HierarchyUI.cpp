#include "HierarchyUI.h"

// Dependencies | imgui
#include <imgui/imgui.h>

// Dependencies | imgui_editor
#include "InspectorUI.h"

namespace it {
	// class Hierarchy

	// Object | public
	void HierarchyUI::update(std::list<GameObject>& gameObjects) {
		// Return if this ui is not supposed to be open
		if (!isOpen)
			return;

		bool isVisible{ ImGui::Begin("Hierarchy", &isOpen) };
		if (isVisible) {
			// Resize transforms vector if needed
			if (gameObjects.size() != transforms.size())
				transforms.resize(gameObjects.size());

			// Copy all transforms to memory
			size_t index = 0ULL;
			for (GameObject& gameObject : gameObjects)
				transforms[index++] = &gameObject.transform;

			// Process hirarchy for each transform
			for (size_t i = 0; i < transforms.size(); i++) {
				if (transforms[i]->getParent() != nullptr)
					continue;
				processHiararchy(transforms[i]);
			}
		}
		
		ImGui::End();
	}

	// Object | private

	// Functions
	void HierarchyUI::processHiararchy(Transform* transform) {
		std::vector<Transform*> children{ transform->getChildren() };
		GameObject* go = transform->getGameObject();

		// Label##ID
		std::string uiId = go->name + "##" + std::to_string((unsigned long long)go);

		// Determine if this node is the currently selected one
		bool isSelected{ selectedGameObject == go };

		if (!children.empty()) 		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanFullWidth | (isSelected ? ImGuiTreeNodeFlags_Selected : 0);
			bool nodeOpen = ImGui::TreeNodeEx(uiId.c_str(), flags);

			// Handle selection
			if (ImGui::IsItemClicked() || (ImGui::IsItemFocused() && (ImGui::IsKeyPressed(ImGuiKey_Enter) || ImGui::IsKeyPressed(ImGuiKey_Space))))
				selectedGameObject = go;

			// Render children
			if (nodeOpen) {
				for (Transform* child : children)
					processHiararchy(child);
				ImGui::TreePop();
			}
		}
		else {
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth | (isSelected ? ImGuiTreeNodeFlags_Selected : 0);
			ImGui::TreeNodeEx(uiId.c_str(), flags);

			if (ImGui::IsItemClicked() || (ImGui::IsItemFocused() && (ImGui::IsKeyPressed(ImGuiKey_Enter) || ImGui::IsKeyPressed(ImGuiKey_Space))))
				selectedGameObject = go;
		}
	}
}
