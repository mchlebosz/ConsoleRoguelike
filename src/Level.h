#pragma once
#include <windows.h>

#include <iostream>
#include <string>
#include <vector>

class Level {
public:
	Level();

	Level(std::vector<std::u32string> map,
		  std::pair<int, int> startingPosition);

	~Level();

	// getters
	std::vector<std::u32string> getMap() const;
	std::pair<int, int> getStartingPosition() const;

	// setters
	void setMap(std::vector<std::u32string>);
	void setStartingPosition(std::pair<int, int> startingPosition);

private:
	// variables
	std::vector<std::u32string> m_tiles;

	// pair starting position
	std::pair<int, int> m_startingPosition;
};