#pragma once

#include <unordered_map>

enum Color {
	Red, Purple, Green, Yellow, Orange, DarkBlue, LightBlue
};

struct ColorValues {
	int r, g, b;
};

// If this isn't extern you'll get a "multiple definitions" error
extern std::unordered_map<int, ColorValues> ColorMap;