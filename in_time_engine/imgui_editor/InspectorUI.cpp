#include "InspectorUI.h"

// Dependencies | in_time_engine
#include <in_time_engine/InTimeEngine.h>

// class InspectorUI

// Static | private

// Properties
it::InspectorUI* it::InspectorUI::singleton = nullptr;

// Static | public

// Getters
it::InspectorUI* it::InspectorUI::getSingleton() {
	return singleton;
}

// Object | private

// Funcitons
void it::InspectorUI::inspectTransform(it::Transform& transform) {
	std::string uiId = "Transform##" + std::to_string((unsigned long long)&transform);

	if (ImGui::TreeNode(uiId.c_str())) {
		it::Transform& transform = gameObject->transform;
		glm::vec3 position = transform.position;
		glm::quat orientation = transform.orientation;
		glm::vec3 scale = transform.scale;

		ImGui::DragFloat3("Position", (float*)&transform.position, 0.1f);
		ImGui::DragFloat4("Orientation", (float*)&transform.orientation, 0.1f);
		ImGui::DragFloat3("Scale", (float*)&transform.scale, 0.1f);

		transform.hintUpdate();

		ImGui::TreePop();
	}
}
void it::InspectorUI::inspectComponent(it::Component& component) {
	const type_info& typeInfo = component.getTypeInfo();
	std::string uiId = std::string(typeInfo.name()) + "##" + std::to_string((unsigned long long)&component);

	if (typeInfo == typeid(EmptyComponent)) {
		ImGui::Selectable(uiId.c_str());
	}

	else if (typeInfo == typeid(Camera2D)) {
		Camera2D* camera = (Camera2D*)&component;

		if (ImGui::CollapsingHeader("Camera Properties", ImGuiTreeNodeFlags_DefaultOpen)) {
			// Background Color
			ImGui::ColorEdit4("Background Color", (float*)&camera->camera2D.backgroundColor);

			// Clear Depth
			ImGui::DragFloat("Clear Depth", &camera->camera2D.clearDepth, 0.01f, -1.0f, 1.0f);

			// Position
			ImGui::DragFloat3("Position", (float*)&camera->camera2D.position, 0.1f);

			// Fullscreen toggle
			ImGui::Checkbox("Render Fullscreen", &camera->camera2D.renderFullScreen);

			// Clipping planes
			ImGui::DragFloat("Near Clipping Plane", &camera->camera2D.nearClippingPlane, 0.01f, 0.001f, camera->camera2D.farClippingPlane - 0.01f);
			ImGui::DragFloat("Far Clipping Plane", &camera->camera2D.farClippingPlane, 1.0f, camera->camera2D.nearClippingPlane + 0.01f, 10000.0f);
		}
	}
	else if (typeInfo == typeid(Camera3D)) {
		Camera3D* camera = (Camera3D*)&component;

		if (ImGui::CollapsingHeader("Camera Properties", ImGuiTreeNodeFlags_DefaultOpen)) {
			// Background Color
			ImGui::ColorEdit4("Background Color", (float*)&camera->camera3D.backgroundColor);

			// Clear Depth
			ImGui::DragFloat("Clear Depth", &camera->camera3D.clearDepth, 0.01f, -1.0f, 1.0f);

			// Position
			ImGui::DragFloat3("Position", (float*)&camera->camera3D.position, 0.1f);

			// Fullscreen toggle
			ImGui::Checkbox("Render Fullscreen", &camera->camera3D.renderFullScreen);

			// Clipping planes
			ImGui::DragFloat("Near Clipping Plane", &camera->camera3D.nearClippingPlane, 0.01f, 0.001f, camera->camera3D.farClippingPlane - 0.01f);
			ImGui::DragFloat("Far Clipping Plane", &camera->camera3D.farClippingPlane, 1.0f, camera->camera3D.nearClippingPlane + 0.01f, 10000.0f);
		}
	}
	else if (typeInfo == typeid(GPUTransform)) {
		it::GPUTransform* gpuTransform = (GPUTransform*)&component;
		gl::Transform* transform = (gl::Transform*)&gpuTransform->glTransform;

		if (ImGui::TreeNode(uiId.c_str())) {
			ImGui::Text(std::to_string(transform->getIndex()).c_str());
			ImGui::TreePop();
		}
	}
	else if (typeInfo == typeid(GPUPoint)) {
		GPUPoint* gpuPoint = (GPUPoint*)&component;
		gl::Point::GPUData data = gpuPoint->point.gpuData;

		if (ImGui::TreeNode(uiId.c_str())) {
			ImGui::InputInt("Transform Index", &data.transformIndex);
			ImGui::DragFloat("Size", &data.size, 0.1f, 0.0f, 100.0f, "%.2f");
			ImGui::DragFloat3("Offset", (float*)&data.offset, 0.1f, -100.0f, 100.0f);
			ImGui::ColorEdit4("Color", (float*)(&data.color));

			ImGui::TreePop();
		}
	}
	else if (typeInfo == typeid(GPULine)) {
		GPULine* gpuLine = (GPULine*)&component;
		gl::Line::GPUData* data = gpuLine->line.gpuData;

		if (ImGui::TreeNode(uiId.c_str())) {
			for (int i = 0; i < 2; ++i) {
				std::string label = "P" + std::to_string(i);

				if (ImGui::TreeNode(label.c_str())) {
					ImGui::PushID(i);  // Ensure unique ImGui IDs for each block

					ImGui::InputInt("Transform Index", &data[i].transformIndex);
					ImGui::DragFloat3("Position", (float*)(&data[i].position), 0.1f, -100.0f, 100.0f);
					ImGui::DragFloat3("Offset", (float*)(&data[i].offset), 0.1f, -100.0f, 100.0f);
					ImGui::ColorEdit4("Color", (float*)(&data[i].color));

					ImGui::PopID();
					ImGui::TreePop();
				}
			}

			ImGui::TreePop();
		}
	}
	else if (typeInfo == typeid(GPUTriangle)) {
		GPUTriangle* gpuTriangle = (GPUTriangle*)&component;
		gl::Triangle::GPUData* data = gpuTriangle->triangle.gpuData;

		if (ImGui::TreeNode(uiId.c_str())) {
			for (size_t i = 0; i < 3; ++i) {
				std::string label = "Vertex " + std::to_string(i);
				if (ImGui::TreeNode(label.c_str())) {
					ImGui::PushID(static_cast<int>(i));  // Unique ID for ImGui

					ImGui::InputInt("Transform Index", &data[i].transformIndex);
					ImGui::DragFloat3("Position", (float*)(&data[i].position), 0.1f, -100.0f, 100.0f);
					ImGui::ColorEdit4("Color", (float*)(&data[i].color));

					ImGui::PopID();
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
		else {
			ImGui::Selectable(uiId.c_str());
		}
	}
	else if (typeInfo == typeid(GPUTriangleFan)) {
		GPUTriangleFan* gpuTriangleFan = (GPUTriangleFan*)&component;
		std::vector<gl::TriangleFan::GPUData>& data = gpuTriangleFan->triangleFan.gpuData;

		if (ImGui::TreeNode(uiId.c_str())) {
			for (size_t i = 0; i < data.size(); ++i) {
				std::string label = "Vertex " + std::to_string(i);
				if (ImGui::TreeNode(label.c_str())) {
					ImGui::PushID(static_cast<int>(i));  // Unique ID for ImGui

					ImGui::InputInt("Transform Index", &data[i].transformIndex);
					ImGui::DragFloat3("Position", (float*)(&data[i].position), 0.1f, -100.0f, 100.0f);
					ImGui::ColorEdit4("Color", (float*)(&data[i].color));

					ImGui::PopID();
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
	}
	else if (typeInfo == typeid(GPUTriangleStrip)) {
			GPUTriangleStrip* gpuTriangleStrip = (GPUTriangleStrip*)&component;
			std::vector<gl::TriangleStrip::GPUData>& data = gpuTriangleStrip->triangleStrip.gpuData;

			if (ImGui::TreeNode(uiId.c_str())) {
				for (size_t i = 0; i < data.size(); ++i) {
					std::string label = "Vertex " + std::to_string(i);
					if (ImGui::TreeNode(label.c_str())) {
						ImGui::PushID(static_cast<int>(i));  // Unique ID for ImGui

						ImGui::InputInt("Transform Index", &data[i].transformIndex);
						ImGui::DragFloat3("Position", (float*)(&data[i].position), 0.1f, -100.0f, 100.0f);
						ImGui::ColorEdit4("Color", (float*)(&data[i].color));

						ImGui::PopID();
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
			}

	else if (typeInfo == typeid(RigidBody2D)) {
		if (ImGui::TreeNode(uiId.c_str())) {
			RigidBody2D* rigidBody2D = (RigidBody2D*)&component;
			b2BodyId bodyId = rigidBody2D->getId();

			float angularDamping = b2Body_GetAngularDamping(bodyId);
			float angularVelocity = b2Body_GetAngularVelocity(bodyId);
			int contactCapacity = b2Body_GetContactCapacity(bodyId);
			float gravityScale = b2Body_GetGravityScale(bodyId);
			int jointCount = b2Body_GetJointCount(bodyId);
			float linearDamping = b2Body_GetLinearDamping(bodyId);
			b2Vec2 linearVelocity = b2Body_GetLinearVelocity(bodyId);
			float mass = b2Body_GetMass(bodyId);
			std::string name = b2Body_GetName(bodyId);
			float rotationalInertia = b2Body_GetRotationalInertia(bodyId);
			int shapeCount = b2Body_GetShapeCount(bodyId);
			float sleepThreshold = b2Body_GetSleepThreshold(bodyId);
			b2BodyType bodyType = b2Body_GetType(bodyId);
			int bodyTypeIndex = static_cast<int>(bodyType);
			bool isAwake = b2Body_IsAwake(bodyId);
			bool isBullet = b2Body_IsBullet(bodyId);
			bool isEnabled = b2Body_IsEnabled(bodyId);
			bool isFixedRotation = b2Body_IsFixedRotation(bodyId);
			bool isSleepEnabled = b2Body_IsSleepEnabled(bodyId);
			bool isValid = b2Body_IsValid(bodyId);
			b2Transform transform2D = b2Body_GetTransform(bodyId);

			b2Vec2 position = transform2D.p;
			float rotation = b2Rot_GetAngle(transform2D.q);

			// Editable fields
			if (ImGui::DragFloat("Angular Damping", &angularDamping, 0.01f, 0.0f, 10.0f))
				b2Body_SetAngularDamping(bodyId, angularDamping);

			if (ImGui::DragFloat("Linear Damping", &linearDamping, 0.01f, 0.0f, 10.0f))
				b2Body_SetLinearDamping(bodyId, linearDamping);

			if (ImGui::DragFloat("Gravity Scale", &gravityScale, 0.1f, 0.0f, 10.0f))
				b2Body_SetGravityScale(bodyId, gravityScale);

			if (ImGui::DragFloat2("Linear Velocity", &linearVelocity.x, 0.1f))
				b2Body_SetLinearVelocity(bodyId, linearVelocity);

			if (ImGui::DragFloat("Angular Velocity", &angularVelocity, 0.1f))
				b2Body_SetAngularVelocity(bodyId, angularVelocity);

			if (ImGui::DragFloat("Sleep Threshold", &sleepThreshold, 0.01f, 0.0f, 1.0f))
				b2Body_SetSleepThreshold(bodyId, sleepThreshold);


			const char* bodyTypeNames[] = { "Static", "Kinematic", "Dynamic" };
			if (ImGui::Combo("Body Type", &bodyTypeIndex, bodyTypeNames, IM_ARRAYSIZE(bodyTypeNames)))
				b2Body_SetType(bodyId, static_cast<b2BodyType>(bodyTypeIndex));

			if (ImGui::Checkbox("Is Bullet", &isBullet))
				b2Body_SetBullet(bodyId, isBullet);

			if (ImGui::Checkbox("Fixed Rotation", &isFixedRotation))
				b2Body_SetFixedRotation(bodyId, isFixedRotation);

			if (ImGui::Checkbox("Awake", &isAwake))
				b2Body_SetAwake(bodyId, isAwake);

			if (ImGui::Checkbox("Enabled", &isEnabled)) {
				if (isEnabled)
					b2Body_Enable(bodyId);
				else
					b2Body_Disable(bodyId);
			}

			if (ImGui::Checkbox("Sleep Enabled", &isSleepEnabled))
				b2Body_EnableSleep(bodyId, isSleepEnabled);

			// Position and Rotation (via transform)
			b2Transform transform = b2Body_GetTransform(bodyId);
			if (ImGui::DragFloat2("Position", &position.x, 0.1f) || ImGui::DragFloat("Rotation (rad)", &rotation, 0.01f)) {

				b2Body_SetTransform(bodyId, position, b2MakeRot(rotation));
			}

			// Display-only fields
			ImGui::SeparatorText("Read-only Properties");
			ImGui::Text("Name: %s", b2Body_GetName(bodyId));
			ImGui::Text("Mass: %.3f", b2Body_GetMass(bodyId));
			ImGui::Text("Rotational Inertia: %.3f", b2Body_GetRotationalInertia(bodyId));
			ImGui::Text("Shape Count: %d", b2Body_GetShapeCount(bodyId));
			ImGui::Text("Joint Count: %d", b2Body_GetJointCount(bodyId));
			ImGui::Text("Contact Capacity: %d", b2Body_GetContactCapacity(bodyId));

			ImGui::TreePop();
		}

	}
	else if (typeInfo == typeid(Shape2D)) {

	}
}

// Object | public

// Constructor / Destructor
it::InspectorUI::InspectorUI() {
	if (singleton == nullptr)
		singleton = this;
}
it::InspectorUI::~InspectorUI() {
	if (this == singleton)
		singleton = nullptr;
}

// Setters
void it::InspectorUI::setGameObject(it::GameObject* gameObject) {
	if (locked)
		return;

	this->gameObject = gameObject;
	if (gameObject == nullptr) {
		resize = false;
	}
	else {
		resize = true;
	}
}

// Functions
void it::InspectorUI::update() {
	ImGui::Begin("Inspector");

	// Return if there is nothing to inspect
	if (gameObject == nullptr) {
		ImGui::End();
		return;
	}

	// Inspect transform
	inspectTransform(gameObject->transform);

	// Inspect components
	std::vector<Component*> components = gameObject->getComponents();
	for (Component* component : components)
		inspectComponent(*component);

	// Resize window
	if (resize) {
		ImVec2 newWindowSize = { 400, 600 };
		ImGui::SetWindowSize(newWindowSize);
		resize = false;
	}

	ImGui::End();
}
