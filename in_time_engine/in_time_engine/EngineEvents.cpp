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
 * File: EngineEvents.h
 * Author: Christopher Barrios Agosto
 * Created on: 13DEC2024
 *
 * Description:
 *  This file contains all engine events.
 *****************************************************************************/

#include "EngineEvents.h"

// class IComponentInit

// Static | private

// Properties
std::list<it::InitializeEvent*> it::InitializeEvent::s_initializeEventList = std::list<it::InitializeEvent*>();

// Functions
void it::InitializeEvent::s_init() {
	// To-Do: Implement
}
void it::InitializeEvent::s_enable() {
	// To-Do: Implement
}
void it::InitializeEvent::s_start() {
	// To-Do: Implement
}

// Object | public

// Constructor / Destructor
it::InitializeEvent::InitializeEvent() {
	node = std::prev(s_initializeEventList.end());
}
it::InitializeEvent::~InitializeEvent() {
	s_initializeEventList.erase(node);
}

// Events
void it::InitializeEvent::onInit() {
	// To be implemented in child class
}
void it::InitializeEvent::onEnable() {
	// To be implemented in child class
}
void it::InitializeEvent::onStart() {
	// To be implemented in child class
}
void it::InitializeEvent::onDisable() {
	// To be implemented in child class
}

// Functions
void it::InitializeEvent::enable(bool enable) {
	// To-Do: Implement
}

// UpdateEvent

// Static | private

// Properties
std::list<it::UpdateEvent*> it::UpdateEvent::s_updateEventList = std::list<it::UpdateEvent*>();

// Functions
void it::UpdateEvent::s_preUpdate() {
	for (it::UpdateEvent* updateEvent : s_updateEventList)
		updateEvent->onPreUpdate();
}
void it::UpdateEvent::s_updateGPUTransform() {
	for (UpdateEvent* updateEvent : s_updateEventList)
		updateEvent->onUpdate();
}
void it::UpdateEvent::s_postUpdate() {
	for (it::UpdateEvent* updateEvent : s_updateEventList)
		updateEvent->onPostUpdate();
}

// Object | public

// Constructor / Destructor
it::UpdateEvent::UpdateEvent() {
	s_updateEventList.push_back(this);
	node = std::prev(s_updateEventList.end());
}
it::UpdateEvent::~UpdateEvent() {
	s_updateEventList.erase(node);
}

// Events
void it::UpdateEvent::onPreUpdate() {
	// To be implemented in child class
}
void it::UpdateEvent::onUpdate() {
	// To be implemented in child class
}
void it::UpdateEvent::onPostUpdate() {
	// To be implemented in child class
}

// PhysicsUpdateEvent

// Static | private

// Properties
std::list<it::PhysicsUpdateEvent2D*> it::PhysicsUpdateEvent2D::s_physics2DTransformUpdateList = std::list<it::PhysicsUpdateEvent2D*>();

// Object | public

// Constructor / Destructor
it::PhysicsUpdateEvent2D::PhysicsUpdateEvent2D() {
	// Add this to the list
	s_physics2DTransformUpdateList.push_back(this);
	node = std::prev(s_physics2DTransformUpdateList.end());
}
it::PhysicsUpdateEvent2D::~PhysicsUpdateEvent2D() {
	// Remove this from the list
	s_physics2DTransformUpdateList.erase(node);
}

// Events
void it::PhysicsUpdateEvent2D::onPrePhysicsUpdate2D() {
	// To be implemented in child class
}
void it::PhysicsUpdateEvent2D::onPostPhysicsUpdate2D() {
	// To be implemented in child class
}

// class PhysicsUpdateEvent3D

// Static | private

// Properties
std::list<it::PhysicsUpdateEvent3D*> it::PhysicsUpdateEvent3D::s_physics3DTransformUpdateList = std::list<it::PhysicsUpdateEvent3D*>();

// Constructor / Destructor
it::PhysicsUpdateEvent3D::PhysicsUpdateEvent3D() {
	// Add this to the list
	s_physics3DTransformUpdateList.push_back(this);
	node = std::prev(s_physics3DTransformUpdateList.end());
}
it::PhysicsUpdateEvent3D::~PhysicsUpdateEvent3D() {
	// Remove this from the list
	s_physics3DTransformUpdateList.erase(node);
}

// Events
void it::PhysicsUpdateEvent3D::onPrePhysicsUpdate3D() {
	// To be implemented in child class
}
void it::PhysicsUpdateEvent3D::onPostPhysicsUpdate3D() {
	// To be implemented in child class
}

// class RenderEvent

// Static | private

// Properties
std::list<it::RenderEvent*> it::RenderEvent::s_renderList = std::list<it::RenderEvent*>();

// Object | public

// Constructor / Destructor
it::RenderEvent::RenderEvent() {
	s_renderList.push_back(this);
	node = std::prev(s_renderList.end());
}
it::RenderEvent::~RenderEvent() {
	s_renderList.erase(node);
}

// Events
void it::RenderEvent::onPreRender() {
	// To be implemented in child class
}
void it::RenderEvent::render() {
	// To be implemented in child class
}
void it::RenderEvent::onPostRender() {
	// To be implemented in child class
}

// class RenderUIEvent

// Static | private

// Properties
std::list<it::RenderUIEvent*> it::RenderUIEvent::s_renderUIList = std::list<it::RenderUIEvent*>();

// Object | public

// Constructor / Destructor
it::RenderUIEvent::RenderUIEvent() {
	s_renderUIList.push_back(this);
	node = std::prev(s_renderUIList.end());
}
it::RenderUIEvent::~RenderUIEvent() {
	s_renderUIList.erase(node);
}

// Events
void it::RenderUIEvent::render() {
	// To be implemented in child class
}
