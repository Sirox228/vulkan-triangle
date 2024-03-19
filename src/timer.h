#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class timer {
	public:
	timer();
	void reset();
	float elapsed();
	float elapsedMillis();

	private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
};

#endif
