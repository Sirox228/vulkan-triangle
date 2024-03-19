#include "timer.h"

timer::timer() {
	reset();
}

void timer::reset() {
	m_Start = std::chrono::high_resolution_clock::now();
}

float timer::elapsed() {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
}

float timer::elapsedMillis() {
	return elapsed() * 1000.0f;
}
