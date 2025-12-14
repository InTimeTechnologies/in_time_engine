#pragma once

// Dependencies | std
#include <string>

// Dependencies | nlohmann
#include <nlohmann/json.hpp>

// Dependencies | in_time_engine
#include "InTimeEngine.h"

namespace nlohmann {	
	// json to_json functions
	inline void to_json(json& j, const glm::vec2& vec2) {
		j = json::array({ vec2[0], vec2[1] });
	}
	inline void to_json(json& j, const glm::vec3& vec3) {
		j = json::array({ vec3[0], vec3[1], vec3[2] });
	}
	inline void to_json(json& j, const glm::vec4& vec4) {
		j = json::array({ vec4[0], vec4[1], vec4[2], vec4[3] });
	}
	inline void to_json(json& j, const glm::quat& quat) {
		j = json::array({ quat[0], quat[1], quat[2], quat[3] });
	}
	inline void to_json(json& j, const glm::mat2& mat2) {
		j = json::array();
		for (size_t i = 0; i < 4; i++)
			j.push_back(mat2[i]);
	}
	inline void to_json(json& j, const glm::mat3& mat3) {
		j = json::array();
		for (size_t i = 0; i < 9; i++)
			j.push_back(mat3[i]);
	}
	inline void to_json(json& j, const glm::mat4& mat4) {
		j = json::array();
		for (size_t i = 0; i < 12; i++)
			j.push_back(mat4[i]);
	}

	inline void to_json(json& j, const b2Vec2& vec2) {
		j = json::array({ vec2.x, vec2.y });
	}
	inline void to_json(json& j, const b2Rot& rot) {
		j = {
			{ "c", rot.c },
			{ "s", rot.s }
		};
	}
	inline void to_json(json& j, const b2BodyDef & bodyDef) {
		j = {
			{ "type", bodyDef.type },
			{ "position", bodyDef.position },
			{ "rotation", bodyDef.rotation },
			{ "linearVelocity", bodyDef.linearVelocity },
			{ "angularVelocity", bodyDef.angularVelocity },
			{ "linearDamping", bodyDef.linearDamping },
			{ "angularDamping", bodyDef.angularDamping },
			{ "gravityScale", bodyDef.gravityScale },
			{ "sleepThreshold", bodyDef.sleepThreshold },
			{ "name", bodyDef.name },
			{ "enableSleep", bodyDef.enableSleep },
			{ "isAwake", bodyDef.isAwake },
			//{ "fixedRotation", bodyDef.fixedRotation },
			{ "isBullet", bodyDef.isBullet },
			{ "isEnabled", bodyDef.isEnabled }
		};
	}
	inline void to_json(json& j, const b2BodyId id) {
		j = {
			j["type"] = b2Body_GetType(id),
			j["position"] = b2Body_GetPosition(id),
			j["rotation"] = b2Body_GetRotation(id),
			j["linearVelocity"] = b2Body_GetLinearVelocity(id),
			j["angularVelocity"] = b2Body_GetAngularVelocity(id),
			j["linearDamping"] = b2Body_GetLinearDamping(id),
			j["angularDamping"] = b2Body_GetAngularDamping(id),
			j["gravityScale"] = b2Body_GetGravityScale(id),
			j["sleepThreshold"] = b2Body_GetSleepThreshold(id),
			j["name"] = b2Body_GetName(id),
			j["enableSleep"] = b2Body_IsSleepEnabled(id),
			j["isAwake"] = b2Body_IsAwake(id),
			//j["fixedRotation"] = b2Body_IsFixedRotation(id),
			j["isBullet"] = b2Body_IsBullet(id),
			j["isEnabled"] = b2Body_IsEnabled(id)
		};
	}
	inline void to_json(json& j, const b2SurfaceMaterial& material) {
		j = {
			{ "friction", material.friction },
			{ "restitution", material.restitution },
			{ "rollingResistance", material.rollingResistance },
			{ "tangentSpeed", material.tangentSpeed },
			{ "userMaterialId", material.userMaterialId },
			{ "customColor", material.customColor }
		};
	}
	inline void to_json(json& j, const b2Filter& filter) {
		j = {
			{ "categoryBits", filter.categoryBits },
			{ "maskBits", filter.maskBits },
			{ "groupIndex", filter.groupIndex }
		};
	}
	inline void to_json(json& j, const b2ShapeDef& shapeDef) {
		j = {
			{ "material", shapeDef.material },
			{ "density", shapeDef.density },
			{ "filter", shapeDef.filter },
			{ "isSensor", shapeDef.isSensor },
			{ "enableSensorEvents", shapeDef.enableSensorEvents },
			{ "enableContactEvents", shapeDef.enableContactEvents },
			{ "enableHitEvents", shapeDef.enableHitEvents },
			{ "enablePreSolveEvents", shapeDef.enablePreSolveEvents },
			{ "invokeContactCreation", shapeDef.invokeContactCreation },
			{ "updateBodyMass", shapeDef.updateBodyMass }
		};
	}
	inline void to_json(json& j, const b2Polygon& polygon) {
		j = {
			{ "vertices", json::array() },
			{ "normals", json::array() },
			{ "centroid", polygon.centroid },
			{ "radius", polygon.radius },
			{ "count", polygon.count }
		};
		for (size_t i = 0; i < polygon.count; i++) {
			j["vertices"].push_back(polygon.vertices[i]);
			j["normals"].push_back(polygon.normals[i]);
		}
	}
	inline void to_json(json& j, const b2ShapeId id) {
		j = {
			//{ "material", b2Shape_GetMaterial(id) },
			{ "density", b2Shape_GetDensity(id) },
			{ "filter", b2Shape_GetFilter(id) },
			{ "isSensor", b2Shape_IsSensor(id) },
			{ "enableSensorEvents", b2Shape_AreSensorEventsEnabled(id) },
			{ "enableContactEvents", b2Shape_AreContactEventsEnabled(id) },
			{ "enableHitEvents", b2Shape_AreHitEventsEnabled(id) },
			{ "enablePreSolveEvents", b2Shape_ArePreSolveEventsEnabled(id) }
			//{ "invokeContactCreation", b2Shape_creation(id) }, // This does not exist in the API
			//{ "updateBodyMass", b2Shape_bodyMass(id) } // This does not exist in the API
		};
	}

	inline void to_json(json& j, const it::GrayImage& grayImage) {
		j = {
			{ "path", grayImage.getPath().string().c_str() }
		};
	}
	inline void to_json(json& j, const it::GrayAlphaImage& grayAlphaImage) {
		j = {
			{ "path", grayAlphaImage.getPath().string().c_str() }
		};
	}
	inline void to_json(json& j, const it::RGBImage& rgbImage) {
		j = {
			{ "path", rgbImage.getPath().string().c_str() }
		};
	}
	inline void to_json(json& j, const it::RGBAImage& rgbaImage) {
		j = {
			{ "path", rgbaImage.getPath().string().c_str() }
		};
	}
	inline void to_json(json& j, const it::Transform& transform) {
		j = {
			{ "position", transform.position },
			{ "orientation", transform.orientation },
			{ "scale", transform.scale }
		};
	}
	inline void to_json(json& j, const it::GameObject& gameObject) {
		j = {
			{ "id", gameObject.id },
			{ "name", gameObject.name },
			{ "transform", gameObject.transform }
		};
	}
	inline void to_json(json& j, const it::Time& time) {
		j = {
			{ "tempTime", time.getTime().count() },
			{ "tempDeltaTime", time.getDeltaTime().count() },
			{ "tempScaledTime", time.getScaledTime().count() },
			{ "tempScaledDeltaTime", time.getScaledDeltaTime().count() },
			{ "tempScale", time.scale },
			{ "tempFixed", time.fixed },
			{ "tickRate", time.tickRate.count() }
		};
	}

	// json from_json functions
	inline void from_json(const json& j, glm::vec2& vec2) {
		j.at(0).get_to(vec2[0]);
		j.at(1).get_to(vec2[1]);
	}
	inline void from_json(const json& j, glm::vec3& vec3) {
		j.at(0).get_to(vec3[0]);
		j.at(1).get_to(vec3[1]);
		j.at(2).get_to(vec3[2]);
	}
	inline void from_json(const json& j, glm::vec4& vec4) {
		j.at(0).get_to(vec4[0]);
		j.at(1).get_to(vec4[1]);
		j.at(2).get_to(vec4[2]);
		j.at(3).get_to(vec4[3]);
	}
	inline void from_json(const json& j, glm::quat& quat) {
		j.at(0).get_to(quat[0]);
		j.at(1).get_to(quat[1]);
		j.at(2).get_to(quat[2]);
		j.at(3).get_to(quat[3]);
	}
	inline void from_json(const json& j, glm::mat2& mat2) {
		float* mat2Array = reinterpret_cast<float*>(&mat2);
		for (size_t i = 0ULL; i < 4; i++)
			j.at(i).get_to(mat2Array[i]);
	}
	inline void from_json(const json& j, glm::mat3& mat3) {
		float* mat3Array = reinterpret_cast<float*>(&mat3);
		for (size_t i = 0ULL; i < 9; i++)
			j.at(i).get_to(mat3Array[i]);
	}
	inline void from_json(const json& j, glm::mat4& mat4) {
		float* mat4Array = reinterpret_cast<float*>(&mat4);
		for (size_t i = 0ULL; i < 16; i++)
			j.at(i).get_to(mat4Array[i]);
	}

	inline void from_json(const json& j, b2Vec2& vec2) {
		j.at(0).get_to(vec2.x);
		j.at(1).get_to(vec2.y);
	}
	inline void from_json(const json& j, b2Rot& rotation) {
		j.at("c").get_to(rotation.c);
		j.at("s").get_to(rotation.s);
	}
	inline void from_json(const json& j, b2BodyDef& bodyDef) {
		j.at("type").get_to(bodyDef.type);
		j.at("position").get_to(bodyDef.position);
		j.at("rotation").get_to(bodyDef.rotation);
		j.at("linearVelocity").get_to(bodyDef.linearVelocity);
		j.at("angularVelocity").get_to(bodyDef.angularVelocity);
		j.at("linearDamping").get_to(bodyDef.linearDamping);
		j.at("angularDamping").get_to(bodyDef.angularDamping);
		j.at("gravityScale").get_to(bodyDef.gravityScale);
		j.at("sleepThreshold").get_to(bodyDef.sleepThreshold);
		std::string name;
		j.at("name").get_to(name);
		bodyDef.name = name.c_str();
		j.at("enableSleep").get_to(bodyDef.enableSleep);
		j.at("isAwake").get_to(bodyDef.isAwake);
		//j.at("fixedRotation").get_to(bodyDef.fixedRotation);
		j.at("isBullet").get_to(bodyDef.isBullet);
		j.at("isEnabled").get_to(bodyDef.isEnabled);
	}
	inline void from_json(const json& j, b2BodyId id) {
		b2BodyType type;
		b2Vec2 position;
		b2Rot rotation;
		b2Vec2 linearVelocity;
		float angularVelocity;
		float linearDamping;
		float angularDamping;
		float gravityScale;
		float sleepThreshold;
		std::string name;
		bool enableSleep;
		bool isAwake;
		bool fixedRotation;
		bool isBullet;
		bool isEnabled;

		j.at("type").get_to(type);
		j.at("position").get_to(position);
		j.at("rotation").get_to(rotation);
		j.at("linearVelocity").get_to(linearVelocity);
		j.at("angularVelocity").get_to(angularVelocity);
		j.at("linearDamping").get_to(linearDamping);
		j.at("angularDamping").get_to(angularDamping);
		j.at("gravityScale").get_to(gravityScale);
		j.at("sleepThreshold").get_to(sleepThreshold);
		j.at("name").get_to(name);
		j.at("enableSleep").get_to(enableSleep);
		j.at("isAwake").get_to(isAwake);
		j.at("fixedRotation").get_to(fixedRotation);
		j.at("isBullet").get_to(isBullet);
		j.at("isEnabled").get_to(isEnabled);

		b2Body_SetType(id, type);
		b2Body_SetTransform(id, position, rotation);
		b2Body_SetLinearVelocity(id, linearVelocity);
		b2Body_SetAngularVelocity(id, angularVelocity);
		b2Body_SetLinearDamping(id, linearDamping);
		b2Body_SetAngularDamping(id, angularDamping);
		b2Body_SetGravityScale(id, gravityScale);
		b2Body_SetSleepThreshold(id, sleepThreshold);
		b2Body_SetName(id, name.c_str());
		b2Body_EnableSleep(id, enableSleep);
		b2Body_SetAwake(id, isAwake);
		//b2Body_SetFixedRotation(id, fixedRotation);
		b2Body_SetBullet(id, isBullet);
		if (isEnabled)
			b2Body_Enable(id);
		else
			b2Body_Disable(id);
	}
	inline void from_json(const json& j, b2SurfaceMaterial& material) {
		j.at("friction").get_to(material.friction);
		j.at("restitution").get_to(material.restitution);
		j.at("rollingResistance").get_to(material.rollingResistance);
		j.at("tangentSpeed").get_to(material.tangentSpeed);
		j.at("userMaterialId").get_to(material.userMaterialId);
		j.at("customColor").get_to(material.customColor);
	}
	inline void from_json(const json& j, b2Filter& filter) {
		j.at("categoryBits").get_to(filter.categoryBits);
		j.at("maskBits").get_to(filter.maskBits);
		j.at("groupIndex").get_to(filter.groupIndex);
	}
	inline void from_json(const json& j, b2ShapeDef& shapeDef) {
		j.at("material").get_to(shapeDef.material);
		j.at("density").get_to(shapeDef.density);
		j.at("filter").get_to(shapeDef.filter);
		j.at("isSensor").get_to(shapeDef.isSensor);
		j.at("enableSensorEvents").get_to(shapeDef.enableSensorEvents);
		j.at("enableContactEvents").get_to(shapeDef.enableContactEvents);
		j.at("enableHitEvents").get_to(shapeDef.enableHitEvents);
		j.at("enablePreSolveEvents").get_to(shapeDef.enablePreSolveEvents);
		j.at("invokeContactCreation").get_to(shapeDef.invokeContactCreation);
		j.at("updateBodyMass").get_to(shapeDef.updateBodyMass);
	}
	inline void from_json(const json& j, b2Polygon& polygon) {
		j.at("centroid").get_to(polygon.centroid);
		j.at("radius").get_to(polygon.radius);
		j.at("count").get_to(polygon.count);
		for (size_t i = 0; i < polygon.count; i++) {
			j.at("vertices").at(i).get_to(polygon.vertices[i]);
			j.at("normals").at(i).get_to(polygon.normals[i]);
		}
	}
	inline void from_json(const json& j, b2ShapeId id) {
		b2Filter filter;
		float density;
		bool isSensor;
		bool enableSensorEvents;
		bool enableContactEvents;
		bool enableHitEvents;
		bool enablePreSolveEvents;

		j.at("density").get_to(density);
		j.at("filter").get_to(filter);
		j.at("isSensor").get_to(isSensor);
		j.at("enableSensorEvents").get_to(enableSensorEvents);
		j.at("enableContactEvents").get_to(enableContactEvents);
		j.at("enableHitEvents").get_to(enableHitEvents);
		j.at("enablePreSolveEvents").get_to(enablePreSolveEvents);

		b2Shape_SetDensity(id, density, true);
		b2Shape_SetFilter(id, filter);
		b2Shape_EnableSensorEvents(id, enableSensorEvents);
		b2Shape_EnableContactEvents(id, enableContactEvents);
		b2Shape_EnableHitEvents(id, enableHitEvents);
		b2Shape_EnablePreSolveEvents(id, enablePreSolveEvents);
	}

	inline void from_json(const json& j, it::GrayImage& grayImage) {
		std::string path;
		j.at("path").get_to(path);
		grayImage.load(path);
	}
	inline void from_json(const json& j, it::GrayAlphaImage& grayAlphaImage) {
		std::string path;
		j.at("path").get_to(path);
		grayAlphaImage.load(path);
	}
	inline void from_json(const json& j, it::RGBImage& rgbImage) {
		std::string path;
		j.at("path").get_to(path);
		rgbImage.load(path);
	}
	inline void from_json(const json& j, it::RGBAImage& rgbaImage) {
		std::string path;
		j.at("path").get_to(path);
		rgbaImage.load(path);
	}
	inline void from_json(const json& j, it::Transform& transform) {
		j.at("position").get_to(transform.position);
		j.at("orientation").get_to(transform.orientation);
		j.at("scale").get_to(transform.scale);
	}
	inline void from_json(const json& j, it::GameObject& gameObject) {
		j.at("id").get_to(gameObject.id);
		j.at("name").get_to(gameObject.name);
		j.at("transform").get_to(gameObject.transform);
	}
	inline void from_json(const json& j, it::Time& time) {
		std::chrono::nanoseconds tempTime{ std::chrono::nanoseconds(j.at("tempTime").get<int64_t>()) };
		std::chrono::nanoseconds tempDeltaTime{ j.at("tempDeltaTime").get<int64_t>() };
		std::chrono::nanoseconds tempScaledTime{ j.at("tempScaledTime").get<int64_t>() };
		std::chrono::nanoseconds tempScaledDeltaTime{ j.at("tempScaledDeltaTime").get<int64_t>() };

		double tempScale{ j.at("tempScale").get<double>() };
		bool tempFixed{ j.at("tempFixed").get<bool>() };
		std::chrono::nanoseconds tickRate{ std::chrono::nanoseconds(j.at("tickRate").get<int64_t>()) };

		time = it::Time(tempTime, tempDeltaTime, tempScaledTime, tempScaledDeltaTime, tempScale, tempFixed, tickRate);
	}

	/***************************************************************************************/

	// ordered_json to_json functions
	inline void to_json(ordered_json& j, const glm::vec2& vec2) {
		j = ordered_json::array({ vec2[0], vec2[1] });
	}
	inline void to_json(ordered_json& j, const glm::vec3& vec3) {
		j = ordered_json::array({ vec3[0], vec3[1], vec3[2] });
	}
	inline void to_json(ordered_json& j, const glm::vec4& vec4) {
		j = ordered_json::array({ vec4[0], vec4[1], vec4[2], vec4[3] });
	}
	inline void to_json(ordered_json& j, const glm::quat& quat) {
		j = ordered_json::array({ quat[0], quat[1], quat[2], quat[3] });
	}
	inline void to_json(ordered_json& j, const glm::mat2& mat2) {
		j = ordered_json::array();
		for (size_t i = 0; i < 4; i++)
			j.push_back(mat2[i]);
	}
	inline void to_json(ordered_json& j, const glm::mat3& mat3) {
		j = ordered_json::array();
		for (size_t i = 0; i < 9; i++)
			j.push_back(mat3[i]);
	}
	inline void to_json(ordered_json& j, const glm::mat4& mat4) {
		j = ordered_json::array();
		for (size_t i = 0; i < 12; i++)
			j.push_back(mat4[i]);
	}

	inline void to_json(ordered_json& j, const b2Vec2& vec2) {
		j = ordered_json::array({ vec2.x, vec2.y });
	}
	inline void to_json(ordered_json& j, const b2Rot& rotation) {
		j = {
			{ "c", rotation.c },
			{ "s", rotation.s }
		};
	}
	inline void to_json(ordered_json& j, const b2BodyDef& bodyDef) {
		j = {
			{ "type", bodyDef.type },
			{ "position", bodyDef.position },
			{ "rotation", bodyDef.rotation },
			{ "linearVelocity", bodyDef.linearVelocity },
			{ "angularVelocity", bodyDef.angularVelocity },
			{ "linearDamping", bodyDef.linearDamping },
			{ "angularDamping", bodyDef.angularDamping },
			{ "gravityScale", bodyDef.gravityScale },
			{ "sleepThreshold", bodyDef.sleepThreshold },
			{ "name", bodyDef.name },
			{ "enableSleep", bodyDef.enableSleep },
			{ "isAwake", bodyDef.isAwake },
			//{ "fixedRotation", bodyDef.fixedRotation },
			{ "isBullet", bodyDef.isBullet },
			{ "isEnabled", bodyDef.isEnabled }
		};
	}
	inline void to_json(ordered_json& j, const b2BodyId id) {
		j = {
			j["type"] = b2Body_GetType(id),
			j["position"] = b2Body_GetPosition(id),
			j["rotation"] = b2Body_GetRotation(id),
			j["linearVelocity"] = b2Body_GetLinearVelocity(id),
			j["angularVelocity"] = b2Body_GetAngularVelocity(id),
			j["linearDamping"] = b2Body_GetLinearDamping(id),
			j["angularDamping"] = b2Body_GetAngularDamping(id),
			j["gravityScale"] = b2Body_GetGravityScale(id),
			j["sleepThreshold"] = b2Body_GetSleepThreshold(id),
			j["name"] = b2Body_GetName(id),
			//j["userData"] = b2Body_GetUserData(id),
			j["enableSleep"] = b2Body_IsSleepEnabled(id),
			j["isAwake"] = b2Body_IsAwake(id),
			//j["fixedRotation"] = b2Body_IsFixedRotation(id),
			j["isBullet"] = b2Body_IsBullet(id),
			j["isEnabled"] = b2Body_IsEnabled(id)
		};
	}
	inline void to_json(ordered_json& j, const b2SurfaceMaterial& material) {
		j = {
			{ "friction", material.friction },
			{ "restitution", material.restitution },
			{ "rollingResistance", material.rollingResistance },
			{ "tangentSpeed", material.tangentSpeed },
			{ "userMaterialId", material.userMaterialId },
			{ "customColor", material.customColor }
		};
	}
	inline void to_json(ordered_json& j, const b2Filter& filter) {
		j = {
			{ "categoryBits", filter.categoryBits },
			{ "maskBits", filter.maskBits },
			{ "groupIndex", filter.groupIndex }
		};
	}
	inline void to_json(ordered_json& j, const b2ShapeDef& shapeDef) {
		j = {
			{ "material", shapeDef.material },
			{ "density", shapeDef.density },
			{ "filter", shapeDef.filter },
			{ "isSensor", shapeDef.isSensor },
			{ "enableSensorEvents", shapeDef.enableSensorEvents },
			{ "enableContactEvents", shapeDef.enableContactEvents },
			{ "enableHitEvents", shapeDef.enableHitEvents },
			{ "enablePreSolveEvents", shapeDef.enablePreSolveEvents },
			{ "invokeContactCreation", shapeDef.invokeContactCreation },
			{ "updateBodyMass", shapeDef.updateBodyMass }
		};
	}
	inline void to_json(ordered_json& j, const b2Polygon& polygon) {
		j = {
			{ "vertices", ordered_json::array() },
			{ "normals", ordered_json::array() },
			{ "centroid", polygon.centroid },
			{ "radius", polygon.radius },
			{ "count", polygon.count }
		};
		for (size_t i = 0; i < polygon.count; i++) {
			j["vertices"].push_back(polygon.vertices[i]);
			j["normals"].push_back(polygon.normals[i]);
		}
	}

	inline void to_json(ordered_json& j, const it::GrayImage& grayImage) {
		j = {
			{ "path", grayImage.getPath() }
		};
	}
	inline void to_json(ordered_json& j, const it::GrayAlphaImage& grayAlphaImage) {
		j = {
			{ "path", grayAlphaImage.getPath() }
		};
	}
	inline void to_json(ordered_json& j, const it::RGBImage& rgbImage) {
		j = {
			{ "path", rgbImage.getPath() }
		};
	}
	inline void to_json(ordered_json& j, const it::RGBAImage& rgbaImage) {
		j = {
			{ "path", rgbaImage.getPath() }
		};
	}
	inline void to_json(ordered_json& j, const it::Transform& transform) {
		j = {
			{ "position", transform.position },
			{ "orientation", transform.orientation },
			{ "scale", transform.scale }
		};
	}
	inline void to_json(ordered_json& j, const it::GameObject& gameObject) {
		j = {
			{ "id", gameObject.id },
			{ "name", gameObject.name },
			{ "transform", gameObject.transform }
		};
	}
	inline void to_json(ordered_json& j, const it::Time& time) {
		j = {
			{ "tempTime", time.getTime().count() },
			{ "tempDeltaTime", time.getDeltaTime().count() },
			{ "tempScaledTime", time.getScaledTime().count() },
			{ "tempScaledDeltaTime", time.getScaledDeltaTime().count() },
			{ "tempScale", time.scale },
			{ "tempFixed", time.fixed },
			{ "tickRate", time.tickRate.count() }
		};
	}

	// ordered_json from_json functions
	inline void from_json(const ordered_json& j, glm::vec2& vec2) {
		j.at(0).get_to(vec2[0]);
		j.at(1).get_to(vec2[1]);
	}
	inline void from_json(const ordered_json& j, glm::vec3& vec3) {
		j.at(0).get_to(vec3[0]);
		j.at(1).get_to(vec3[1]);
		j.at(2).get_to(vec3[2]);
	}
	inline void from_json(const ordered_json& j, glm::vec4& vec4) {
		j.at(0).get_to(vec4[0]);
		j.at(1).get_to(vec4[1]);
		j.at(2).get_to(vec4[2]);
		j.at(3).get_to(vec4[3]);
	}
	inline void from_json(const ordered_json& j, glm::quat& quat) {
		j.at(0).get_to(quat[0]);
		j.at(1).get_to(quat[1]);
		j.at(2).get_to(quat[2]);
		j.at(3).get_to(quat[3]);
	}
	inline void from_json(const ordered_json& j, glm::mat2& mat2) {
		float* mat2Array = reinterpret_cast<float*>(&mat2);
		for (size_t i = 0ULL; i < 4; i++)
			j.at(i).get_to(mat2Array[i]);
	}
	inline void from_json(const ordered_json& j, glm::mat3& mat3) {
		float* mat3Array = reinterpret_cast<float*>(&mat3);
		for (size_t i = 0ULL; i < 9; i++)
			j.at(i).get_to(mat3Array[i]);
	}
	inline void from_json(const ordered_json& j, glm::mat4& mat4) {
		float* mat4Array = reinterpret_cast<float*>(&mat4);
		for (size_t i = 0ULL; i < 16; i++)
			j.at(i).get_to(mat4Array[i]);
	}

	inline void from_json(const ordered_json& j, b2Vec2& vec2) {
		j.at(0).get_to(vec2.x);
		j.at(1).get_to(vec2.y);
	}
	inline void from_json(const ordered_json& j, b2Rot& rotation) {
		j.at("c").get_to(rotation.c);
		j.at("s").get_to(rotation.s);
	}
	inline void from_json(const ordered_json& j, b2BodyDef& bodyDef) {
		j.at("type").get_to(bodyDef.type);
		j.at("position").get_to(bodyDef.position);
		j.at("rotation").get_to(bodyDef.rotation);
		j.at("linearVelocity").get_to(bodyDef.linearVelocity);
		j.at("angularVelocity").get_to(bodyDef.angularVelocity);
		j.at("linearDamping").get_to(bodyDef.linearDamping);
		j.at("angularDamping").get_to(bodyDef.angularDamping);
		j.at("gravityScale").get_to(bodyDef.gravityScale);
		j.at("sleepThreshold").get_to(bodyDef.sleepThreshold);
		std::string name;
		j.at("name").get_to(name);
		bodyDef.name = name.c_str();
		j.at("enableSleep").get_to(bodyDef.enableSleep);
		j.at("isAwake").get_to(bodyDef.isAwake);
		//j.at("fixedRotation").get_to(bodyDef.fixedRotation);
		j.at("isBullet").get_to(bodyDef.isBullet);
		j.at("isEnabled").get_to(bodyDef.isEnabled);
	}
	inline void from_json(const ordered_json& j, b2BodyId id) {
		b2BodyType type;
		b2Vec2 position;
		b2Rot rotation;
		b2Vec2 linearVelocity;
		float angularVelocity;
		float linearDamping;
		float angularDamping;
		float gravityScale;
		float sleepThreshold;
		std::string name;
		bool enableSleep;
		bool isAwake;
		bool fixedRotation;
		bool isBullet;
		bool isEnabled;

		j.at("type").get_to(type);
		j.at("position").get_to(position);
		j.at("rotation").get_to(rotation);
		j.at("linearVelocity").get_to(linearVelocity);
		j.at("angularVelocity").get_to(angularVelocity);
		j.at("linearDamping").get_to(linearDamping);
		j.at("angularDamping").get_to(angularDamping);
		j.at("gravityScale").get_to(gravityScale);
		j.at("sleepThreshold").get_to(sleepThreshold);
		j.at("name").get_to(name);
		j.at("enableSleep").get_to(enableSleep);
		j.at("isAwake").get_to(isAwake);
		j.at("fixedRotation").get_to(fixedRotation);
		j.at("isBullet").get_to(isBullet);
		j.at("isEnabled").get_to(isEnabled);

		b2Body_SetType(id, type);
		b2Body_SetTransform(id, position, rotation);
		b2Body_SetLinearVelocity(id, linearVelocity);
		b2Body_SetAngularVelocity(id, angularVelocity);
		b2Body_SetLinearDamping(id, linearDamping);
		b2Body_SetAngularDamping(id, angularDamping);
		b2Body_SetGravityScale(id, gravityScale);
		b2Body_SetSleepThreshold(id, sleepThreshold);
		b2Body_SetName(id, name.c_str());
		b2Body_EnableSleep(id, enableSleep);
		b2Body_SetAwake(id, isAwake);
		//b2Body_SetFixedRotation(id, fixedRotation);
		b2Body_SetBullet(id, isBullet);
		if (isEnabled)
			b2Body_Enable(id);
		else
			b2Body_Disable(id);
	}
	inline void from_json(const ordered_json& j, b2SurfaceMaterial& material) {
		j.at("friction").get_to(material.friction);
		j.at("restitution").get_to(material.restitution);
		j.at("rollingResistance").get_to(material.rollingResistance);
		j.at("tangentSpeed").get_to(material.tangentSpeed);
		j.at("userMaterialId").get_to(material.userMaterialId);
		j.at("customColor").get_to(material.customColor);
	}
	inline void from_json(const ordered_json& j, b2Filter& filter) {
		j.at("categoryBits").get_to(filter.categoryBits);
		j.at("maskBits").get_to(filter.maskBits);
		j.at("groupIndex").get_to(filter.groupIndex);
	}
	inline void from_json(const ordered_json& j, b2ShapeDef& shapeDef) {
		j.at("material").get_to(shapeDef.material);
		j.at("density").get_to(shapeDef.density);
		j.at("filter").get_to(shapeDef.filter);
		j.at("isSensor").get_to(shapeDef.isSensor);
		j.at("enableSensorEvents").get_to(shapeDef.enableSensorEvents);
		j.at("enableContactEvents").get_to(shapeDef.enableContactEvents);
		j.at("enableHitEvents").get_to(shapeDef.enableHitEvents);
		j.at("enablePreSolveEvents").get_to(shapeDef.enablePreSolveEvents);
		j.at("invokeContactCreation").get_to(shapeDef.invokeContactCreation);
		j.at("updateBodyMass").get_to(shapeDef.updateBodyMass);
	}
	inline void from_json(const ordered_json& j, b2Polygon& polygon) {
		j.at("centroid").get_to(polygon.centroid);
		j.at("radius").get_to(polygon.radius);
		j.at("count").get_to(polygon.count);
		for (size_t i = 0; i < polygon.count; i++) {
			j.at("vertices").at(i).get_to(polygon.vertices[i]);
			j.at("normals").at(i).get_to(polygon.normals[i]);
		}
	}

	inline void from_json(const ordered_json& j, it::GrayImage& grayImage) {
		std::string path;
		j.at("path").get_to(path);
		grayImage.load(path);
	}
	inline void from_json(const ordered_json& j, it::GrayAlphaImage& grayAlphaImage) {
		std::string path;
		j.at("path").get_to(path);
		grayAlphaImage.load(path);
	}
	inline void from_json(const ordered_json& j, it::RGBImage& rgbImage) {
		std::string path;
		j.at("path").get_to(path);
		rgbImage.load(path);
	}
	inline void from_json(const ordered_json& j, it::RGBAImage& rgbaImage) {
		std::string path;
		j.at("path").get_to(path);
		rgbaImage.load(path);
	}
	inline void from_json(const ordered_json& j, it::Transform& transform) {
		j.at("position").get_to(transform.position);
		j.at("orientation").get_to(transform.orientation);
		j.at("scale").get_to(transform.scale);
	}
	inline void from_json(const ordered_json& j, it::GameObject& gameObject) {
		j.at("id").get_to(gameObject.id);
		j.at("name").get_to(gameObject.name);
		j.at("transform").get_to(gameObject.transform);
	}
	inline void from_json(const ordered_json& j, it::Time& time) {
		std::chrono::nanoseconds tempTime{ std::chrono::nanoseconds(j.at("tempTime").get<int64_t>()) };
		std::chrono::nanoseconds tempDeltaTime{ j.at("tempDeltaTime").get<int64_t>() };
		std::chrono::nanoseconds tempScaledTime{ j.at("tempScaledTime").get<int64_t>() };
		std::chrono::nanoseconds tempScaledDeltaTime{ j.at("tempScaledDeltaTime").get<int64_t>() };

		double tempScale{ j.at("tempScale").get<double>() };
		bool tempFixed{ j.at("tempFixed").get<bool>() };
		std::chrono::nanoseconds tickRate{ std::chrono::nanoseconds(j.at("tickRate").get<int64_t>()) };

		time.reset(tempTime, tempDeltaTime, tempScaledTime, tempScaledDeltaTime, tempScale, tempFixed, tickRate);
	}
}
