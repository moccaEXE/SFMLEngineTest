#pragma once
#include <cstdlib>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>

	inline void rand_init() {srand(time(NULL));};
	inline float random(float min, float max) { return (rand() / float(RAND_MAX))*(max - min) + min; }
	inline int random(int min, int max) { return rand() % (max - min + 1) + min; }
