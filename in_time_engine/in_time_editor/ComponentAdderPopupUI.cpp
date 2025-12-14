#include "ComponentAdderPopupUI.h"

// Dependencies | std
#include <string>

// Dependencies | imgui
#include <imgui/imgui.h>

namespace it {
	// class ComponentAdderPopupUI

	// Object | public

	// Functions
	void ComponentAdderPopupUI::update(GameObject& gameObject) {
		InTimeEngine* inTimeEngine = InTimeEngine::s_getSingleton();
		if (inTimeEngine == nullptr)
			return;

		std::string popupName = "Add Component Popup";
		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup(popupName.c_str());

		ComponentRegistry& componentRegistry = inTimeEngine->componentRegistry;
		const std::vector<ComponentRegistry::Entry>& componentEntries = componentRegistry.getEntries();

		// Begin popup
		if (ImGui::BeginPopup(popupName.c_str())) {
			ImGui::Text("Select a component to add:");

			for (size_t i = 0; i < componentEntries.size(); i++) {
				if (ImGui::Selectable(componentEntries[i].name.c_str())) {
					gameObject.addComponent(componentEntries[i].constructor());
					ImGui::CloseCurrentPopup();
					break;
				}
			}

			ImGui::EndPopup();
		}
	}
}