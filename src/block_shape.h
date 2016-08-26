#pragma once

#include <point.h>
#include <vector>

struct BlockShape {
	Point origin_offset;
	std::vector<Point> offsets;
}; // Don't forget that semicolon