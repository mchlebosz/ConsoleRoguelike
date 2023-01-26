#include "Level.h"

Level::Level() {
	m_tiles            = std::vector<std::u32string>();
	m_startingPosition = std::make_pair(1, 1);
}

Level::Level(std::vector<std::u32string> map,
			 std::pair<int, int> startingPosition,
			 std::pair<int, int> exitPosition, std::vector<Enemy*> enemies) {
	m_tiles            = map;
	m_startingPosition = startingPosition;
	m_exitPosition     = exitPosition;
	m_enemies          = enemies;
}

// getters
std::vector<std::u32string> Level::getMap() const {
	return m_tiles;
}

std::pair<int, int> Level::getStartingPosition() const {
	return m_startingPosition;
}

std::pair<int, int> Level::getExitPosition() const {
	return m_exitPosition;
}

std::vector<Enemy*> Level::getEnemies() const {
	return m_enemies;
}

// setters

void Level::setMap(std::vector<std::u32string> map) {
	m_tiles = map;
}

void Level::setStartingPosition(std::pair<int, int> startingPosition) {
	m_startingPosition = startingPosition;
}

void Level::setExitPosition(std::pair<int, int> exitPosition) {
	m_exitPosition = exitPosition;
}

void Level::setEnemies(std::vector<Enemy*> enemies) {
	m_enemies = enemies;
}