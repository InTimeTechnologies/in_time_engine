#pragma once

namespace gl {
	struct Time {
		// Properties
		float time = 0.0f;
		float deltaTime = 0.0f;
		float scaledTime = 0.0f;
		float scaledDeltaTime = 0.0f;

		// Constructor / Destructor
		Time() = default;
		Time(const Time& time) = default;
		Time(Time&& time) = default;
		~Time() = default;

		// Operators | assignment
		Time& operator=(const Time& time) = default;
		Time& operator=(Time&& time) = default;
	};
}
