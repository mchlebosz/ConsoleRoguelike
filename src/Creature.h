#pragma once

#include <string>
#include <vector>

#include "Item.h"

// Abstract class representing a creature
class Creature {
public:
	// Default constructor
	Creature();
	// Constructor taking name, position on the map and health points
	Creature(int id, char32_t appearance, int x, int y, int health);

	virtual ~Creature() = default;

	// Abstract method responsible for attacking another creature
	virtual void attack(Creature &other) = 0;

	// Getters and setters for name, position on the map, health points and
	// appearance
	int getId() const;
	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
	int getHealth() const;
	virtual void setHealth(int health);
	char32_t getAppearance() const;
	void setAppearance(char32_t appearance);

protected:
	// ID of the creature
	int m_id;
	// X position of the creature on the map
	int m_x;
	// Y position of the creature on the map
	int m_y;
	// Health points of the creature
	int m_health;
	// Appearance of the creature (single character)
	char32_t m_appearance;
};
