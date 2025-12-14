#include "UserComponentSerializer.h"

// struct UserComponentSerializer

// Object | public

// Functions
nlohmann::ordered_json UserComponentSerializer::operator()(const it::Component& component, nlohmann::ordered_json& json) {
	return nlohmann::ordered_json::object();
}
nlohmann::json UserComponentSerializer::operator()(const it::Component& component, nlohmann::json& json) {
	return nlohmann::json::object();
}

// struct UserComponentSerializer

// Object | public

// Functions
it::Component* UserComponentDeserializer::operator()(const nlohmann::ordered_json& json) {
	return nullptr;
}
it::Component* UserComponentDeserializer::operator()(const nlohmann::json& json) {
	return nullptr;
}
