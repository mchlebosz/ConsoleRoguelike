#pragma once

#include <string.h>

#include <vector>

#include "Creature.h"

// Class representing an enemy
class Enemy : public Creature {
public:
	// Basic constructor
	Enemy(int id);
	// Constructor taking name, position on the map, health points, type, dodge
	// chance, attack power, and items
	// Enemy.h
	Enemy(int id, char appearance, int x, int y, int health, int attackPower);
	// Destructor
	virtual ~Enemy();

	// Method responsible for moving the enemy
	virtual void move();
	// Method responsible for attacking another creature
	virtual void attack(Creature &other);
	// Getters and setters for type
	std::string getType() const;
	void setType(std::string type);

	// Getters and setters for dodge chance
	int getDodgeChance() const;
	void setDodgeChance(int dodgeChance);

	// Getters and setters for attack power
	int getAttackPower() const;
	void setAttackPower(int attackPower);

	// Getters and setters for items
	std::vector<Item> getItems() const;
	void setItems(std::vector<Item> items);
	// Method for adding an item to the list of items
	void addToItems(Item item);

protected:
	// Type of the enemy
	std::string m_type;
	// Chance of dodging an attack (percentage, from 0 to 100)
	int m_dodgeChance;
	// Attack power of the enemy
	int m_attackPower;
	// List of items possessed by the enemy
	std::vector<Item> m_items;
};
