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
	Creature(int id, std::string name, wchar_t appearance, int x, int y,
			 int health);
	// Destructor
	virtual ~Creature();

	// Abstract method responsible for moving the creature
	virtual void move() = 0;
	// Abstract method responsible for attacking another creature
	virtual void attack(Creature &other) = 0;

	// Getters and setters for name, position on the map, health points and
	// appearance
	int getId() const;
	std::string getName() const;
	void setName(std::string name);
	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);
	int getHealth() const;
	void setHealth(int health);
	wchar_t getAppearance() const;
	void setAppearance(wchar_t appearance);

protected:
	// ID of the creature
	int m_id;
	// Name of the creature
	std::string m_name;
	// X position of the creature on the map
	int m_x;
	// Y position of the creature on the map
	int m_y;
	// Health points of the creature
	int m_health;
	// Appearance of the creature (single character)
	wchar_t m_appearance;
};