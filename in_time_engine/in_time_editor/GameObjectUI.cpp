#include "GameObjectUI.h"

// Dependencies | imgui
#include <imgui/imgui.h>

namespace it {
	void GameObjectUI::update(InTimeEngine& inTimeEngine) {
		if (!isOpen)
			return;

		bool isVisible{ ImGui::Begin("Game Object UI", &isOpen) };
		if (isVisible) {
            // id
            ImGui::InputInt("ID", &gameObjectId);

            // name
            ImGui::InputText("Name", gameObjectName, IM_ARRAYSIZE(gameObjectName));

            // Create button
            if (ImGui::Button("Create")) {
                inTimeEngine.gameObjectManager.createGameObject(gameObjectId, gameObjectName);
				isOpen = false;
            }
		}
		ImGui::End();
	}
}
