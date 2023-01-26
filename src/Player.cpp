#include "Player.h"

#include <cmath>

using namespace std::chrono;

Player::Player(int id) : Creature() {
	m_id          = id;
	m_appearance  = U'@';
	m_experience  = 0;
	m_attackPower = 1;
	m_maxHealth   = 10;
	setLevel(1);
	m_health        = m_maxHealth;
	m_inventory     = std::vector<Item>();
	m_x             = 0;
	m_y             = 0;
	m_moveTimer     = steady_clock::now();
	m_speed         = 1;
	m_attackRange   = 1;
	m_isMeleeAttack = false;
	m_attackTimer   = steady_clock::now();
	m_attackSpeed   = 1;
}

/**
 * Player::Player(int id, char32_t appearance, int x, int y, int health, int
 * maxHealth, int level, int attackPower, int64_t speed) : Creature(id,
 * appearance, x, y, health), m_experience(0), m_attackPower(attackPower),
 * m_maxHealth(maxHealth), m_speed(speed), m_moveTimer(steady_clock::now()) {
 * setLevel(level); m_isMeleeAttack = false; m_attackTimer =
 * steady_clock::now(); }
 *
 * @param id The id of the player.
 * @param appearance The character that will be used to represent the player on
 * the map.
 * @param x The x coordinate of the player.
 * @param y The y coordinate of the player.
 * @param health The player's current health.
 * @param maxHealth The maximum health of the player.
 * @param level The level of the player.
 * @param attackPower The amount of damage the player does when attacking.
 * @param speed The speed of the player in milliseconds.
 */
Player::Player(int id, char32_t appearance, int x, int y, int health,
			   int maxHealth, int level, int attackPower, int64_t speed) :
	Creature(id, appearance, x, y, health),
	m_experience(0),
	m_attackPower(attackPower),
	m_maxHealth(maxHealth),
	m_speed(speed),
	m_moveTimer(steady_clock::now()) {
	setLevel(level);
	m_isMeleeAttack = false;
	m_attackTimer   = steady_clock::now();
}

/**
 * If the time since the last move is greater than the speed of the player, move
 * the player up and update the melee weapon list.
 */
void Player::moveUp() {
	auto time = steady_clock::now();
	if (duration_cast<milliseconds>(time - m_moveTimer).count() >= m_speed) {
		m_y--;
		m_moveTimer = time;
	}
	updateMeleeWeaponList();
}

/**
 * If the time since the last move is greater than the speed of the player, move
 * the player down and update the melee weapon list.
 */
void Player::moveDown() {
	auto time = steady_clock::now();
	if (duration_cast<milliseconds>(time - m_moveTimer).count() >= m_speed) {
		m_y++;
		m_moveTimer = time;
	}
	updateMeleeWeaponList();
}

/**
 * If the time since the last move is greater than the speed of the player, move
 * the player left and update the melee weapon list.
 */
void Player::moveLeft() {
	auto time = steady_clock::now();
	if (duration_cast<milliseconds>(time - m_moveTimer).count() >= m_speed) {
		m_x--;
		m_moveTimer = time;
	}
	updateMeleeWeaponList();
}

/**
 * If the time since the last movement is greater than the speed of the player,
 * move the player right and update the melee weapon list.
 */
void Player::moveRight() {
	auto time = steady_clock::now();
	if (duration_cast<milliseconds>(time - m_moveTimer).count() >= m_speed) {
		m_x++;
		m_moveTimer = time;
	}
	updateMeleeWeaponList();
}

/**
 * If the time since the last attack is greater than the attack speed, then set
 * the attack timer to the current time and set the melee attack flag to true.
 */
void Player::attack() {
	auto time = steady_clock::now();
	if (duration_cast<milliseconds>(time - m_attackTimer).count() >=
		m_attackSpeed) {
		m_attackTimer   = time;
		m_isMeleeAttack = true;
		updateMeleeWeaponList();
	}
}

/**
 * If the time since the last attack is greater than the attack speed, then the
 * other creature's health is reduced by the attack power and the attack timer
 * is set to the current time
 *
 * @param other The creature that is being attacked.
 */
void Player::attack(Creature &other) {
	auto time = steady_clock::now();
	if (duration_cast<milliseconds>(time - m_attackTimer).count() >=
		m_attackSpeed) {
		other.setHealth(other.getHealth() - m_attackPower);
		m_attackTimer   = time;
		m_isMeleeAttack = true;
		updateMeleeWeaponList();
	}
}

/**
 * It returns a copy of the player's inventory
 *
 * @return A vector of items.
 */
std::vector<Item> Player::getInventory() const {
	return m_inventory;
}

/**
 * `void Player::setInventory(std::vector<Item> inventory)`
 *
 * The function is called `setInventory` and it's a member of the `Player`
 * class. It takes a single argument, which is a `std::vector<Item>` called
 * `inventory`. It returns nothing
 *
 * @param inventory The inventory of the player.
 */
void Player::setInventory(std::vector<Item> inventory) {
	m_inventory = inventory;
}

/**
 * Adds an item to the player's inventory.
 *
 * @param item The item to be added to the inventory.
 */
void Player::addToInventory(Item *item) {
	m_inventory.push_back(*item);
}

/**
 * This function returns the value of the member variable m_experience
 *
 * @return The value of the private member variable m_experience.
 */
int Player::getExperience() const {
	return m_experience;
}

/**
 * The function sets the experience of the player and adapts the level to the
 * experience without substracting the sum of experience from the player
 *
 * @param experience The amount of experience the player has.
 */
void Player::setExperience(int experience) {
	m_experience = experience;
	int newlevel = getLevel();
	// adapt level to experience without substracting sum of experience from
	// player
	if (experience >= getNextLevelExp()) {
		while (experience >= getNextLevelExp()) {
			experience -= getNextLevelExp();
			newlevel++;
		}
		setLevel(newlevel);
	}
}

/**
 * This function returns the value of the member variable m_level
 *
 * @return The level of the player.
 */
int Player::getLevel() const {
	return m_level;
}

/**
 * The function sets the level of the player and adapts the health and attack
 * power to the level
 *
 * @param level The level of the player.
 */
void Player::setLevel(int level) {
	m_level = level;
	// adapt health and attack power to level (linearly)
	//  1 health point per odd level
	//  1 attack power per 3th level
	if (m_level % 2 == 1) setMaxHealth(getMaxHealth() + 1);
	if (m_level % 3 == 0) setAttackPower(getAttackPower() + 1);

	setHealth(getMaxHealth());
}
/**
 * This function returns the value of the private member variable m_attackPower.
 *
 * @return The attack power of the player.
 */

int Player::getAttackPower() const {
	return m_attackPower;
}

/**
 * This function sets the attack power of the player
 *
 * @param attackPower The amount of damage the player will do to the enemy.
 */
void Player::setAttackPower(int attackPower) {
	m_attackPower = attackPower;
}

/**
 * This function returns the value of the private member variable m_maxHealth.
 *
 * @return The max health of the player.
 */
int Player::getMaxHealth() const {
	return m_maxHealth;
}

/**
 * This function sets the maximum health of the player
 *
 * @param maxHealth The maximum health the player can have.
 */
void Player::setMaxHealth(int maxHealth) {
	m_maxHealth = maxHealth;
}

/**
 * It returns the amount of experience needed to level up.
 *
 * @return The next level's experience requirement.
 */
int Player::getNextLevelExp() const {
	// make it scale with level
	// (level/x)^y
	return round(pow((float)(m_level + 1) / 0.5, 3)) + 1;
}

/**
 * It returns the previous level's experience.
 *
 * @return The amount of experience needed to reach the previous level.
 */
int Player::getPrevLevelExp() const {
	// make it scale with level
	return round(pow((float)(m_level) / 0.5, 3)) + 1;
}

/**
 * This function returns the time point of the player's move timer.
 *
 * @return A time_point object.
 */
time_point<steady_clock> Player::getMoveTimer() const {
	return m_moveTimer;
}

/**
 * Sets the move timer to the time point passed in.
 *
 * @param moveTimer The time the player last moved.
 */
void Player::setMoveTimer(time_point<steady_clock> moveTimer) {
	m_moveTimer = moveTimer;
}

// speed of the player
/**
 * It returns the speed of the player.
 *
 * @return The speed of the player.
 */
int64_t Player::getSpeed() const {
	return m_speed;
}

/**
 * This function sets the speed of the player
 *
 * @param speed The speed of the player.
 */
void Player::setSpeed(int64_t speed) {
	m_speed = speed;
}

// attack delay
/**
 * This function returns the value of the private member variable m_attackTimer.
 *
 * @return A const reference to the m_attackTimer member variable.
 */
time_point<steady_clock> Player::getAttackTimer() const {
	return m_attackTimer;
}

/**
 * Sets the attack timer to the time point passed in
 *
 * @param attackTimer The time at which the player last attacked.
 */
void Player::setAttackTimer(time_point<steady_clock> attackTimer) {
	m_attackTimer = attackTimer;
}

// attack speed of the player
/**
 * This function returns the value of the private member variable m_attackSpeed
 *
 * @return The attack speed of the player.
 */
int64_t Player::getAttackSpeed() const {
	return m_attackSpeed;
}

/**
 * This function sets the attack speed of the player
 *
 * @param attackSpeed The attack speed of the player.
 */
void Player::setAttackSpeed(int64_t attackSpeed) {
	m_attackSpeed = attackSpeed;
}

// attack range
/**
 * This function returns the value of the private member variable m_attackRange
 *
 * @return The attack range of the player.
 */
int Player::getAttackRange() const {
	return m_attackRange;
}

/**
 * This function sets the attack range of the player
 *
 * @param attackRange The range of the attack.
 */
void Player::setAttackRange(int attackRange) {
	m_attackRange = attackRange;
}

// melee weapon list
/**
 * This function returns the value of the private member variable
 * m_isMeleeAttack
 *
 * @return The value of the variable m_isMeleeAttack.
 */
bool Player::getIsMeleeAttack() const {
	return m_isMeleeAttack;
}

/**
 * This function sets the value of the m_isMeleeAttack variable to the value of
 * the isMeleeAttack parameter, and then calls the updateMeleeWeaponList()
 * function.
 *
 * @param isMeleeAttack true if the player is attacking with a melee weapon,
 * false if the player is attacking with a ranged weapon
 */
void Player::setIsMeleeAttack(bool isMeleeAttack) {
	m_isMeleeAttack = isMeleeAttack;
	updateMeleeWeaponList();
}

/**
 * It creates a list of swords that are displayed around the player when the
 * player is attacking
 */
void Player::updateMeleeWeaponList() {
	// clear old swords
	m_meleeWeaponList.clear();
	// add swords as m_meleeWeaponList at cross with coords max attack range
	char32_t sword = U'🔪';
	if (!m_isMeleeAttack) {
		sword = U' ';
	}
	for (int i = 1; i <= m_attackRange; i++) {
		m_meleeWeaponList.push_back(
			new Player(i, sword, getX() + i * 2, getY(), 1, 1, 1, 1, 1));
		m_meleeWeaponList.push_back(new Player(
			i + m_attackRange, sword, getX() - i * 2, getY(), 1, 1, 1, 1, 1));
		m_meleeWeaponList.push_back(new Player(
			i + m_attackRange * 2, sword, getX(), getY() - i, 1, 1, 1, 1, 1));
		m_meleeWeaponList.push_back(new Player(
			i + m_attackRange * 3, sword, getX(), getY() + i, 1, 1, 1, 1, 1));
	}
}

/**
 * It returns a vector of Creature pointers
 *
 * @return A vector of Creature pointers.
 */
std::vector<Creature *> Player::getMeleeWeaponList() const {
	return m_meleeWeaponList;
}

/**
 * If the health is greater than the max health, set the health to the max
 * health, otherwise set the health to the health
 *
 * @param health The amount of health the player has.
 */
void Player::setHealth(int health) {
	if (health > m_maxHealth) {
		m_health = m_maxHealth;
	} else {
		m_health = health;
	}
}