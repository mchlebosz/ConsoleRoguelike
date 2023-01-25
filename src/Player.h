#pragma once

#include "Creature.h"

// Class representing a player
class Player : public Creature {
public:
	// Empty constructor taking only the ID
	Player(int id);
	// Constructor taking name, position on the map, health points, experience,
	// level, attack power, maximum health and starting inventory
	Player(int id, char32_t appearance, int x, int y, int health, int maxHealth,
		   int level, int attackPower, int speed);

	virtual ~Player() = default;
	// Method responsible for moving the player
	virtual void moveUp();
	virtual void moveDown();
	virtual void moveLeft();
	virtual void moveRight();
	// Method responsible for attacking another creature
	virtual void attack(Creature &other);

	// Getters and setters for inventory
	std::vector<Item> getInventory() const;
	void setInventory(std::vector<Item> inventory);
	// Method for adding an item to the inventory
	void addToInventory(Item item);

	// Getters and setters for experience, level and attack power
	int getExperience() const;
	void setExperience(int experience);
	int getLevel() const;
	void setLevel(int level);
	int getAttackPower() const;
	void setAttackPower(int attackPower);
	// Method for getting the experience needed to reach the next level
	int getNextLevelExp() const;

	// Getter and setter for maximum health
	int getMaxHealth() const;
	void setMaxHealth(int maxHealth);

	// Getter and setter for move delay
	int getMoveTimer() const;
	void setMoveTimer(int moveTimer);

	// Getter and setter for speed
	int getSpeed() const;
	void setSpeed(int speed);

protected:
	// Inventory of the player (list of items)
	std::vector<Item> m_inventory;
	// Current experience points of the player
	int m_experience;
	// Current level of the player
	int m_level;
	// Current attack power of the player
	int m_attackPower;
	// Maximum health of the player
	int m_maxHealth;
	// speed of the player
	int m_speed;
	// move delay
	time_t m_moveTimer;
};
