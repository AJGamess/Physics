#pragma once
#include <stdlib.h>
#include <algorithm>

inline float randomf() {
	return rand() / (float)RAND_MAX;
}
inline float randomf(float max) {
	return randomf() * max;
}
inline float randomf(float min, float max) {
	if (min > max) std::swap(min, max);
	return min + (randomf() * (max - min));
}
