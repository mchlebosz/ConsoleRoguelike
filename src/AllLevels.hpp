#pragma once

#include <fstream>
#include <iostream>
#include <vector>

#include "Level.h"

std::vector<Level> initLevels() {
	std::vector<Level> allLevels;

	/*
	Working Chars
	 🚪  🥰 🥴 🤢 🤮  😈 👿 💀 👽 👻 🤖 🦂 🍪 🍩 🍭 🍦 🍔 🌟

	*/
	// add levels here

	allLevels.push_back(Level(
		std::vector<std::u32string> {
			U"█████████████████████████████████████████████████",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"█████████████████████████    ██                ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"█████████████████████████████████████████████████" },
		std::make_pair(4, 2), std::make_pair(4, 8),
		std::vector<Enemy*> { new Enemy(0, U'😈', 40, 3, 5, 1),
							  new Enemy(1, U'💀', 10, 10, 5, 1),
							  new Enemy(2, U'👻', 30, 12, 5, 1) }));

	allLevels.push_back(Level(
		std::vector<std::u32string> {
			U"█████████████████████████████████████",
			U"██           ████████████████████████",
			U"██                                 ██",
			U"██           ████████              ██",
			U"██           ██    ██              ██",
			U"██           ██    ██              ██",
			U"███████████████    ██     X        ██",
			U"██   ◎       ██    ██              ██",
			U"██           ██    ██              ██",
			U"██           ████████              ██",
			U"██                                 ██",
			U"█████████████████████████████████████" },
		std::make_pair(4, 2), std::make_pair(4, 8),
		std::vector<Enemy*> { new Enemy(0, U'😈', 7, 6, 5, 1),
							  new Enemy(1, U'💀', 3, 5, 5, 1),
							  new Enemy(2, U'👻', 10, 12, 5, 1) }));

	allLevels.push_back(Level(
		std::vector<std::u32string> {
			U"█████████████████████████████████████",
			U"██           ████████████████████████",
			U"██                                 ██",
			U"██           ████████              ██",
			U"██           ██    ██              ██",
			U"██           ██    ██ W            ██",
			U"███████████████    ██              ██",
			U"██   ◎       ██    ██              ██",
			U"██           ██    ██              ██",
			U"██           ████████              ██",
			U"██                                 ██",
			U"█████████████████████████████████████" },
		std::make_pair(4, 2), std::make_pair(4, 8),
		std::vector<Enemy*> { new Enemy(0, U'😈', 10, 20, 5, 1),
							  new Enemy(1, U'💀', 10, 6, 5, 1),
							  new Enemy(2, U'👻', 10, 30, 5, 1) }));

	return allLevels;
}
