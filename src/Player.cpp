#include "Player.h"

#include <cmath>

using namespace std::chrono;

Player::Player(int id) : Creature() {
	m_id         = id;
	m_appearance = U'@';
	m_experience = 0;
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

Player::Player(int id, char32_t appearance, int x, int y, int health,
			   int maxHealth, int level, int attackPower, int64_t speed) :
	Creature(id, appearance, x, y, health),
	m_experience(0),
	m_attackPower(attackPower),
	m_speed(speed),
	m_moveTimer(steady_clock::now()) {
	setLevel(level);
	m_isMeleeAttack = false;
	m_attackTimer   = steady_clock::now();
}

void Player::moveUp() {
	auto time = steady_clock::now();
	if (duration_cast<milliseconds>(time - m_moveTimer).count() >= m_speed) {
		m_y--;
		m_moveTimer = time;
	}
	updateMeleeWeaponList();
}

void Player::moveDown() {
	auto time = steady_clock::now();
	if (duration_cast<milliseconds>(time - m_moveTimer).count() >= m_speed) {
		m_y++;
		m_moveTimer = time;
	}
	updateMeleeWeaponList();
}

void Player::moveLeft() {
	auto time = steady_clock::now();
	if (duration_cast<milliseconds>(time - m_moveTimer).count() >= m_speed) {
		m_x--;
		m_moveTimer = time;
	}
	updateMeleeWeaponList();
}

void Player::moveRight() {
	auto time = steady_clock::now();
	if (duration_cast<milliseconds>(time - m_moveTimer).count() >= m_speed) {
		m_x++;
		m_moveTimer = time;
	}
	updateMeleeWeaponList();
}

void Player::attack() {
	auto time = steady_clock::now();
	if (duration_cast<milliseconds>(time - m_attackTimer).count() >=
		m_attackSpeed) {
		m_attackTimer   = time;
		m_isMeleeAttack = true;
		updateMeleeWeaponList();
	}
}

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

std::vector<Item> Player::getInventory() const {
	return m_inventory;
}

void Player::setInventory(std::vector<Item> inventory) {
	m_inventory = inventory;
}

void Player::addToInventory(Item item) {
	m_inventory.push_back(item);
}

int Player::getExperience() const {
	return m_experience;
}

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

int Player::getLevel() const {
	return m_level;
}

void Player::setLevel(int level) {
	m_level = level;
	// adapt health and attack power to level (linearly)
	//  1 health point per odd level
	//  1 attack power per 3th level
	if (m_level % 2 == 1) setMaxHealth(m_level / 2 + 4);
	if (m_level % 3 == 0) setAttackPower(m_level / 3);

	setHealth(getMaxHealth());
}

int Player::getAttackPower() const {
	return m_attackPower;
}

void Player::setAttackPower(int attackPower) {
	m_attackPower = attackPower;
}

int Player::getMaxHealth() const {
	return m_maxHealth;
}

void Player::setMaxHealth(int maxHealth) {
	m_maxHealth = maxHealth;
}

int Player::getNextLevelExp() const {
	// make it scale with level
	// (level/x)^y
	return round(pow((float)(m_level + 1) / 0.6, 2.2)) + 1;
}

int Player::getPrevLevelExp() const {
	// make it scale with level
	return round(pow((float)(m_level) / 0.6, 2.2)) + 1;
}

// move delay
time_point<steady_clock> Player::getMoveTimer() const {
	return m_moveTimer;
}

void Player::setMoveTimer(time_point<steady_clock> moveTimer) {
	m_moveTimer = moveTimer;
}

// speed of the player
int64_t Player::getSpeed() const {
	return m_speed;
}

void Player::setSpeed(int64_t speed) {
	m_speed = speed;
}

// attack delay
time_point<steady_clock> Player::getAttackTimer() const {
	return m_attackTimer;
}

void Player::setAttackTimer(time_point<steady_clock> attackTimer) {
	m_attackTimer = attackTimer;
}

// attack speed of the player
int64_t Player::getAttackSpeed() const {
	return m_attackSpeed;
}

void Player::setAttackSpeed(int64_t attackSpeed) {
	m_attackSpeed = attackSpeed;
}

// attack range
int Player::getAttackRange() const {
	return m_attackRange;
}

void Player::setAttackRange(int attackRange) {
	m_attackRange = attackRange;
}

// melee weapon list
bool Player::getIsMeleeAttack() const {
	return m_isMeleeAttack;
}

void Player::setIsMeleeAttack(bool isMeleeAttack) {
	m_isMeleeAttack = isMeleeAttack;
	updateMeleeWeaponList();
}

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

std::vector<Creature *> Player::getMeleeWeaponList() const {
	return m_meleeWeaponList;
}