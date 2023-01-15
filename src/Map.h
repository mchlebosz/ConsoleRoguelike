#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Creature.h"
#include "Level.h"

// Class responsible for storing information about the map and displaying it
class Map {
public:
	// Constructor taking the width and height of the map
	Map(int width, int height);
	// Destructor
	~Map();

	// Getters and setters for the width and height of the map
	int getWidth() const;
	void setWidth(int width);
	int getHeight() const;
	void setHeight(int height);

	// Method for setting the appearance of a tile on the map
	void setTileAppearance(int x, int y, char32_t appearance);
	// Method for getting the appearance of a tile on the map
	char32_t getTileAppearance(int x, int y) const;

	// Method for setting the appearance of a creature on the map
	void setCreatureAppearance(int id, int x, int y);
	// Method for getting the appearance of a creature on the map
	char32_t getCreatureAppearance(int id) const;

	// Method for adding a creature to the map
	void addCreature(int id, Creature* creature);
	// Method for removing a creature from the map
	void removeCreature(int id);
	// Method for getting a creature from the map
	Creature* getCreature(int id) const;

	// Method for displaying the map
	void display() const;

	std::u32string getMapString() const;

	void loadMap(std::vector<std::u32string> newMap);

private:
	// Width of the map
	int m_width;
	// Height of the map
	int m_height;
	// Tiles of the map (2D vector of characters)
	std::vector<std::vector<char32_t>> m_tiles;

	// Map of creatures on the map (key: ID of the creature, value: reference to
	// the creature)
	std::unordered_map<int, Creature*> m_creatures;
};