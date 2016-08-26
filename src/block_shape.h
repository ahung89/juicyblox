#pragma once

#include <point.h>
#include <vector>
#include <util/color.h>

struct BlockShape {
	Point origin_offset;
	std::vector<Point> offsets;
	Color color;
}; // Don't forget that semicolon