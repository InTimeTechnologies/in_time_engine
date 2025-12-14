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
 * File: Transform.cpp
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
 *  destructor is called.
 *****************************************************************************/

#include "Transform.h"

// Dependencies | glm
#include <glm/gtx/matrix_decompose.hpp>

// Dependencies | in_time_engine
#include "GameObject.h"

#if defined(OPENGL_ENGINE)
#include "gpu_component/GPUTransform.h"
#endif

#if defined(BOX2D_ENGINE)
#include "physics_engine_2d/RigidBody2D.h"
#endif

#include <iostream>

namespace it {
	// class Transform

	// Object | public

	// Constructor / Destructor
	Transform::Transform(GameObject* gameObject) : gameObject(gameObject) {

	}
	Transform::Transform(const Transform& transform) :
		position(transform.position),
		orientation(transform.orientation),
		scale(transform.scale) {
	}
	Transform::~Transform() {
		setParent(nullptr);
		for (Transform* currentChildTransform : children)
			currentChildTransform->setParent(nullptr);
	}
	Transform::Transform(Transform&& transform) noexcept:
		gameObject(transform.gameObject),
		parent(transform.parent),
		children(std::move(transform.children)),
		position(transform.position),
		orientation(transform.orientation),
		scale(transform.scale),
		globalMatrix(transform.globalMatrix) {

		// Reset moved transform
		transform.gameObject = nullptr;
		transform.parent = nullptr;
		transform.children.clear();
	}

	// Operators | Assignment
	Transform& Transform::operator=(const Transform& transform) {
		if (this == &transform)
			return *this;
		position = transform.position;
		orientation = transform.orientation;
		scale = transform.scale;

		makeDirty();
		return *this;
	}
	Transform& Transform::operator=(Transform&& transform) noexcept {
		if (this == &transform)
			return *this;
		// Unlink from current parent
		setParent(nullptr);
		// Move data
		gameObject = transform.gameObject;
		parent = transform.parent;
		children = std::move(transform.children);
		position = transform.position;
		orientation = transform.orientation;
		scale = transform.scale;
		globalMatrix = transform.globalMatrix;
		// Reset moved transform
		transform.gameObject = nullptr;
		transform.parent = nullptr;
		transform.children.clear();

		makeDirty();
		return *this;
	}

	// Getters
	GameObject* Transform::getGameObject() const {
		return gameObject;
	}
	Transform* Transform::getParent() const {
		return parent;
	}
	std::vector<Transform*> Transform::getChildren() const {
		return children;
	}
	glm::vec3 Transform::getPosition() const {
		return position;
	}
	glm::quat Transform::getOrientation() const {
		return orientation;
	}
	glm::vec3 Transform::getScale() const {
		return scale;
	}
	glm::vec3 Transform::getRotation() const {
		return glm::eulerAngles(orientation);
	}
	glm::mat4 Transform::getGlobalMatrix() {
		if (dirty)
			calculateGlobalMatrix();
		return globalMatrix;
	}
	glm::vec3 Transform::getGlobalPosition() const {
		glm::vec3 globalPosition{ position };
		Transform* currentTransform{ parent };
		while (currentTransform != nullptr) {
			globalPosition += currentTransform->position;
			currentTransform = currentTransform->parent;
		}
		return globalPosition;
	}
	glm::quat Transform::getGlobalOrientation() const {
		glm::quat globalOrientation{ orientation };
		Transform* currentTransform{ parent };
		while (currentTransform != nullptr) {
			globalOrientation = currentTransform->orientation * globalOrientation;
			currentTransform = currentTransform->parent;
		}
		return globalOrientation;
	}
	glm::vec3 Transform::getGlobalScale() const {
		glm::vec3 globalScale{ scale };
		Transform* currentTransform{ parent };
		while (currentTransform != nullptr) {
			globalScale *= currentTransform->scale;
			currentTransform = currentTransform->parent;
		}
		return globalScale;
	}
	glm::vec3 Transform::getGlobalRotation() const {
		glm::vec3 globalRotation{ getRotation() };
		Transform* currentTransform{ parent };
		while (currentTransform != nullptr) {
			globalRotation += currentTransform->getRotation();
			currentTransform = currentTransform->parent;
		}
		return globalRotation;
	}
	glm::mat4 Transform::getMatrix() const {
		glm::mat4 matrix{ 1.0f };
		matrix = glm::translate(matrix, position);
		matrix *= glm::mat4{ orientation };
		matrix = glm::scale(matrix, scale);
		return matrix;
	}
	bool Transform::isDirty() const {
		return dirty;
	}

	// Setters
	void Transform::setPosition(const glm::vec3& position) {
		this->position = position;
		makeDirty();
	}
	void Transform::setOrientation(const glm::quat& orientation) {
		this->orientation = glm::normalize(orientation);
		makeDirty();
	}
	void Transform::setScale(const glm::vec3& scale) {
		this->scale = scale;
		makeDirty();
	}
	void Transform::setRotation(const glm::vec3& rotation) {
		orientation = glm::normalize(glm::quat(rotation));
		makeDirty();
	}
	void Transform::setParent(Transform* transform) {
		// Unlink from current parent
		if (parent != nullptr)
			for (unsigned int i = 0; i < parent->children.size(); i++)
				if (parent->children[i] == this) {
					parent->children.erase(parent->children.begin() + i);
					parent = nullptr;
					break;
				}

		// Exit if new parent == mullptr
		if (transform == nullptr)
			return;

		// Link to new parent
		parent = transform;
		parent->children.push_back(this);

		makeDirty();
	}
	void Transform::calculateGlobalMatrix() {
		// Get local matrix or global matrix
		globalMatrix = parent == nullptr ? getMatrix() : parent->getGlobalMatrix() * getMatrix();
		dirty = false;
		//if (parent == nullptr)
		//	globalMatrix = getMatrix();
		//else
		//	globalMatrix = parent->getGlobalMatrix() * getMatrix();
	}

	// Functions
	void Transform::makeDirty() {
		dirty = true;
		for (Transform* child : children)
			child->makeDirty();
	}

	void Transform::setTransform(const glm::mat4& transform) {
		glm::vec3 skew = glm::vec3(0); // Ignored
		glm::vec4 perspective = glm::vec4(0); // Ignored
		glm::decompose(transform, scale, orientation, position, skew, perspective);
		makeDirty();
	}

	void Transform::translateBy(const glm::vec3& translation) {
		position += translation;
		makeDirty();
	}
	void Transform::orientBy(const glm::quat& orientation) {
		this->orientation = orientation + this->orientation;
		makeDirty();
	}
	void Transform::scaleBy(const glm::vec3& scale) {
		this->scale *= scale;
		makeDirty();
	}
	void Transform::rotateBy(const glm::vec3& rotation) {
		glm::quat deltaOrientation = glm::quat(rotation);
		orientation = glm::normalize(deltaOrientation * orientation);
		makeDirty();
	}

	glm::vec3 Transform::toLocalPosition(const glm::vec3& globalPosition) {
		return glm::inverse(getGlobalMatrix()) * glm::vec4(globalPosition, 1.0f);
	}
	glm::quat Transform::toLocalOrientation(const glm::quat& globalOrientation) {
		return glm::quat_cast(glm::inverse(getGlobalMatrix()) * glm::mat4_cast(globalOrientation));
	}
	glm::vec3 Transform::toLocalScale(const glm::vec3& globalScale) {
		glm::vec3 parentGlobalScale = parent != nullptr ? parent->getGlobalScale() : glm::vec3(1.0f);
		return globalScale / parentGlobalScale;
	}
	glm::vec3 Transform::toLocalRotation(const glm::vec3& globalRotation) {
		return glm::eulerAngles(toLocalOrientation(globalRotation));
	}
}
