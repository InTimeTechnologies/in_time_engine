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
 * File: InTimeEngine.cpp
 * Author: Christopher Barrios Agosto
 * Created on: 13DEC2024
 *
 * Description:
 *  Operates all the core systems of the engine such as:
 *  - Game loop
 *  - Game object and component lifetime tracking to the game egine
 *  - Garbage collection through the interfaces
 *  - Time synchronization
 *  - Third party system update(s) such as but not limited to physics engine
 *  - Notification of engine events such as:
 *    - update
 *    - physicsUpdate
 *    - render
 *    - component initialization events
 *    - etc.
 *****************************************************************************/

#include "InTimeEngine.h"

// Dependencies | std
#include <thread>

// Dependencies | physics_engine_2d
#include "physics_engine_2d/RigidBody2D.h"

// class InTimeEngine

// Static | private

// Properties
it::InTimeEngine* it::InTimeEngine::s_singleton = nullptr;
bool it::InTimeEngine::s_initialized = false;

// Static | public

// Getters
it::InTimeEngine* it::InTimeEngine::s_getSingleton() {
	return s_singleton;
}

// Object | public

// Constructor / Destructor
it::InTimeEngine::InTimeEngine(const std::filesystem::path& applicationDirectoryPath) {
	if (s_singleton == nullptr)
		s_singleton = this;
}
it::InTimeEngine::~InTimeEngine() {
	if (s_singleton != nullptr)
		s_singleton = nullptr;

	if (destroyGameObjectsOnDelete)
		GameObject::s_destroyGameObjectsImmediately();
}

// Getters
it::EngineState it::InTimeEngine::getState() const {
	return state;
}
bool it::InTimeEngine::getShouldPause() const {
	return shouldPause;
}
bool it::InTimeEngine::getShouldStop() const {
	return shouldStop;
}

// Functions
void it::InTimeEngine::run() {
	// Update engine state
	state = EngineState::RUNNING;

	// Set up time
	realTime.start();

	std::chrono::nanoseconds lastPhysicsTick = realTime.getRunTime();
	std::chrono::nanoseconds lastCoreTick = realTime.getRunTime();

	// Engine / game loop
	while (!shouldStop) {
		// Update time
		realTime.tick();
		bool physicsShouldUpdate = physicsTime.tick(realTime.getRunTime() - lastPhysicsTick);
		bool coreShouldUpdate = coreTime.tick(realTime.getRunTime() - lastCoreTick);

		if (physicsShouldUpdate)
			lastPhysicsTick += physicsTime.tickRate;

		if (coreShouldUpdate)
			lastCoreTick += coreTime.fixed ? coreTime.tickRate : realTime.getDeltaTime();

		if (!physicsShouldUpdate && !coreShouldUpdate) {
			// Sleep thread until next time to update
			std::chrono::nanoseconds physicsDeltaTimeToTick = realTime.getRunTime() - lastPhysicsTick + physicsTime.tickRate;
			std::chrono::nanoseconds coreDeltaTimeToTick = realTime.getRunTime() - lastCoreTick + (coreTime.fixed ? coreTime.tickRate : std::chrono::nanoseconds(0));
			std::chrono::nanoseconds deltaTimeToTick = physicsDeltaTimeToTick > coreDeltaTimeToTick ? physicsDeltaTimeToTick : coreDeltaTimeToTick;
			std::chrono::steady_clock::time_point timeToWakeUpThread = realTime.getStartTime() + realTime.getRunTime() + deltaTimeToTick;
			std::cout << "Sleeping for " << std::chrono::duration<double>(deltaTimeToTick).count() << std::endl;
			std::this_thread::sleep_until(timeToWakeUpThread);
			continue;
		}

	
		// If core or physics requires update, update UI and input
		if (coreShouldUpdate || physicsShouldUpdate) {
			resetInput();
			processInput();

			// Init components (enable, disable, start)
			initializeLogics();
		}

		// Update physics if it requires update
		if (physicsShouldUpdate) {
			// Update physics engine
			prePhysicsUpdate();
			updatePhysics(physicsTime.getScaledDeltaTimeF());
			postPhysicsUpdate();
		}

		// Update core if it requires update
		if (coreShouldUpdate) {
			// Update core engine
			preUpdate();
			update();
			postUpdate();

			// Render
			preRender();
			render();
			postRender();
		}

		// Collect garbage
		s_collectGarbage();

		// Process termination
		if (shouldStop) {
			bool callbackIsSet = static_cast<bool>(onStopCallback);
			if (callbackIsSet)
				shouldStop = onStopCallback();

			if (!shouldStop)
				continue;

			if (destroyGameObjectsOnStop)
				GameObject::s_destroyGameObjectsImmediately();
		}

		// Process pause
		if (shouldPause) {
			bool processed = false;
			do {
				bool callbackIsSet = static_cast<bool>(onPauseCallback);
				if (callbackIsSet)
					processed = onPauseCallback();
			} while (!processed);

			shouldPause = false;
		}
	}

	// Update engine state
	state = EngineState::IDLE;
}
void it::InTimeEngine::step() {
	// Update engine state
	state = EngineState::STEPPING;

	// Update time
	realTime.tick();
	physicsTime.tick(physicsTime.tickRate);
	coreTime.tick(physicsTime.tickRate);

	// If core or physics requires update, update UI and input
	{
		resetInput();
		processInput();

		// Init components (enable, disable, start)
		initializeLogics();
	}

	// Update physics if it requires update
	{
		// Update physics engine
		prePhysicsUpdate();
		updatePhysics(physicsTime.getScaledDeltaTimeF());
		postPhysicsUpdate();
	}

	// Update core if it requires update
	{
		// Update core engine
		preUpdate();
		update();
		postUpdate();

		// Render
		preRender();
		render();
		postRender();
	}

	// Collect garbage
	s_collectGarbage();

	// Process termination
	if (shouldStop) {
		bool callbackIsSet = static_cast<bool>(onStopCallback);
		if (callbackIsSet)
			shouldStop = onStopCallback();

		if (!shouldStop)
			return;

		if (destroyGameObjectsOnStop)
			GameObject::s_destroyGameObjectsImmediately();
	}

	// Process pause
	if (shouldPause) {
		bool processed = false;
		do {
			bool callbackIsSet = static_cast<bool>(onPauseCallback);
			if (callbackIsSet)
				processed = onPauseCallback();
		} while (!processed);

		shouldPause = false;
	}


	// Update engine state
	state = EngineState::IDLE;
}

void it::InTimeEngine::pause() {
	shouldPause = true;
}
void it::InTimeEngine::stop() {
	shouldStop = true;
}

// Object | private
void it::InTimeEngine::initializeLogics() {
	for (InitializeEvent* iComponentInit : InitializeEvent::s_initializeEventList)
		iComponentInit->onInit();

	InitializeEvent::s_initializeEventList.clear();
}

void it::InTimeEngine::resetInput() {
	#if defined(GLFW_ENGINE)
	glfw::GLFWEngine* engine = glfw::GLFWEngine::getSingleton();
	if (engine != nullptr) {
		engine->resetInput();
	}
	#endif
}
void it::InTimeEngine::processInput() {
	#if defined(GLFW_ENGINE)
	glfw::GLFWEngine* glfwEngine = glfw::GLFWEngine::getSingleton();
	if (glfwEngine != nullptr) {
		glfwEngine->processInput();
	}
	#endif
}

void it::InTimeEngine::preUpdate() {
	for (UpdateEvent* iUpdate : UpdateEvent::s_updateEventList)
		iUpdate->onPreUpdate();
}
void it::InTimeEngine::update() {
	Transform::s_updateGPUTransform();
}
void it::InTimeEngine::postUpdate() {
	for (UpdateEvent* iUpdate : UpdateEvent::s_updateEventList)
		iUpdate->onPostUpdate();
}

void it::InTimeEngine::prePhysicsUpdate() {
	for (PhysicsUpdateEvent2D* iPhysicsUpdate : PhysicsUpdateEvent2D::s_physics2DTransformUpdateList)
		iPhysicsUpdate->onPrePhysicsUpdate2D();
}
void it::InTimeEngine::updatePhysics(float timeStep) {
	#if defined(BOX2D_ENGINE)
	physicsEngine2D.update(timeStep);

	for (RigidBody2D* rigidBody2D : RigidBody2D::s_rigidBodyList) {
		b2BodyId rigidBodyId = rigidBody2D->getId();
		b2Vec2 position2D = b2Body_GetPosition(rigidBodyId);
		float rotation2D = b2Rot_GetAngle(b2Body_GetRotation(rigidBodyId));

		GameObject& gameObject = rigidBody2D->getGameObject();
		Transform& transform = gameObject.transform;

		glm::vec3 position = transform.getGlobalPosition();
		glm::vec3 rotation = transform.getGlobalRotation();
		position.x = position2D.x;
		position.y = position2D.y;
		rotation.z = rotation2D;

		//transform.position = transform.toLocalPosition(position);
		//transform.orientation = transform.toLocalOrientation(glm::quat(rotation));

		transform.position = position;
		transform.orientation = glm::quat(rotation);

		gameObject.transform.hintGlobalMatrixUpdate();
		gameObject.transform.hintGPUUpdate();
	}
	#endif
}
void it::InTimeEngine::postPhysicsUpdate() {
	for (PhysicsUpdateEvent2D* iPhysicsUpdate : PhysicsUpdateEvent2D::s_physics2DTransformUpdateList)
		iPhysicsUpdate->onPostPhysicsUpdate2D();
}

void it::InTimeEngine::preRender() {
	for (RenderEvent* iRender : RenderEvent::s_renderList)
		iRender->onPreRender();
}
void it::InTimeEngine::render() {
	#if defined(VULKAN_ENGINE)

	#if defined(DEAR_IMGUI)
	// Setup ImGui for next frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	#endif

	Vulkan::VulkanEngine* vulkanEngine = Vulkan::VulkanEngine::s_getSingleton();
	if (vulkanEngine != nullptr) {
		vulkanEngine->render();
	}

	// Render UI
	for (RenderUIEvent* iRenderUI : RenderUIEvent::s_renderUIList)
		iRenderUI->render();

	#if defined(DEAR_IMGUI)
	// Render Dear ImGUI UI
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	#endif

	#endif

	#if defined(OPENGL_ENGINE)
	gl::GLEngine* glEngine = gl::GLEngine::s_getSingleton();
	if (glEngine == nullptr)
		return;

	glEngine->time.time = this->coreTime.getTimeF();
	glEngine->time.deltaTime = this->coreTime.getDeltaTimeF();
	glEngine->time.scaledTime = this->coreTime.getScaledTimeF();
	glEngine->time.scaledDeltaTime = this->coreTime.getScaledDeltaTimeF();

	Camera2D::s_updateTransforms();
	glEngine->render();

	UIEngine* uiEngine = UIEngine::s_getSingleton();
	assert(uiEngine != nullptr);
	uiEngine->render();

	glEngine->swapBuffers();
	#endif
}
void it::InTimeEngine::postRender() {
	for (RenderEvent* iRender : RenderEvent::s_renderList)
		iRender->onPostRender();
}

void it::InTimeEngine::updateEditor() {
	editor.update();
}

void it::InTimeEngine::s_collectGarbage() {
	// Note: Do not change order of garbage collection. Components must be collected first to keep data integrity.
	Component::s_collectGarbage();
	GameObject::s_collectGarbage();
}

/*
#include "InTimeEngine.h"

  // Dependencies | std
#include <thread>

// Dependencies | physics_engine_2d
#include "physics_engine_2d/RigidBody2D.h"

// class InTimeEngine

// Static | private

// Properties
it::InTimeEngine* it::InTimeEngine::s_singleton = nullptr;
bool it::InTimeEngine::s_initialized = false;

// Static | public

// Getters
it::InTimeEngine* it::InTimeEngine::s_getSingleton() {
	return s_singleton;
}

// Object | public

// Constructor / Destructor
it::InTimeEngine::InTimeEngine(const std::filesystem::path& applicationDirectoryPath) {
	if (s_singleton == nullptr)
		s_singleton = this;
}
it::InTimeEngine::~InTimeEngine() {
	if (s_singleton != nullptr)
		s_singleton = nullptr;

	if (destroyGameObjectsOnDelete)
		GameObject::s_destroyGameObjectsImmediately();
}

// Getters
bool it::InTimeEngine::getShouldPause() const {
	return shouldPause;
}
bool it::InTimeEngine::getShouldStop() const {
	return shouldStop;
}

// Functions
void it::InTimeEngine::run() {
	// Set up time
	realTime.start();
	time.reset(realTime.getRunTime());
	physicsTime.reset(realTime.getRunTime());

	std::chrono::nanoseconds lastPhysicsTickTime = realTime.getRunTime();
	std::chrono::nanoseconds lastTickTime = realTime.getRunTime();

	// Engine / game loop
	while (!shouldStop) {
		// Update real time / run time. It's necessary for physics and core time to work
		realTime.tick();

		std::chrono::nanoseconds physicsTickDeltaTime = realTime.getRunTime() - lastPhysicsTickTime;
		std::chrono::nanoseconds tickDeltaTime = realTime.getRunTime() - lastTickTime;

		std::chrono::steady_clock::time_point nextPhysicsUpdateTime = physicsTime.nextTimeToTick(realTime.getLastTickTime());
		std::chrono::steady_clock::time_point nextUpdateUpdateTime = time.nextTimeToTick(realTime.getLastTickTime());
		std::chrono::steady_clock::time_point nextTimeToTick = nextPhysicsUpdateTime > nextUpdateUpdateTime ? nextPhysicsUpdateTime : nextUpdateUpdateTime;

		if (nextTimeToTick < realTime.getLastTickTime()) {
			std::chrono::nanoseconds threadSleepTime = physicsTime.nextTimeToTick(realTime.getLastTickTime()) - realTime.getLastTickTime();
			std::cout << "Sleeping for: " << threadSleepTime << std::endl;
			std::this_thread::sleep_until(nextTimeToTick);
			continue;
		}

		bool physicsUpdateDue = physicsTime.tick(physicsTickDeltaTime);
		bool updateDue = time.tick(tickDeltaTime);

		if (physicsUpdateDue) {
			lastPhysicsTickTime += physicsTime.tickRate;
		}
		if (updateDue) {
			if (time.fixed)
				lastTickTime += time.tickRate;
			else
				lastTickTime += tickDeltaTime;
		}

		// If core or physics requires update, update UI and input
		if (updateDue || physicsUpdateDue) {
			resetInput();
			processInput();

			// Init components (enable, disable, start)
			initializeLogics();
		}

		// Update physics if it requires update
		if (physicsUpdateDue) {
			do {
				std::cout << "Physics update:" << std::endl;

				// Update physics engine
				prePhysicsUpdate();
				updatePhysics(physicsTime.getScaledDeltaTimeF());
				postPhysicsUpdate();

				physicsTime.tick(physicsTickDeltaTime);
				lastPhysicsTickTime += physicsTime.tickRate;
				physicsTickDeltaTime = realTime.getRunTime() - lastPhysicsTickTime;
				physicsUpdateDue = physicsTime.shouldTick(physicsTickDeltaTime);
			} while (physicsUpdateDue);
		}
		//if (physicsUpdateDue) {
		//	do {
		//		std::cout << "Physics update:" << std::endl;

		//		// Update physics engine
		//		prePhysicsUpdate();
		//		updatePhysics(physicsTime.getScaledDeltaTimeF());
		//		postPhysicsUpdate();
		//	} while (physicsTime.tick(physics));
		//}

		// Update core if it requires update
		if (updateDue) {
			std::cout << "Update" << std::endl;

			// Update core engine
			preUpdate();
			update();
			postUpdate();

			// Render
			preRender();
			render();
			postRender();
		}

		// Collect garbage
		s_collectGarbage();

		// Process termination
		if (shouldStop) {
			bool callbackIsSet = static_cast<bool>(onStopCallback);
			if (callbackIsSet)
				shouldStop = onStopCallback();

			if (!shouldStop)
				continue;

			if (destroyGameObjectsOnStop)
				GameObject::s_destroyGameObjectsImmediately();
		}

		// Process pause
		if (shouldPause) {
			bool processed = false;
			do {
				bool callbackIsSet = static_cast<bool>(onPauseCallback);
				if (callbackIsSet)
					processed = onPauseCallback();
			} while (!processed);

			shouldPause = false;
		}
	}
}

void it::InTimeEngine::pause() {
	shouldPause = true;
}
void it::InTimeEngine::stop() {
	shouldStop = true;
}

// Object | private
void it::InTimeEngine::initializeLogics() {
	for (InitializeEvent* iComponentInit : InitializeEvent::s_initializeEventList)
		iComponentInit->onInit();

	InitializeEvent::s_initializeEventList.clear();
}

void it::InTimeEngine::resetInput() {
#if defined(GLFW_ENGINE)
	glfw::GLFWEngine* engine = glfw::GLFWEngine::getSingleton();
	if (engine != nullptr) {
		engine->resetInput();
	}
#endif
}
void it::InTimeEngine::processInput() {
#if defined(GLFW_ENGINE)
	glfw::GLFWEngine* glfwEngine = glfw::GLFWEngine::getSingleton();
	if (glfwEngine != nullptr) {
		glfwEngine->processInput();
	}
#endif
}

void it::InTimeEngine::preUpdate() {
	for (UpdateEvent* iUpdate : UpdateEvent::s_updateEventList)
		iUpdate->onPreUpdate();
}
void it::InTimeEngine::update() {
	Transform::s_updateGPUTransform();
}
void it::InTimeEngine::postUpdate() {
	for (UpdateEvent* iUpdate : UpdateEvent::s_updateEventList)
		iUpdate->onPostUpdate();
}

void it::InTimeEngine::prePhysicsUpdate() {
	for (PhysicsUpdateEvent2D* iPhysicsUpdate : PhysicsUpdateEvent2D::s_physics2DTransformUpdateList)
		iPhysicsUpdate->onPrePhysicsUpdate2D();
}
void it::InTimeEngine::updatePhysics(float timeStep) {
#if defined(BOX2D_ENGINE)
	physicsEngine2D.update(timeStep);

	for (RigidBody2D* rigidBody2D : RigidBody2D::s_rigidBodyList) {
		b2BodyId rigidBodyId = rigidBody2D->getId();
		b2Vec2 position2D = b2Body_GetPosition(rigidBodyId);
		float rotation2D = b2Rot_GetAngle(b2Body_GetRotation(rigidBodyId));

		GameObject& gameObject = rigidBody2D->getGameObject();
		Transform& transform = gameObject.transform;

		glm::vec3 position = transform.getGlobalPosition();
		glm::vec3 rotation = transform.getGlobalRotation();
		position.x = position2D.x;
		position.y = position2D.y;
		rotation.z = rotation2D;

		//transform.position = transform.toLocalPosition(position);
		//transform.orientation = transform.toLocalOrientation(glm::quat(rotation));

		transform.position = position;
		transform.orientation = glm::quat(rotation);

		gameObject.transform.hintGlobalMatrixUpdate();
		gameObject.transform.hintGPUUpdate();
	}
#endif
}
void it::InTimeEngine::postPhysicsUpdate() {
	for (PhysicsUpdateEvent2D* iPhysicsUpdate : PhysicsUpdateEvent2D::s_physics2DTransformUpdateList)
		iPhysicsUpdate->onPostPhysicsUpdate2D();
}

void it::InTimeEngine::preRender() {
	for (RenderEvent* iRender : RenderEvent::s_renderList)
		iRender->onPreRender();
}
void it::InTimeEngine::render() {
#if defined(VULKAN_ENGINE)

#if defined(DEAR_IMGUI)
	// Setup ImGui for next frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
#endif

	Vulkan::VulkanEngine* vulkanEngine = Vulkan::VulkanEngine::s_getSingleton();
	if (vulkanEngine != nullptr) {
		vulkanEngine->render();
	}

	// Render UI
	for (RenderUIEvent* iRenderUI : RenderUIEvent::s_renderUIList)
		iRenderUI->render();

#if defined(DEAR_IMGUI)
	// Render Dear ImGUI UI
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

#endif

#if defined(OPENGL_ENGINE)
	gl::GLEngine* glEngine = gl::GLEngine::s_getSingleton();
	if (glEngine == nullptr)
		return;

	glEngine->time.time = this->time.getTimeF();
	glEngine->time.deltaTime = this->time.getDeltaTimeF();
	glEngine->time.scaledTime = this->time.getScaledTimeF();
	glEngine->time.scaledDeltaTime = this->time.getScaledDeltaTimeF();

	Camera2D::s_updateTransforms();
	glEngine->render();

#if defined(IMGUI_ENGINE)
	UIEngine* uiEngine = UIEngine::s_getSingleton();
	assert(uiEngine != nullptr);
	uiEngine->render();
#endif

	glEngine->swapBuffers();
#endif
}
void it::InTimeEngine::postRender() {
	for (RenderEvent* iRender : RenderEvent::s_renderList)
		iRender->onPostRender();
}


void it::InTimeEngine::s_collectGarbage() {
	// Note: Do not change order of garbage collection. Components must be collected first to keep data integrity.
	Component::s_collectGarbage();
	GameObject::s_collectGarbage();
}

*/