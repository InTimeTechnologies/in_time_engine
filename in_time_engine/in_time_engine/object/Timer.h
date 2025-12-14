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
 * File: Timer.h
 * Author: Christopher Barrios Agosto
 * Created on: 25DEC2024
 *
 * Description:
 *  Timer class that uses the In Time Engine's core time.
 *  Set a function to call when time is up.
 *  When running is set to true, it starts ticking down when engine is running.
 *****************************************************************************/

#pragma once

// Dependencies | InTimeEngine
#include "in_time_engine/InTimeEngine.h"

namespace it {
	class Timer : public UpdateEvent {
		// Static
		private:
			// Properties
			static std::chrono::nanoseconds defaultTimeLeft;

		// Object
		private:
			// Properties
			bool running = false;
			std::chrono::nanoseconds timeLeft = defaultTimeLeft;

		public:
			// Properties
			std::chrono::nanoseconds initialTimeLeft = defaultTimeLeft;
			std::function<void()> function = std::function<void()>();

			// Constructor / Destructor
			Timer() = default;
			Timer(std::chrono::nanoseconds time) : timeLeft(time), initialTimeLeft(time) {}
			~Timer() = default;

			// Events
			void onPreUpdate() override {
				if (!running)
					return;

				timeLeft -= InTimeEngine::s_getSingleton()->coreTime.getDeltaTime();
				if (timeLeft <= std::chrono::nanoseconds(0)) {
					bool functionIsSet = static_cast<bool>(function);
					if (functionIsSet)
						function();

					running = false;
				}
			}
			void onPostUpdate() override {
				// Ignored
			}

			// Functions
			void start() {
				running = true;
			}
			void stop() {
				running = false;
			}
			void reset() {
				timeLeft = initialTimeLeft;
			}
	};
}
