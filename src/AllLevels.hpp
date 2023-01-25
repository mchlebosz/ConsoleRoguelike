#pragma once

#include <fstream>
#include <iostream>
#include <vector>

#include "Level.h"

std::vector<Level> loadLevels() {
	// load levels from file and return as vector of Level objects

	std::vector<Level> allLevels;

	std::ifstream file("./src/levels.txt");

	std::cout << "Loading levels..." << std::endl;
	if (file.is_open()) {
		std::vector<std::u32string> levelMap;
		std::pair<int, int> playerPos;
		// load levels in utf8 format but then save them as utf32
		std::string line;
		while (std::getline(file, line)) {
			if (line == "START") {
				// start of new level
				std::cout << "Loading level..." << std::endl;
				levelMap.clear();
			} else if (line == "END") {
				// end of level
				allLevels.push_back(Level(levelMap, playerPos));
			} else if (line == "PLAYER") {
				// player position
				std::getline(file, line);
				playerPos.first = std::stoi(line);
				std::getline(file, line);
				playerPos.second = std::stoi(line);
			} else {
				// add line to level map
				std::cout << line << std::endl;
				levelMap.push_back(std::u32string(line.begin(), line.end()));
			}
		}
		file.close();
	} else {
		std::cout << "Unable to open file" << std::endl;
	}

	return allLevels;
}

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
			U"███████████████    ██                          ██",
			U"██   ◎                                         ██",
			U"██                                             🚪",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"██                                             ██",
			U"█████████████████████████████████████████████████" },
		std::make_pair(4, 2)));

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
		std::make_pair(4, 2)));

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
		std::make_pair(2, 2)));

	return allLevels;
}
