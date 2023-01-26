#pragma once

#include <string.h>

#include <chrono>
#include <utility>
#include <vector>

using namespace std::chrono;

#include "Map.h"

// Class representing an enemy
class Enemy : public Creature {
public:
	// Basic constructor
	Enemy(int id);
	// Constructor taking name, position on the map, health points, type, dodge
	// chance, attack power, and items
	// Enemy.h
	Enemy(int id, char32_t appearance, int x, int y, int health,
		  int attackPower, int speed, int attackSpeed);

	virtual ~Enemy() = default;

	// Method responsible for moving the enemy
	virtual void move();
	// Method responsible for attacking another creature
	virtual void attack(Creature &other);
	void moveTowardsPlayer(Creature &player);
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

	int getExperience() const;
	void updateExperience();

	// Method for checking if player is in staight line of sight
	bool checkLineOfSight(Creature &player, Map &map);

	// getters and setters for speed and attack speed
	int getSpeed() const;
	void setSpeed(int speed);
	int getAttackSpeed() const;
	void setAttackSpeed(int attackSpeed);

protected:
	// Type of the enemy
	std::string m_type;
	// Chance of dodging an attack (percentage, from 0 to 100)
	int m_dodgeChance;
	// Attack power of the enemy
	int m_attackPower;
	// List of items possessed by the enemy
	std::vector<Item> m_items;

	int m_experience;

	// move timer
	steady_clock::time_point m_moveTimer;
	steady_clock::time_point m_attackTimer;

	int m_speed;
	int m_attackSpeed;
};
