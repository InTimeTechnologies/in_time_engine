#include "HierarchyUI.h"

// Dependencies | std
#include <iostream>

// Dependencies | imgui_editor
#include "InspectorUI.h"

// class Hierarchy

// Object | private

// Functions
void it::HierarchyUI::processHiararchy(const Transform& transform) {
	std::vector<Transform*> children = transform.getChildren();
	std::string uiId = transform.getGameObject().name + "##" + std::to_string((unsigned long long)&transform.getGameObject());

	if (children.size() > 0) {
		if (ImGui::TreeNode(uiId.c_str())) {
			if (ImGui::IsItemClicked())
				InspectorUI::getSingleton()->setGameObject(&transform.getGameObject());

			for (Transform* child : children)
				processHiararchy(*child);

			ImGui::TreePop();
		}
	}
	else {
		ImGui::Selectable(uiId.c_str());
	}
	
	if (ImGui::IsItemClicked())
		InspectorUI::getSingleton()->setGameObject(&transform.getGameObject());

}

// Object | public
void it::HierarchyUI::update() {
	ImGui::Begin("Hierarchy");
	transforms.resize(GameObject::s_gameObjectList.size());
	{
		size_t i = 0ULL;
		for (GameObject* gameObject : GameObject::s_gameObjectList) {
			transforms[i++] = &gameObject->transform;
		}
	}

	for (size_t i = 0; i < transforms.size(); i++) {
		if (transforms[i]->getParent() != nullptr)
			continue;
		processHiararchy(*transforms[i]);
	}

	ImGui::End();
}
