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
 * File: Stopwatch.h
 * Author: Christopher Barrios Agosto
 * Created on: 25DEC2024
 * Updated on: 25DEC2024
 *
 * Description:
 *  Stopwatch class that uses the In Time Engine's core time.
 *  Use the running variable to control whether it ticks or not.
 *****************************************************************************/

#pragma once

// Dependencies | InTimeEngine
#include "../InTimeEngine.h"

namespace it {
	class Stopwatch : public UpdateEvent {
		// Object
		public:
			// Properties
			bool running = false;
			std::chrono::nanoseconds timeElapsed = std::chrono::nanoseconds(0);

			// Constructor / Destructor
			Stopwatch() = default;
			~Stopwatch() = default;

			// Getters
			std::chrono::nanoseconds getTimeElapsed() const {
				return timeElapsed;
			}
			
			// Events
			void onPreUpdate() override {
				if (running)
					timeElapsed += it::InTimeEngine::s_getSingleton()->coreTime.getDeltaTime();
			}
			void onPostUpdate() override {
				// Ignored
			}
	};
}
