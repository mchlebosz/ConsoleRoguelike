#pragma once

#include <iostream>
#include <vector>

#include "Level.h"

std::vector<Level> initLevels() {
	std::vector<Level> allLevels;
	allLevels.push_back(Level(
		std::vector<std::u32string> {
			U"█████████████████████████████████████",
			U"██           ████████████████████████",
			U"██                                 ██",
			U"██           ████████              ██",
			U"██           ██    ██              ██",
			U"██           ██    ██              ██",
			U"███████████████    ██              ██",
			U"██           ██    ██              ██",
			U"██           ██    ██              ██",
			U"██   ◎       ████████              ██",
			U"██                                 ██",
			U"█████████████████████████████████████" },
		std::make_pair(2, 2)));

	allLevels.push_back(Level(
		std::vector<std::u32string> {
			U"█████████████████████████████████████",
			U"██           ████████████████████████",
			U"██                                 ██",
			U"██           ████████              ██",
			U"██           ██    ██              ██",
			U"██           ██    ██              ██",
			U"███████████████    ██              ██",
			U"██   ◎       ██    ██              ██",
			U"██           ██    ██              ██",
			U"██           ████████              ██",
			U"██                                 ██",
			U"█████████████████████████████████████" },
		std::make_pair(2, 2)));

	return allLevels;
}
