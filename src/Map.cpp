#include "Map.h"
/**
 * The function takes in a width and height and creates a map with that width
 * and height
 *
 * @param width The width of the map in tiles
 * @param height The height of the map in tiles.
 */
Map::Map(int width, int height) : m_width(width), m_height(height) {
	// Initialize the tiles of the map with empty spaces
	m_tiles.resize(height);
	for (int y = 0; y < height; y++) {
		m_tiles[y].resize(width);
		for (int x = 0; x < width; x++) {
			m_tiles[y][x] = U' ';
		}
	}
}

// destroys the map
/**
 * Delete all the creatures on the map, then delete all the items on the map.
 */
Map::~Map() {
	// Delete all the creatures on the map
	for (auto& creature : m_creatures) {
		delete creature.second;
	}

	// Delete all the items on the map
	for (auto& item : m_items) {
		delete item.first;
	}
}

/**
 * It returns the width of the map.
 *
 * @return The width of the map.
 */
int Map::getWidth() const {
	return m_width;
}

/**
 * This function sets the width of the map
 *
 * @param width The width of the map.
 */
void Map::setWidth(int width) {
	m_width = width;
}

/**
 * It returns the height of the map.
 *
 * @return The height of the map.
 */
int Map::getHeight() const {
	return m_height;
}

/**
 * This function sets the height of the map
 *
 * @param height The height of the map.
 */
void Map::setHeight(int height) {
	m_height = height;
}

/**
 * Sets the appearance of the tile at the given coordinates to the given
 * appearance.
 *
 * @param x The x coordinate of the tile to set.
 * @param y The y coordinate of the tile to set.
 * @param appearance The character to display on the screen.
 */
void Map::setTileAppearance(int x, int y, char32_t appearance) {
	m_tiles[y][x] = appearance;
}

/**
 * It returns the appearance of the tile at the given coordinates
 *
 * @param x The x coordinate of the tile to get the appearance of.
 * @param y The y coordinate of the tile to get the appearance of.
 *
 * @return A character.
 */
char32_t Map::getTileAppearance(int x, int y) const {
	return m_tiles[y][x];
}

/**
 * It adds a creature to the map
 *
 * @param id The id of the creature.
 * @param creature The creature to add to the map.
 */
void Map::addCreature(int id, Creature* creature) {
	m_creatures.insert(std::make_pair(id, creature));
}

/**
 * It removes a creature from the map
 *
 * @param id The id of the creature to remove.
 */
void Map::removeCreature(int id) {
	m_creatures.erase(id);
}

Creature* Map::getCreature(int id) const {
	return m_creatures.at(id);
}

/**
 * It displays the map, and if there is a creature on a tile, it displays the
 * creature's appearance instead of the tile's appearance
 */
void Map::display() const {
	// Display the top border of the map
	std::wcout << U"╔══";
	for (int x = 0; x < m_width; x++) {
		std::wcout << U"═";
	}
	std::wcout << U"══╗" << std::endl;
	// empty line
	std::wcout << U"║  ";
	for (int x = 0; x < m_width; x++) {
		std::wcout << U" ";
	}
	std::wcout << U"  ║" << std::endl;

	// Display the tiles of the map
	for (int y = 0; y < m_height; y++) {
		std::wcout << U"║  ";
		for (int x = 0; x < m_width; x++) {
			// Check if there is a creature on the current tile
			bool creatureOnTile = false;
			for (auto& creature : m_creatures) {
				if (creature.second->getX() == x &&
					creature.second->getY() == y) {
					// Display the appearance of the creature
					std::wcout << creature.second->getAppearance();
					creatureOnTile = true;
					break;
				}
			}
			if (!creatureOnTile) {
				// Display the appearance of the tile
				std::wcout << m_tiles[y][x];
			}
		}
		std::wcout << U"  ║" << std::endl;
	}

	// empty line
	std::wcout << U"║  ";
	for (int x = 0; x < m_width; x++) {
		std::wcout << U" ";
	}
	std::wcout << U"  ║" << std::endl;

	// Display the bottom border of the map
	std::wcout << U"╚══";
	for (int x = 0; x < m_width; x++) {
		std::wcout << U"═";
	}
	std::wcout << U"══╝" << std::endl;
}

/**
 * It returns a string that represents the map
 *
 * @return A string of the map.
 */
std::u32string Map::getMapString() const {
	std::u32string mapString = U"";
	// Display the top border of the map

	mapString += U"╔══";
	for (int x = 0; x < m_width; x++) {
		mapString += U"═";
	}
	mapString += U"══╗\n";
	// empty line
	mapString += U"║  ";
	for (int x = 0; x < m_width; x++) {
		mapString += U" ";
	}
	mapString += U"  ║\n";

	// Display the tiles of the map
	for (int y = 0; y < m_height; y++) {
		mapString += U"║  ";
		for (int x = 0; x < m_width; x++) {
			// Check if there is an item on the current tile
			bool itemOnTile = false;
			for (auto& item : m_items) {
				if (item.second.first == x && item.second.second == y) {
					// Display the appearance of the item
					mapString += item.first->getAppearance();
					itemOnTile = true;
					break;
				}
			}

			// Check if there is a creature on the current tile
			bool creatureOnTile = false;
			for (auto& creature : m_creatures) {
				if (creature.second->getX() == x &&
					creature.second->getY() == y) {
					// Display the appearance of the creature
					mapString += creature.second->getAppearance();
					creatureOnTile = true;
					break;
				}
			}
			if (!creatureOnTile && !itemOnTile) {
				// Display the appearance of the tile
				mapString += m_tiles[y][x];
			}
		}
		mapString += U"  ║\n";
	}

	// empty line
	mapString += U"║  ";
	for (int x = 0; x < m_width; x++) {
		mapString += U" ";
	}
	mapString += U"  ║\n";

	// Display the bottom border of the map
	mapString += U"╚══";
	for (int x = 0; x < m_width; x++) {
		mapString += U"═";
	}
	mapString += U"══╝\n";

	return mapString;
}

/**
 * It takes a vector of strings, and then copies each character from the strings
 * into a vector of vectors of characters
 *
 * @param newMap A vector of strings, each string is a row of the map.
 */
void Map::loadMap(std::vector<std::u32string> newMap) {
	// Clear the current map
	m_tiles.clear();
	m_creatures.clear();

	// set each tile from the new map
	m_tiles.resize(newMap.size());
	m_width  = newMap[0].size();
	m_height = newMap.size();
	for (size_t y = 0; y < newMap.size(); y++) {
		m_tiles[y].resize(newMap[y].size());
		for (size_t x = 0; x < newMap[y].size(); x++) {
			m_tiles[y][x] = newMap[y][x];
		}
	}
}

// Method for adding an item to the map
/**
 * It takes a pointer to an item, and two integers, and inserts a copy of the
 * item into a map, with the two integers as the key
 *
 * @param item The item to add to the map.
 * @param x The x coordinate of the item
 * @param y The y coordinate of the item
 */
void Map::addItem(Item* item, int x, int y) {
	m_items.insert(std::make_pair(new Item(*item), std::make_pair(x, y)));
}

// Method for removing an item from the map
/**
 * It removes an item from the map.
 *
 * @param item The item to remove from the map.
 */
void Map::removeItem(Item* item) {
	m_items.erase(item);
}

// Method for getting the  item
/**
 * If there's an item at the given coordinates, return it. Otherwise, return
 * nullptr
 *
 * @param x The x coordinate of the item to get.
 * @param y The y coordinate of the item to get.
 *
 * @return A pointer to an Item.
 */
Item* Map::getItem(int x, int y) const {
	for (auto& item : m_items) {
		if (item.second.first == x && item.second.second == y) {
			return item.first;
		}
	}
	return nullptr;
}

// Method for getting the position of an item
/**
 * "Given an item, return the position of that item."
 *
 * The function is a member of the Map class, so it has access to the private
 * member variables of the Map class
 *
 * @param item The item to get the position of.
 *
 * @return A pair of ints.
 */
std::pair<int, int> Map::getItemPosition(Item* item) const {
	return m_items.at(item);
}
