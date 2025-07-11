#include "Time.h"

float it::durationToFloat(const std::chrono::steady_clock::duration duration) {
	return std::chrono::duration<float>(duration).count();
}
double it::durationToDouble(const std::chrono::steady_clock::duration duration) {
	return std::chrono::duration<double>(duration).count();
}

// class RealTime

// Object | public

// Getters
std::chrono::steady_clock::time_point it::RealTime::getStartTime() const {
	return startTime;
}
std::chrono::steady_clock::time_point it::RealTime::getLastTickTime() const {
	return tickTime;
}
std::chrono::nanoseconds it::RealTime::getRunTime() const {
	return runTime;
}
std::chrono::nanoseconds it::RealTime::getDeltaTime() const {
	return deltaTime;
}

// Functions
void it::RealTime::start() {
	startTime = std::chrono::steady_clock::now();
}
void it::RealTime::tick() {
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	runTime = now - startTime;
	deltaTime = now - tickTime;
	tickTime = now;
}
std::chrono::steady_clock::time_point it::RealTime::now() {
	return std::chrono::steady_clock::now();
}

// class FixedTime

// Object | public

// Constructor / Destructor
it::Time::Time(bool fixed, std::chrono::nanoseconds tickRate) : fixed(fixed), tickRate(tickRate) {

}
it::Time::Time(bool fixed, float tickRate) : fixed(fixed), tickRate(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<float>(tickRate))) {

}
it::Time::Time(bool fixed, double tickRate) : fixed(fixed), tickRate(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(tickRate))) {

}

// Getters
std::chrono::nanoseconds it::Time::getTime() const {
	return time;
}
std::chrono::nanoseconds it::Time::getDeltaTime() const {
	return deltaTime;
}
std::chrono::nanoseconds it::Time::getScaledTime() const {
	return scaledTime;
}
std::chrono::nanoseconds it::Time::getScaledDeltaTime() const {
	return scaledDeltaTime;
}

float it::Time::getTimeF() const {
	return std::chrono::duration<float>(time).count();
}
float it::Time::getDeltaTimeF() const {
	return std::chrono::duration<float>(deltaTime).count();
}
float it::Time::getScaledTimeF() const {
	return std::chrono::duration<float>(scaledTime).count();
}
float it::Time::getScaledDeltaTimeF() const {
	return std::chrono::duration<float>(scaledDeltaTime).count();
}

double it::Time::getTimeD() const {
	return std::chrono::duration<double>(time).count();;
}
double it::Time::getDeltaTimeD() const {
	return std::chrono::duration<double>(deltaTime).count();
}
double it::Time::getScaledTimeD() const {
	return std::chrono::duration<double>(scaledTime).count();
}
double it::Time::getScaledDeltaTimeD() const {
	return std::chrono::duration<double>(scaledDeltaTime).count();
}

// Functions
void it::Time::reset() {
	std::chrono::nanoseconds zero = std::chrono::nanoseconds(0);
	time = zero;
	deltaTime = zero;
	scaledTime = zero;
	scaledDeltaTime = zero;
}
void it::Time::reset(const std::chrono::nanoseconds newTime) {
	std::chrono::nanoseconds zero = std::chrono::nanoseconds(0);
	time = newTime;
	deltaTime = zero;
	scaledTime = newTime;
	scaledDeltaTime = zero;
}
void it::Time::normalize(const std::chrono::nanoseconds minimumTime) {
	time = time % minimumTime;
	scaledTime = scaledTime % minimumTime;
}
void it::Time::forceTick(const std::chrono::nanoseconds realDeltaTime) {
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
bool it::Time::tick(const std::chrono::nanoseconds realDeltaTime) {
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
		scaledDeltaTime += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime * scale);
		scaledTime += realDeltaTime;
	}

	return true; // Ticked
}
bool it::Time::shouldTick(const std::chrono::nanoseconds realDeltaTime) const {
	if (fixed) {
		return realDeltaTime >= tickRate ? true : false;
	}
	else {
		return true;
	}
}
std::chrono::steady_clock::time_point it::Time::nextTimeToTick(const std::chrono::steady_clock::time_point realCurrentTime) const {
	return fixed ? realCurrentTime + tickRate : realCurrentTime;
}
