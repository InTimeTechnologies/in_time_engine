#pragma once

// Dependencies | std
#include <chrono>

namespace it {
	// Functions
	float durationToFloat(const std::chrono::steady_clock::duration duration);
	double durationToDouble(const std::chrono::steady_clock::duration duration);

	class RealTime {
		// Object
		private:
			// Properties
			std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
			std::chrono::steady_clock::time_point tickTime = startTime;
			std::chrono::nanoseconds runTime = std::chrono::nanoseconds(0LL);
			std::chrono::nanoseconds deltaTime = std::chrono::nanoseconds(0LL);

		public:
			// Constructor / Destructor
			RealTime() = default;
			~RealTime() = default;

			// Getters
			std::chrono::steady_clock::time_point getStartTime() const;
			std::chrono::steady_clock::time_point getLastTickTime() const;
			std::chrono::nanoseconds getRunTime() const;
			std::chrono::nanoseconds getDeltaTime() const;

			// Functions
			void start();
			void tick();
			std::chrono::steady_clock::time_point now();
	};

	class Time {
		// Object
		private:
			// Properties
			std::chrono::nanoseconds time = std::chrono::nanoseconds(0);
			std::chrono::nanoseconds deltaTime = std::chrono::nanoseconds(0);
			std::chrono::nanoseconds scaledTime = std::chrono::nanoseconds(0);
			std::chrono::nanoseconds scaledDeltaTime = std::chrono::nanoseconds(0);

		public:
			// Properties
			double scale = 1.0;
			bool fixed = true;
			std::chrono::nanoseconds tickRate = std::chrono::nanoseconds(16666666);

			// Constructor / Destructor
			Time() = default;
			Time(bool fixed, const std::chrono::nanoseconds tickRate);
			Time(bool fixed, float tickRate);
			Time(bool fixed, double tickRate);
			Time(const Time& time) = default;
			Time(Time&& time) = default;
			~Time() = default;

			// Operators | assignment
			Time& operator=(const Time& time) = default;
			Time& operator=(Time&& time) = default;

			// Getters
			std::chrono::nanoseconds getTime() const;
			std::chrono::nanoseconds getDeltaTime() const;
			std::chrono::nanoseconds getScaledTime() const;
			std::chrono::nanoseconds getScaledDeltaTime() const;

			float getTimeF() const;
			float getDeltaTimeF() const;
			float getScaledTimeF() const;
			float getScaledDeltaTimeF() const;

			double getTimeD() const;
			double getDeltaTimeD() const;
			double getScaledTimeD() const;
			double getScaledDeltaTimeD() const;

			// Functions
			void reset();
			void reset(const std::chrono::nanoseconds newTime);
			void normalize(const std::chrono::nanoseconds minimumTime);
			void forceTick(const std::chrono::nanoseconds realDeltaTime);
			bool tick(const std::chrono::nanoseconds realDeltaTime);
			bool shouldTick(const std::chrono::nanoseconds realDeltaTime) const;
			std::chrono::steady_clock::time_point nextTimeToTick(const std::chrono::steady_clock::time_point realCurrentTime) const;
	};
}
