#include "Map.h"
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

int Map::getWidth() const {
	return m_width;
}

void Map::setWidth(int width) {
	m_width = width;
}

int Map::getHeight() const {
	return m_height;
}

void Map::setHeight(int height) {
	m_height = height;
}

void Map::setTileAppearance(int x, int y, char32_t appearance) {
	m_tiles[y][x] = appearance;
}

char32_t Map::getTileAppearance(int x, int y) const {
	return m_tiles[y][x];
}

void Map::addCreature(int id, Creature* creature) {
	m_creatures.insert(std::make_pair(id, creature));
}

void Map::removeCreature(int id) {
	m_creatures.erase(id);
}

Creature* Map::getCreature(int id) const {
	return m_creatures.at(id);
}

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
void Map::addItem(Item* item, int x, int y) {
	m_items.insert(std::make_pair(new Item(*item), std::make_pair(x, y)));
}

// Method for removing an item from the map
void Map::removeItem(Item* item) {
	m_items.erase(item);
}

// Method for getting the  item
Item* Map::getItem(int x, int y) const {
	for (auto& item : m_items) {
		if (item.second.first == x && item.second.second == y) {
			return item.first;
		}
	}
	return nullptr;
}

// Method for getting the position of an item
std::pair<int, int> Map::getItemPosition(Item* item) const {
	return m_items.at(item);
}
