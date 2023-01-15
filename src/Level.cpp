#include "Level.h"

Level::Level() {
	m_tiles            = std::vector<std::u32string>();
	m_startingPosition = std::make_pair(1, 1);
}

Level::Level(std::vector<std::u32string> map,
			 std::pair<int, int> startingPosition) {
	m_tiles            = map;
	m_startingPosition = startingPosition;
}

Level::~Level() {}

// getters
std::vector<std::u32string> Level::getMap() const {
	return m_tiles;
}

std::pair<int, int> Level::getStartingPosition() const {
	return m_startingPosition;
}

// setters

void Level::setMap(std::vector<std::u32string> map) {
	m_tiles = map;
}

void Level::setStartingPosition(std::pair<int, int> startingPosition) {
	m_startingPosition = startingPosition;
}
