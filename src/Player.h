#pragma once

#include "Creature.h"

// Class representing a player
class Player : public Creature {
public:
	// Constructor taking name, position on the map, health points, experience,
	// level, attack power, maximum health and starting inventory
	Player(int id, std::string name, char appearance, int x, int y, int health,
		   int maxHealth, int level, int attackPower);
	// Destructor
	virtual ~Player();

	// Method responsible for moving the player
	virtual void move();
	// Method responsible for attacking another creature
	virtual void attack(Creature &other);

	// Getters and setters for appearance
	wchar_t getAppearance() const;
	void setAppearance(wchar_t appearance);

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
	int getHealth() const;
	void setHealth(int health);

	// Getter and setter for maximum health
	int getMaxHealth() const;
	void setMaxHealth(int maxHealth);

protected:
	// Appearance of the player (single character)
	wchar_t m_appearance;
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
};
