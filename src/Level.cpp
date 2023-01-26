#include "Level.h"

Level::Level() {
	m_tiles            = std::vector<std::u32string>();
	m_startingPosition = std::make_pair(1, 1);
}

/**
 *  @brief Construct a new Level object
 *
 * @param map A vector of strings, each string representing a row of the map.
 * @param startingPosition The starting position of the player.
 * @param exitPosition The position of the exit tile.
 * @param enemies A vector of pointers to Enemy objects.
 */
Level::Level(std::vector<std::u32string> map,
			 std::pair<int, int> startingPosition,
			 std::pair<int, int> exitPosition, std::vector<Enemy*> enemies) {
	m_tiles            = map;
	m_startingPosition = startingPosition;
	m_exitPosition     = exitPosition;
	m_enemies          = enemies;
}

// getters
/**
 * Returns a vector of strings containing the map data.
 *
 * @return A vector of strings.
 */
std::vector<std::u32string> Level::getMap() const {
	return m_tiles;
}

/**
 * It returns the starting position of the player
 *
 * @return A pair of integers.
 */
std::pair<int, int> Level::getStartingPosition() const {
	return m_startingPosition;
}

/**
 * It returns the exit position of the level
 *
 * @return A pair of integers.
 */
std::pair<int, int> Level::getExitPosition() const {
	return m_exitPosition;
}

/**
 * It returns a vector of pointers to Enemy objects
 *
 * @return A vector of pointers to Enemy objects.
 */
std::vector<Enemy*> Level::getEnemies() const {
	return m_enemies;
}

// setters

/**
 * This function takes a vector of strings and sets the m_tiles variable to the
 * value of the parameter.
 *
 * @param map The map to set.
 */
void Level::setMap(std::vector<std::u32string> map) {
	m_tiles = map;
}

/**
 * `setStartingPosition` sets the starting position of the level
 *
 * @param startingPosition The starting position of the player.
 */
void Level::setStartingPosition(std::pair<int, int> startingPosition) {
	m_startingPosition = startingPosition;
}

/**
 * This function sets the exit position of the level.
 *
 * @param exitPosition The position of the exit in the level.
 */
void Level::setExitPosition(std::pair<int, int> exitPosition) {
	m_exitPosition = exitPosition;
}

/**
 * `void Level::setEnemies(std::vector<Enemy*> enemies)`
 *
 * `void` is the return type of the function
 *
 * @param enemies A vector of Enemy pointers.
 */
void Level::setEnemies(std::vector<Enemy*> enemies) {
	m_enemies = enemies;
}