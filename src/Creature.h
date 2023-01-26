#pragma once

#include <string>
#include <vector>

#include "Item.h"

// Abstract class representing a creature

/// @brief
/// Creature class
/// @details
/// This class is the base class for all creatures in the game. It contains
/// information about the creature's name, position on the map, health points
/// and appearance. It also contains a pure virtual method for attacking
/// another creature.
class Creature {
public:
	// Default constructor
	Creature();

	/// @brief
	/// Creature constructor
	/// @details
	/// This constructor takes the name, position on the map and health points
	/// of the creature.
	/// @param id The ID of the creature
	/// @param appearance The appearance of the creature
	/// @param x The X position of the creature on the map
	/// @param y The Y position of the creature on the map
	/// @param health The health points of the creature
	Creature(int id, char32_t appearance, int x, int y, int health);

	virtual ~Creature() = default;

	// Abstract method responsible for attacking another creature

	/// @brief
	/// Attack method
	/// @details
	/// This method is responsible for attacking another creature. It is a pure
	/// virtual method, so it must be implemented in the derived classes.
	/// @param other The creature to attack
	virtual void attack(Creature &other) = 0;

	// Getters and setters for name, position on the map, health points and
	// appearance

	/// @brief
	/// Get ID method
	/// @details
	/// This method returns the ID of the creature.
	/// @return The ID of the creature
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
