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

#pragma once

// Dependencies | std
#include <functional>
#include <vector>
#include <string>
#include <filesystem>

// Dependencies | in_time_engine
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "ComponentRegistry.h"
#include "Transform.h"
#include "Component.h"
#include "Scene.h"
#include "SceneManager.h"
#include "CustomComponentSerializer.h"
#include "Time.h"
#include "EngineEvents.h"
#include "EngineState.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "IPlatformBackend.h"

// Dependencies | window
#include "window/WindowManager.h"

// Dependencies | input
#include "input/mouse_keyboard/MouseKeyboardInput.h"
#include "input/joystick/JoystickInput.h"

// Dependencies | box2d_engine
#include "physics_engine_2d/PhysicsEngine2D.h"

// Namespace
namespace it {
	// Forward declarations
	class InTimeEditor;

	class InTimeEngine {
		// Friends
		friend class InTimeEditor;

		// Static
		private:
			// Properties
			static InTimeEngine* s_singleton;
			static bool s_initialized;

		public:
			// Getters
			static InTimeEngine* s_getSingleton();

		// Object
		private:
			// Properties
			bool shouldPause{ false };
			bool shouldStop{ false };

		public:
			// Inner engines
			PhysicsEngineB2D physicsEngine2D;

			// Properties
			RealTime realTime{};
			Time coreTime{ false, std::chrono::nanoseconds(8333333 /* 120 FPS */ )};
			FixedTime fixedTime{ 1.0, std::chrono::nanoseconds(16666666LL /* 60 FPS */) };
			ResourceManager resourceManager{};
			GameObjectManager gameObjectManager{};
			ComponentRegistry componentRegistry{};
			SceneManager sceneManager{};

			MouseKeyboardInput mouseKeyboardInput{};
			JoystickInput joystickInput{};

			// Callbacks
			std::function<bool()> onPauseCallback{ std::function<bool()>() };
			std::function<bool()> onStopCallback{ std::function<bool()>() };

			// Flags
			bool destroyGameObjectsOnStop{ false };
			bool destroyGameObjectsOnDelete{ true };

			// Properties | window
			WindowManager windowManager{};

			// Properties | backends
			IPlatformBackend* inputEventBackend{ nullptr };

			// Constructor / Destructor
			InTimeEngine();
			~InTimeEngine();

			// Getters
			bool getShouldPause() const;
			bool getShouldStop() const;

			// Functions
			void run();
			void step();

			void pause();
			void stop();

		private:
			// Functions
			void initializeLogics();

			void prePhysicsUpdate();
			void updatePhysics(float timeStep);
			void postPhysicsUpdate();

			void preUpdate();
			void update();
			void postUpdate();

			void preRender();
			void render();
			void postRender();

			void collectGarbage();
	};
}

// Dependencies | in_time_engine | components
#include "component/EmptyComponent.h"
#include "component/Transformation.h"
#include "component/PhysicsTransformation.h"

// Dependencies | in_time_engine | object
#include "object/Stopwatch.h"
#include "object/Timer.h"
#include "object/FrameCounter.h"
#include "object/KeyPressPrinter.h"
