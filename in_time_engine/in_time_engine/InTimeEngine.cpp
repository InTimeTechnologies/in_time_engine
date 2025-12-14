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
it::InTimeEngine::InTimeEngine() {
	if (s_singleton == nullptr)
		s_singleton = this;

	componentRegistry.add(typeid(EmptyComponent), 1, "Empty Component", []() { return new EmptyComponent(); });
	componentRegistry.add(typeid(Transformation), 2, "Transformation", []() { return new Transformation(); });
	componentRegistry.add(typeid(PhysicsTransformation), 3, "FixedTransformation", []() { return new PhysicsTransformation(); });

	componentRegistry.add(typeid(RigidBodyB2D), 1000, "Ridig Body B2D", []() { return new RigidBodyB2D(); });

	componentRegistry.add(typeid(GPUTransform), 2000, "GPU Transform", []() { return new GPUTransform(); });
	componentRegistry.add(typeid(Camera2D), 2001, "Camera 2D", []() { return new Camera2D(); });
	componentRegistry.add(typeid(Camera3D), 2002, "Camera 3D", []() { return new Camera3D(); });
	componentRegistry.add(typeid(GPUPoint), 2003, "GPU Point", []() { return new GPUPoint(); });
	componentRegistry.add(typeid(GPULine), 2004, "GPU Line", []() { return new GPULine(); });
	componentRegistry.add(typeid(GPUMultiLine), 2005, "GPU Multiline", []() { return new GPUMultiLine(); });
	componentRegistry.add(typeid(GPUTriangle), 2006, "GPU Triangle", []() { return new GPUTriangle(); });
	componentRegistry.add(typeid(GPUTriangleStrip), 2007, "GPU Triangle Strip", []() { return new GPUTriangleStrip(); });
	componentRegistry.add(typeid(GPUTriangleFan), 2008, "GPU Triangle Fan", []() { return new GPUTriangleFan(); });

	/* Every component in the registry by default:
		EmptyComponent
		Transformation
		PhysicsTransformation



		GPUTransform
		Camera2D
		Camera3D
		GPUPoint
		GPULine
		GPUMultiLine
		GPUTriangle
		GPUTriangleStrip
		GPUTriangleFan
	*/
}
it::InTimeEngine::~InTimeEngine() {
	gameObjectManager.destroyGameObjectsImmediately();

	if (s_singleton != nullptr)
		s_singleton = nullptr;
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

	std::chrono::nanoseconds lastPhysicsTick = realTime.getRunTime();
	std::chrono::nanoseconds lastCoreTick = realTime.getRunTime();

	// Engine / game loop
	while (!shouldStop) {
		// Update time
		realTime.tick();
		bool physicsShouldUpdate{ false };
		bool coreShouldUpdate{ false };

		physicsShouldUpdate = fixedTime.shouldTick(realTime.getRunTime() - lastPhysicsTick);
		coreShouldUpdate = coreTime.shouldTick(realTime.getRunTime() - lastCoreTick);

		if (physicsShouldUpdate) {
			fixedTime.tick();
			lastPhysicsTick += fixedTime.tickRate;
		}
		if (coreShouldUpdate) {
			std::chrono::nanoseconds deltaTimeSinceLastCoreUpdate = realTime.getRunTime() - lastCoreTick;
			coreTime.tick(deltaTimeSinceLastCoreUpdate);
			if (coreTime.fixed)
				lastCoreTick += coreTime.tickRate;
			else
				lastCoreTick = realTime.getRunTime();
		}

		if (!physicsShouldUpdate && !coreShouldUpdate) {
			continue;

			//// Sleep thread until next time to update
			//std::chrono::steady_clock::time_point fixedTimeNextTimePointToTick = fixedTime.nextTimePointToTick(realTime.getLastTickTime());
			//std::chrono::steady_clock::time_point coreTimeNextTimePointToTick = coreTime.nextTimePointToTick(realTime.getLastTickTime());
			//std::chrono::steady_clock::time_point timeToWeakUpThread = fixedTimeNextTimePointToTick < coreTimeNextTimePointToTick ? fixedTimeNextTimePointToTick : coreTimeNextTimePointToTick;
			//
			//// Try to busy wait if the wait is to short
			//std::chrono::nanoseconds deltaTimeToNextTick = timeToWeakUpThread - realTime.getStartTime();
			//if (deltaTimeToNextTick < std::chrono::microseconds(200)) {
			//	std::cout << "Performing busy wait until next frame." << std::endl;
			//	continue;
			//}

			//std::cout << "Delta time for next update " << deltaTimeToNextTick << std::endl;
			//std::cout << "Sleeping for " << deltaTimeToNextTick << std::endl;
			//std::this_thread::sleep_until(timeToWeakUpThread);
			//continue;
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
			updatePhysics(fixedTime.getScaledDeltaTimeF());
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
		collectGarbage();

		// Process termination
		if (shouldStop) {
			bool callbackIsSet = static_cast<bool>(onStopCallback);
			if (callbackIsSet)
				shouldStop = onStopCallback();

			if (!shouldStop)
				continue;

			gameObjectManager.destroyGameObjectsImmediately();
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
void it::InTimeEngine::step() {
	// Update time
	fixedTime.tick(fixedTime.tickRate);
	coreTime.tick(fixedTime.tickRate);

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
		updatePhysics(fixedTime.getScaledDeltaTimeF());
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
	collectGarbage();

	// Process termination
	if (shouldStop) {
		bool callbackIsSet = static_cast<bool>(onStopCallback);
		if (callbackIsSet)
			shouldStop = onStopCallback();

		if (!shouldStop)
			return;

		gameObjectManager.destroyGameObjectsImmediately();
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
	glfwEngine.resetInput();
}
void it::InTimeEngine::processInput() {
	glfwEngine.processInput();
}

void it::InTimeEngine::preUpdate() {
	for (UpdateEvent* iUpdate : UpdateEvent::s_updateEventList)
		iUpdate->onPreUpdate();
}
void it::InTimeEngine::update() {
	
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
	physicsEngine2D.update(timeStep);

	// Copy events game objects' transforms (only copies dynamic bodies that moved)
	b2BodyEvents events = b2World_GetBodyEvents(physicsEngine2D.getWorldId());
	for (int i = 0; i < events.moveCount; i++) {
		// Copy event data
		const b2BodyMoveEvent* event = events.moveEvents + i;
		RigidBodyB2D* rigidBodyB2d = reinterpret_cast<RigidBodyB2D*>(event->userData);
		GameObject* gameObject = rigidBodyB2d->getGameObject();
		if (gameObject == nullptr)
			continue;

		b2Vec2 position = b2Body_GetPosition(event->bodyId);
		float angle = b2Rot_GetAngle(b2Body_GetRotation(event->bodyId));

		// Copy data to game object
		glm::vec3 rotation = gameObject->transform.getGlobalRotation();
		rotation.z = angle;

		gameObject->transform.position.x = position.x;
		gameObject->transform.position.y = position.y;
		gameObject->transform.orientation = glm::quat(rotation);

		// Mark transform as dirty
		gameObject->transform.makeDirty();
	}

	// Copy every rigid body to game objecs's transform (inefficient for physics simulation)
	//for (RigidBody2D* rigidBody2D : RigidBody2D::s_rigidBodyList) {
	//	b2BodyId rigidBodyId = rigidBody2D->getId();
	//	b2Vec2 position2D = b2Body_GetPosition(rigidBodyId);
	//	float rotation2D = b2Rot_GetAngle(b2Body_GetRotation(rigidBodyId));

	//	GameObject& gameObject = rigidBody2D->getGameObject();
	//	Transform& transform = gameObject.transform;

	//	glm::vec3 position = transform.getGlobalPosition();
	//	glm::vec3 rotation = transform.getGlobalRotation();
	//	position.x = position2D.x;
	//	position.y = position2D.y;
	//	rotation.z = rotation2D;

	//	transform.position = position;
	//	transform.orientation = glm::quat(rotation);

	//	gameObject.transform.hintGlobalMatrixUpdate();
	//	gameObject.transform.hintGPUUpdate();
	//}
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

	gl::Engine* glEngine = gl::Engine::s_getSingleton();
	if (glEngine == nullptr)
		return;

	glEngine->time.time = this->coreTime.getTimeF();
	glEngine->time.deltaTime = this->coreTime.getDeltaTimeF();
	glEngine->time.scaledTime = this->coreTime.getScaledTimeF();
	glEngine->time.scaledDeltaTime = this->coreTime.getScaledDeltaTimeF();

	Camera2D::s_updateTransforms();
	GPUTransform::s_synch();
	glEngine->render();
	glEngine->swapBuffers();
}
void it::InTimeEngine::postRender() {
	for (RenderEvent* iRender : RenderEvent::s_renderList)
		iRender->onPostRender();
}

void it::InTimeEngine::collectGarbage() {
	// Note: Do not change order of garbage collection. Components must be collected first to keep data integrity.
	gameObjectManager.collectGarbage();
}
