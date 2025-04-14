#pragma once
#include <vector>
#include "Vec2.h"

struct Path {
	std::vector<Vec2> nodes;
};

float clamp(float n, float lower, float upper);