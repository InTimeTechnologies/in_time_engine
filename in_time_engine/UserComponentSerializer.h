#pragma once

// Dependencies | in_time_engine
#include <in_time_engine/CustomComponentSerializer.h>

struct UserComponentSerializer : public it::CustomComponentSerializer {
	nlohmann::ordered_json operator()(const it::Component& component, nlohmann::ordered_json& json) override;
	nlohmann::json operator()(const it::Component& component, nlohmann::json& json) override;
};

struct UserComponentDeserializer : public it::CustomComponentDeserializer {
	it::Component* operator()(const nlohmann::ordered_json& json) override;
	it::Component* operator()(const nlohmann::json& json) override;
};
