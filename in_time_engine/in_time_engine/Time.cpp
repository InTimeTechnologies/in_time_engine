#include "Time.h"

namespace it {
	float durationToFloat(const std::chrono::steady_clock::duration duration) {
		return std::chrono::duration<float>(duration).count();
	}
	double durationToDouble(const std::chrono::steady_clock::duration duration) {
		return std::chrono::duration<double>(duration).count();
	}

	// class RealTime

	// Object | public

	// Getters
	std::chrono::steady_clock::time_point RealTime::getStartTime() const {
		return startTime;
	}
	std::chrono::steady_clock::time_point RealTime::getLastTickTime() const {
		return tickTime;
	}
	std::chrono::nanoseconds RealTime::getRunTime() const {
		return runTime;
	}
	std::chrono::nanoseconds RealTime::getDeltaTime() const {
		return deltaTime;
	}

	// Functions
	void RealTime::start() {
		startTime = std::chrono::steady_clock::now();
	}
	void RealTime::tick() {
		std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
		runTime = now - startTime;
		deltaTime = now - tickTime;
		tickTime = now;
	}
	std::chrono::steady_clock::time_point RealTime::now() {
		return std::chrono::steady_clock::now();
	}

	// class FixedTime

	// Object | public

	// Constructor
	FixedTime::FixedTime(double scale, std::chrono::nanoseconds tickRate) : scale(scale), tickRate(tickRate) {

	}

	// Getters
	std::chrono::nanoseconds FixedTime::getTime() const {
		return time;
	}
	std::chrono::nanoseconds FixedTime::getDeltaTime() const {
		return deltaTime;
	}
	std::chrono::nanoseconds FixedTime::getScaledTime() const {
		return scaledTime;
	}
	std::chrono::nanoseconds FixedTime::getScaledDeltaTime() const {
		return scaledDeltaTime;
	}

	float FixedTime::getTimeF() const {
		return std::chrono::duration<float>(time).count();
	}
	float FixedTime::getDeltaTimeF() const {
		return std::chrono::duration<float>(deltaTime).count();
	}
	float FixedTime::getScaledTimeF() const {
		return std::chrono::duration<float>(scaledTime).count();
	}
	float FixedTime::getScaledDeltaTimeF() const {
		return std::chrono::duration<float>(scaledDeltaTime).count();
	}

	double FixedTime::getTimeD() const {
		return std::chrono::duration<double>(time).count();;
	}
	double FixedTime::getDeltaTimeD() const {
		return std::chrono::duration<double>(deltaTime).count();
	}
	double FixedTime::getScaledTimeD() const {
		return std::chrono::duration<double>(scaledTime).count();
	}
	double FixedTime::getScaledDeltaTimeD() const {
		return std::chrono::duration<double>(scaledDeltaTime).count();
	}

	// Functions
	void FixedTime::tick() {
		// Tick to time + tickRate
		deltaTime = tickRate;
		time += tickRate;
		scaledDeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime * scale);
		scaledTime += scaledDeltaTime;
	}
	void FixedTime::tick(const std::chrono::nanoseconds tickRate) {
		// Tick to time + tickRate
		deltaTime = tickRate;
		time += tickRate;
		scaledDeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime * scale);
		scaledTime += scaledDeltaTime;
	}
	void FixedTime::reset() {
		time = std::chrono::nanoseconds(0LL);
		deltaTime = std::chrono::nanoseconds(0LL);
		scaledTime = std::chrono::nanoseconds(0LL);
		scaledDeltaTime = std::chrono::nanoseconds(0LL);
	}
	bool FixedTime::shouldTick(const std::chrono::nanoseconds deltaTime) const {
		return deltaTime >= tickRate ? true : false;
	}
	std::chrono::steady_clock::time_point FixedTime::nextTimePointToTick(const std::chrono::steady_clock::time_point referenceTimePoint) const {
		return referenceTimePoint + tickRate;
	}

	// class Time

	// Object | public

	// Constructor / Destructor
	Time::Time(bool fixed, std::chrono::nanoseconds tickRate) : fixed(fixed), tickRate(tickRate) {

	}
	Time::Time(bool fixed, float tickRate) : fixed(fixed), tickRate(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<float>(tickRate))) {

	}
	Time::Time(bool fixed, double tickRate) : fixed(fixed), tickRate(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(tickRate))) {

	}
	Time::Time(const std::chrono::nanoseconds time, const std::chrono::nanoseconds deltaTime, const std::chrono::nanoseconds scaledTime, const std::chrono::nanoseconds scaledDeltaTime, double scale, bool fixed, const std::chrono::nanoseconds tickRate)
		: time(time), deltaTime(deltaTime), scaledTime(scaledTime), scaledDeltaTime(scaledDeltaTime), scale(scale), fixed(fixed), tickRate(tickRate) {

	}

	// Getters
	std::chrono::nanoseconds Time::getTime() const {
		return time;
	}
	std::chrono::nanoseconds Time::getDeltaTime() const {
		return deltaTime;
	}
	std::chrono::nanoseconds Time::getScaledTime() const {
		return scaledTime;
	}
	std::chrono::nanoseconds Time::getScaledDeltaTime() const {
		return scaledDeltaTime;
	}

	// Setters
	void Time::reset(const std::chrono::nanoseconds time, const std::chrono::nanoseconds deltaTime, const std::chrono::nanoseconds scaledTime, const std::chrono::nanoseconds scaledDeltaTime, double scale, bool fixed, const std::chrono::nanoseconds tickRate) {
		this->time = time;
		this->deltaTime = deltaTime;
		this->scaledTime = scaledTime;
		this->scaledDeltaTime = scaledDeltaTime;
		this->scale = scale;
		this->fixed = fixed;
		this->tickRate = tickRate;
	}

	float Time::getTimeF() const {
		return std::chrono::duration<float>(time).count();
	}
	float Time::getDeltaTimeF() const {
		return std::chrono::duration<float>(deltaTime).count();
	}
	float Time::getScaledTimeF() const {
		return std::chrono::duration<float>(scaledTime).count();
	}
	float Time::getScaledDeltaTimeF() const {
		return std::chrono::duration<float>(scaledDeltaTime).count();
	}

	double Time::getTimeD() const {
		return std::chrono::duration<double>(time).count();;
	}
	double Time::getDeltaTimeD() const {
		return std::chrono::duration<double>(deltaTime).count();
	}
	double Time::getScaledTimeD() const {
		return std::chrono::duration<double>(scaledTime).count();
	}
	double Time::getScaledDeltaTimeD() const {
		return std::chrono::duration<double>(scaledDeltaTime).count();
	}

	// Functions
	void Time::reset() {
		std::chrono::nanoseconds zero = std::chrono::nanoseconds(0);
		time = zero;
		deltaTime = zero;
		scaledTime = zero;
		scaledDeltaTime = zero;
	}
	void Time::reset(const std::chrono::nanoseconds newTime) {
		std::chrono::nanoseconds zero = std::chrono::nanoseconds(0);
		time = newTime;
		deltaTime = zero;
		scaledTime = newTime;
		scaledDeltaTime = zero;
	}
	void Time::normalize(const std::chrono::nanoseconds minimumTime) {
		time = time % minimumTime;
		scaledTime = scaledTime % minimumTime;
	}
	void Time::forceTick(const std::chrono::nanoseconds realDeltaTime) {
		if (fixed) {
			// Tick using tickRate
			time += tickRate;
			deltaTime = tickRate;
			scaledDeltaTime += std::chrono::duration_cast<std::chrono::steady_clock::duration>(deltaTime * scale);
			scaledTime += scaledDeltaTime;
		}
		else {
			// Tick to current real time
			deltaTime = realDeltaTime;
			time += realDeltaTime;
			scaledDeltaTime += std::chrono::duration_cast<std::chrono::steady_clock::duration>(deltaTime * scale);
			scaledTime += scaledDeltaTime;
		}
	}
	bool Time::tick(const std::chrono::nanoseconds realDeltaTime) {
		if (fixed) {
			// Should tick?
			if (!shouldTick(realDeltaTime))
				return false; // Failed to tick

			// Tick to time + tickRate
			deltaTime = tickRate;
			time += tickRate;
			scaledDeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime * scale);
			scaledTime += scaledDeltaTime;
		}
		else {
			// Tick to current real time
			deltaTime = realDeltaTime;
			time += realDeltaTime;
			scaledDeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime * scale);
			scaledTime += scaledDeltaTime;
		}

		return true; // Ticked
	}
	bool Time::shouldTick(const std::chrono::nanoseconds realDeltaTime) const {
		if (fixed) {
			return realDeltaTime >= tickRate ? true : false;
		}
		else {
			return true;
		}
	}
	std::chrono::steady_clock::time_point Time::nextTimePointToTick(const std::chrono::steady_clock::time_point realCurrentTime) const {
		return fixed ? realCurrentTime + tickRate : realCurrentTime;
	}
}
