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
 *  destructro is called.
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

// class Transform

// Static | private

// Properties
std::list<it::Transform*> it::Transform::s_gpuTransformUpdateList = std::list<it::Transform*>();
std::list<it::Transform*> it::Transform::s_physics2DTransformUpdateList = std::list<it::Transform*>();

// Functions
void it::Transform::s_updateGPUTransform() {
	while (s_gpuTransformUpdateList.size() > 0) {
		// Update global matrix
		Transform* transform = s_gpuTransformUpdateList.front();
		transform->setGlobalMatrix();

		#if defined(OPENGL_ENGINE)
		// Send global matrix to gpu
		if (transform->gpuTransform != nullptr)
			transform->gpuTransform->update(transform->globalMatrix);
		#endif

		// Remove gpu update node from update list
		transform->gpuRequiresUpdate = false;
		s_gpuTransformUpdateList.erase(transform->gpuTransformNode);
	}
}

// Object | private

// Functions
void it::Transform::unhintGPUUpdate() {
	if (gpuRequiresUpdate) {
		s_gpuTransformUpdateList.erase(gpuTransformNode);
		gpuRequiresUpdate = false;
	}
}

// Object | public

// Constructor / Destructor
it::Transform::Transform(GameObject& gameObject) : gameObject(gameObject) {
	hintUpdate();
}
it::Transform::~Transform() {
	setParent(nullptr);
	for (Transform* currentChildTransform : children)
		currentChildTransform->setParent(nullptr);
}

// Getters
it::GameObject& it::Transform::getGameObject() const {
	return gameObject;
}
it::Transform* it::Transform::getParent() const {
	return parent;
}
std::vector<it::Transform*> it::Transform::getChildren() const {
	return children;
}
it::RigidBody2D* it::Transform::getRigidBody2D() const {
	return rigidBody2D;
}
it::GPUTransform* it::Transform::getGPUTransform() const {
	return gpuTransform;
}
bool it::Transform::getGlobalMatrixRequiresUpdate() const {
	return globalMatrixRequiresUpdate;
}
bool it::Transform::getGPURequiresUpdate() const {
	return gpuRequiresUpdate;
}
glm::vec3 it::Transform::getPosition() const {
	return position;
}
glm::quat it::Transform::getOrientation() const {
	return orientation;
}
glm::vec3 it::Transform::getScale() const {
	return scale;
}
glm::vec3 it::Transform::getRotation() const {
	return glm::eulerAngles(orientation);
}
glm::mat4 it::Transform::getGlobalMatrix() {
	if (globalMatrixRequiresUpdate)
		setGlobalMatrix();
	return globalMatrix;
}

// Setters
void it::Transform::setPosition(const glm::vec3& position) {
	this->position = position;
	hintUpdate();
}
void it::Transform::setOrientation(const glm::quat& orientation) {
	this->orientation = glm::normalize(orientation);
	hintUpdate();
}
void it::Transform::setScale(const glm::vec3& scale) {
	this->scale = scale;
	hintUpdate();
}
void it::Transform::setRotation(const glm::vec3& rotation) {
	orientation = glm::normalize(glm::quat(rotation));
	hintUpdate();
}
void it::Transform::setParent(it::Transform* transform) {
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

	hintUpdate();
}
void it::Transform::setGlobalMatrix() {
	if (parent == nullptr)
		globalMatrix = getMatrix();
	else
		globalMatrix = parent->getGlobalMatrix() * getMatrix();
	globalMatrixRequiresUpdate = false;

	hintUpdate();
}

// Functions
void it::Transform::hintUpdate() {
	hintGlobalMatrixUpdate();
	hintGPUUpdate();
}
void it::Transform::hintGlobalMatrixUpdate() {
	if (globalMatrixRequiresUpdate)
		return;
	globalMatrixRequiresUpdate = true;
}
void it::Transform::hintGPUUpdate() {
	if (gpuTransform == nullptr || gpuRequiresUpdate)
		return;
	gpuRequiresUpdate = true;

	s_gpuTransformUpdateList.push_back(this);
	gpuTransformNode = std::prev(s_gpuTransformUpdateList.end());

	for (Transform* currentChildTransform : children)
		currentChildTransform->hintGPUUpdate();
}

void it::Transform::setTransform(const glm::mat4& transform) {
	glm::vec3 skew = glm::vec3(0); // Ignored
	glm::vec4 perspective = glm::vec4(0); // Ignored
	glm::decompose(transform, scale, orientation, position, skew, perspective);
	hintUpdate();
}

void it::Transform::translateBy(const glm::vec3& translation) {
	position += translation;
	hintUpdate();
}
void it::Transform::orientBy(const glm::quat& orientation) {
	this->orientation = orientation + this->orientation;
	hintUpdate();
}
void it::Transform::scaleBy(const glm::vec3& scale) {
	this->scale *= scale;
	hintUpdate();
}
void it::Transform::rotateBy(const glm::vec3& rotation) {
	glm::quat deltaOrientation = glm::quat(rotation);
	orientation = glm::normalize(deltaOrientation * orientation);
	hintUpdate();
}

glm::vec3 it::Transform::getGlobalPosition() {
	glm::mat4 matrix = getGlobalMatrix();
	return glm::vec3(matrix[3]); // Gets the entire 4th column and drops w
}
glm::quat it::Transform::getGlobalOrientation() const {
	if (parent == nullptr)
		return orientation;
	return orientation * parent->getGlobalOrientation();
}
glm::vec3 it::Transform::getGlobalScale() const {
	if (parent == nullptr)
		return scale;
	return scale * parent->getGlobalScale();
}
glm::vec3 it::Transform::getGlobalRotation() const {
	return glm::eulerAngles(getGlobalOrientation());
}
glm::mat4 it::Transform::getMatrix() const {
	glm::mat4 matrix = glm::mat4(1);
	matrix = glm::translate(matrix, position);
	matrix *= glm::mat4_cast(orientation);
	matrix = glm::scale(matrix, scale);
	return matrix;
}

glm::vec3 it::Transform::toLocalPosition(const glm::vec3& globalPosition) {
	return glm::inverse(getGlobalMatrix()) * glm::vec4(globalPosition, 1.0f);
}
glm::quat it::Transform::toLocalOrientation(const glm::quat& globalOrientation) {
	return glm::quat_cast(glm::inverse(getGlobalMatrix()) * glm::mat4_cast(globalOrientation));
}
glm::vec3 it::Transform::toLocalScale(const glm::vec3& globalScale) {
	glm::vec3 parentGlobalScale = parent != nullptr ? parent->getGlobalScale() : glm::vec3(1.0f);
	return globalScale / parentGlobalScale;
}
glm::vec3 it::Transform::toLocalRotation(const glm::vec3& globalRotation) {
	return glm::eulerAngles(toLocalOrientation(globalRotation));
}
