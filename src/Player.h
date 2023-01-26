#pragma once

#include <chrono>
#include <vector>

#include "Creature.h"
using namespace std::chrono;

// Class representing a player
class Player : public Creature {
public:
	// Empty constructor taking only the ID
	Player(int id);
	// Constructor taking name, position on the map, health points, experience,
	// level, attack power, maximum health and starting inventory
	Player(int id, char32_t appearance, int x, int y, int health, int maxHealth,
		   int level, int attackPower, int64_t speed);

	virtual ~Player() = default;
	// Method responsible for moving the player
	virtual void moveUp();
	virtual void moveDown();
	virtual void moveLeft();
	virtual void moveRight();
	// Method responsible for attacking another creature
	virtual void attack();

	virtual void attack(Creature &other);

	// Getters and setters for inventory
	std::vector<Item> getInventory() const;
	void setInventory(std::vector<Item> inventory);
	// Method for adding an item to the inventory
	void addToInventory(Item *item);

	// Getters and setters for experience, level and attack power
	int getExperience() const;
	void setExperience(int experience);
	int getLevel() const;
	void setLevel(int level);
	int getAttackPower() const;
	void setAttackPower(int attackPower);
	// Method for getting the experience needed to reach the next level
	int getNextLevelExp() const;
	int getPrevLevelExp() const;

	// Getter and setter for maximum health
	int getMaxHealth() const;
	void setMaxHealth(int maxHealth);

	void setHealth(int health);

	// Getter and setter for move delay
	time_point<steady_clock> getMoveTimer() const;
	void setMoveTimer(time_point<steady_clock> moveTimer);

	// Getter and setter for attack delay
	time_point<steady_clock> getAttackTimer() const;
	void setAttackTimer(time_point<steady_clock> attackTimer);

	// Getter and setter for speed
	int64_t getSpeed() const;
	void setSpeed(int64_t speed);

	// Getter and setter for attack speed
	int64_t getAttackSpeed() const;
	void setAttackSpeed(int64_t attackSpeed);

	// Getter and setter for attack range
	int getAttackRange() const;
	void setAttackRange(int attackRange);

	// Getter and setter for isMeleeAttack
	bool getIsMeleeAttack() const;
	void setIsMeleeAttack(bool isMeleeAttack);

	void updateMeleeWeaponList();

	std::vector<Creature *> getMeleeWeaponList() const;

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
	int64_t m_speed;
	// attack speed
	int64_t m_attackSpeed;
	// move time
	time_point<steady_clock> m_moveTimer;
	//
	time_point<steady_clock> m_attackTimer;
	// attack range
	int m_attackRange;

	bool m_isMeleeAttack;

	std::vector<Creature *> m_meleeWeaponList;
};
