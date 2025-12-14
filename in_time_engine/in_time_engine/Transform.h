/******************************************************************************
 * Copyright (c) 2024 Christopher Barrios Agosto. All Rights Reserved.
 *
 * Licensing Information:
 *  This software and associated documentation files (the "Software") may not
 *  be used, copied, modified, merged, published, distributed, sublicensed,
 *  or sold without the prior written permission of the copyright owner.
 *
 *  Unauthorized use of this file, via any medium, is strictly prohibited.
 *****************************************************************************/

/******************************************************************************
 * Project: In Time Engine
 * File: Transform.h
 * Author: Christopher Barrios Agosto
 * Created on: 13DEC2024
 *
 * Description:
 *  Owned through "has a" relationship by the GameObject class.
 *  This is the means to control game objects three dimensional behaviour
 *  (translation, rotation (euler & quaternion) and scale).
 *  Parent and child transforms can be assigned.
 *  Parent and child relationships are automatically broken through
 *  destructor.
 *  Game objects's transform will live even after the destroy or
 *  destroyImmediately are called if stack allocated until the game object's
 *  destructro is called.
 *****************************************************************************/

#pragma once

// Dependencies | std
#include <vector>
#include <functional>

// Dependencies | std
#include <list>

// Dependencies | glm
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace it {
	// Forward declarations
	class GameObject;
	class RigidBody2D;
	class GPUTransform;

	class Transform {
		// Friends
		friend class InTimeEngine;

		// Object
		private:
			// Properties
			GameObject* gameObject{ nullptr };
			Transform* parent{ nullptr };
			std::vector<Transform*> children{};
			bool dirty{ true };

		public:
			// Properties
			glm::vec3 position{ 0, 0, 0 };
			glm::quat orientation{ 1, 0, 0, 0 };
			glm::vec3 scale{ 1, 1, 1 };
			glm::mat4 globalMatrix{ 1 };

			// Constructor / Destructor
			Transform() = default;
			Transform(GameObject* gameObject);
			Transform(const Transform& transform);
			Transform(Transform&& transform) noexcept;
			~Transform();

			// Operators | Assignment
			Transform& operator=(const Transform& transform);
			Transform& operator=(Transform&& transform) noexcept;

			// Getters
			GameObject* getGameObject() const;
			Transform* getParent() const;
			std::vector<Transform*> getChildren() const;
			glm::vec3 getPosition() const;
			glm::quat getOrientation() const;
			glm::vec3 getRotation() const;
			glm::vec3 getScale() const;
			glm::mat4 getMatrix() const;
			glm::vec3 getGlobalPosition() const;
			glm::quat getGlobalOrientation() const;
			glm::vec3 getGlobalRotation() const;
			glm::vec3 getGlobalScale() const;
			glm::mat4 getGlobalMatrix();
			bool isDirty() const;


			// Setters
			void setPosition(const glm::vec3& position);
			void setOrientation(const glm::quat& orientation);
			void setScale(const glm::vec3& scale);
			void setRotation(const glm::vec3& rotation);
			void setTransform(const glm::mat4& transform);
			void setParent(Transform* transform);

			// Functions
			void makeDirty();
			void calculateGlobalMatrix();

			void translateBy(const glm::vec3& translation);
			void orientBy(const glm::quat& orientation);
			void scaleBy(const glm::vec3& scale);
			void rotateBy(const glm::vec3& rotation);

			glm::vec3 toLocalPosition(const glm::vec3& globalPosition);
			glm::quat toLocalOrientation(const glm::quat& globalOrientation);
			glm::vec3 toLocalScale(const glm::vec3& globalScale);
			glm::vec3 toLocalRotation(const glm::vec3& globalRotation);

	};
}
