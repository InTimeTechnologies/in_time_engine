#pragma once

// Dependencies | nlohmann
#include <nlohmann/json.hpp>

// Dependencies | in_time_engine
#include "Component.h"

namespace it {
	struct CustomComponentSerializer {
		virtual nlohmann::ordered_json operator()(const it::Component& component, nlohmann::ordered_json& json) = 0;
		virtual nlohmann::json operator()(const it::Component& component, nlohmann::json& json) = 0;
	};

	struct CustomComponentDeserializer {
		virtual Component* operator()(const nlohmann::ordered_json& json) = 0;
		virtual Component* operator()(const nlohmann::json& json) = 0;
	};
}
