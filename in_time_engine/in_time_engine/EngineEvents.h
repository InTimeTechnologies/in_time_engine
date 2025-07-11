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

#pragma once

// Dependencies | std
#include <list>

namespace it {
	class InitializeEvent {
		// Friends
		friend class InTimeEngine;
 
		// Static
		private:
			// Properties
			static std::list<InitializeEvent*> s_initializeEventList;

			// Functions
			static void s_init();
			static void s_enable();
			static void s_start();

		// Object
		private:
			// Properties
			std::list<InitializeEvent*>::iterator node;

		public:
			// Constructor / Destructor
			InitializeEvent();
			virtual ~InitializeEvent();

			// Events
			virtual void onInit();
			virtual void onEnable();
			virtual void onStart();
			virtual void onDisable();

			// Functions
			void enable(bool enable);
	};

	class UpdateEvent {
		// Friends
		friend class InTimeEngine;

		// Static
		private:
			// Properties
			static std::list<UpdateEvent*> s_updateEventList;

			// Functions
			static void s_preUpdate();
			static void s_updateGPUTransform();
			static void s_postUpdate();

		// Object
		private:
			// Properties
			std::list<UpdateEvent*>::iterator node;

		public:
			// Constructor / Destructor
			UpdateEvent();
			virtual ~UpdateEvent();

			// Events
			virtual void onPreUpdate();
			virtual void onUpdate();
			virtual void onPostUpdate();
	};

	class PhysicsUpdateEvent2D {
		// Friends
		friend class InTimeEngine;

		// Static
		private:
			// Properties
			static std::list<PhysicsUpdateEvent2D*> s_physics2DTransformUpdateList;

		// Object
		private:
			// Properties
			std::list<PhysicsUpdateEvent2D*>::iterator node;

		public:
			// Constructor / Destructor
			PhysicsUpdateEvent2D();
			virtual ~PhysicsUpdateEvent2D();

			// Events
			virtual void onPrePhysicsUpdate2D();
			virtual void onPostPhysicsUpdate2D();
	};

	class PhysicsUpdateEvent3D {
		// Friends
		friend class InTimeEngine;

		// Static
		private:
			// Properties
			static std::list<PhysicsUpdateEvent3D*> s_physics3DTransformUpdateList;

		// Object
		private:
			// Properties
			std::list<PhysicsUpdateEvent3D*>::iterator node;

		public:
			// Constructor / Destructor
			PhysicsUpdateEvent3D();
			virtual ~PhysicsUpdateEvent3D();

			// Events
			virtual void onPrePhysicsUpdate3D();
			virtual void onPostPhysicsUpdate3D();
	};

	class RenderEvent {
		// Friends
		friend class InTimeEngine;

		// Static
		private:
			// Properties
			static std::list<RenderEvent*> s_renderList;

		// Object
		private:
			// Properties
			std::list<RenderEvent*>::iterator node;

		public:
			// Constructor / Destructor
			RenderEvent();
			virtual ~RenderEvent();

			// Events
			virtual void onPreRender();
			virtual void render();
			virtual void onPostRender();
	};

	class RenderUIEvent {
		// Friends
		friend class InTimeEngine;

		// Static
		private:
			// Properties
			static std::list<RenderUIEvent*> s_renderUIList;

		// Object
		private:
			// Properties
			std::list<RenderUIEvent*>::iterator node;

		public:
			// Constructor / Destrctor
			RenderUIEvent();
			virtual ~RenderUIEvent();

			// Events
			virtual void render();
	};
}