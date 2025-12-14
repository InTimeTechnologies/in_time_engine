#include "EngineTimeUI.h"

// Depdendencies | std
#include <string>

// Dependencies | imgui
#include <imgui/imgui.h>

namespace it {
    // class EngineTimeUI

    // Object | public

    // Functions
    void EngineTimeUI::update(InTimeEngine& inTimeEngine) {
        if (!isOpen)
            return;

        const char* uuid = "Engine Time";
        if (ImGui::Begin(uuid, &isOpen)) {
            // Real time
            ImGui::SeparatorText("Real Time");
            renderTime(inTimeEngine.realTime);

            // Time
            ImGui::SeparatorText("Core Time");
            ImGui::PushID("Core Time Values");
            renderTime(inTimeEngine.coreTime);
            ImGui::PopID();

            // Physics time
            ImGui::SeparatorText("Fixed Time");
            ImGui::PushID("Fixed Time Values");
            renderFixedTime(inTimeEngine.fixedTime);
            ImGui::PopID();
        }
        ImGui::End();
    }

    // Object | private

    // Functions
    double EngineTimeUI::toSeconds(std::chrono::nanoseconds nanoseconds) {
        return std::chrono::duration<double>(nanoseconds).count();
    }
    void EngineTimeUI::renderTime(RealTime& realTime) {
        double startTimeSec = toSeconds(realTime.getStartTime().time_since_epoch());
        double lastTickTimeSec = toSeconds(realTime.getLastTickTime().time_since_epoch());
        double runTimeSec = toSeconds(realTime.getRunTime());
        double deltaTimeSec = toSeconds(realTime.getDeltaTime());
        double nowSec = toSeconds(realTime.now().time_since_epoch());

        ImGui::InputDouble("Start Time (sec)", &startTimeSec, 0.0, 0.0, "%.9f", ImGuiInputTextFlags_ReadOnly);
        ImGui::InputDouble("Last Tick (sec)", &lastTickTimeSec, 0.0, 0.0, "%.9f", ImGuiInputTextFlags_ReadOnly);
        ImGui::InputDouble("Run Time (sec)", &runTimeSec, 0.0, 0.0, "%.6f", ImGuiInputTextFlags_ReadOnly);
        ImGui::InputDouble("Delta Time (sec)", &deltaTimeSec, 0.0, 0.0, "%.9f", ImGuiInputTextFlags_ReadOnly);
        ImGui::InputDouble("Now (sec)", &nowSec, 0.0, 0.0, "%.9f", ImGuiInputTextFlags_ReadOnly);
    }
    void EngineTimeUI::renderTime(Time& time) {
        double timeSec = time.getTimeD();
        double deltaSec = time.getDeltaTimeD();
        double scaledTimeSec = time.getScaledTimeD();
        double scaledDeltaSec = time.getScaledDeltaTimeD();

        // Show time values (read-only)
        ImGui::InputDouble("Time (sec)", &timeSec, 0, 0, "%.6f", ImGuiInputTextFlags_ReadOnly);
        ImGui::InputDouble("Delta Time (sec)", &deltaSec, 0, 0, "%.9f", ImGuiInputTextFlags_ReadOnly);

        ImGui::InputDouble("Scaled Time (sec)", &scaledTimeSec, 0, 0, "%.6f", ImGuiInputTextFlags_ReadOnly);
        ImGui::InputDouble("Scaled Delta Time (sec)", &scaledDeltaSec, 0, 0, "%.9f", ImGuiInputTextFlags_ReadOnly);

        ImGui::Spacing();

        // Editable fields
        ImGui::InputDouble("Time Scale", &time.scale, 0.01, 0.1, "%.3f");

        bool fixed = time.fixed;
        if (ImGui::Checkbox("Fixed Timestep", &fixed)) {
            time.fixed = fixed;
        }

        // Convert tickRate to seconds
        double tickRateSec = toSeconds(time.tickRate);
        ImGui::InputDouble("Tick Rate (sec)", &tickRateSec, 0.000001, 0.0001, "%.9f");

        // Write back tickRate if changed
        time.tickRate = std::chrono::nanoseconds((long long)(tickRateSec * 1e9));

        ImGui::Spacing();
        ImGui::Spacing();
    }
    void EngineTimeUI::renderFixedTime(FixedTime& fixedTime) {
        double timeSec = fixedTime.getTimeD();
        double deltaSec = fixedTime.getDeltaTimeD();
        double scaledTimeSec = fixedTime.getScaledTimeD();
        double scaledDeltaSec = fixedTime.getScaledDeltaTimeD();

        // Show time values (read-only)
        ImGui::InputDouble("Time (sec)", &timeSec, 0, 0, "%.6f", ImGuiInputTextFlags_ReadOnly);
        ImGui::InputDouble("Delta Time (sec)", &deltaSec, 0, 0, "%.9f", ImGuiInputTextFlags_ReadOnly);

        ImGui::InputDouble("Scaled Time (sec)", &scaledTimeSec, 0, 0, "%.6f", ImGuiInputTextFlags_ReadOnly);
        ImGui::InputDouble("Scaled Delta Time (sec)", &scaledDeltaSec, 0, 0, "%.9f", ImGuiInputTextFlags_ReadOnly);

        ImGui::Spacing();

        // Editable fields
        ImGui::InputDouble("Time Scale", &fixedTime.scale, 0.01, 0.1, "%.3f");

        // Convert tickRate to seconds
        double tickRateSec = toSeconds(fixedTime.tickRate);
        ImGui::InputDouble("Tick Rate (sec)", &tickRateSec, 0.000001, 0.0001, "%.9f");

        // Write back tickRate if changed
        fixedTime.tickRate = std::chrono::nanoseconds((long long)(tickRateSec * 1e9));

        ImGui::Spacing();
        ImGui::Spacing();
    }
}
