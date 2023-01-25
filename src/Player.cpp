#include "Player.h"

Player::Player(int id) : Creature() {
	m_id          = id;
	m_appearance  = U'@';
	m_experience  = 0;
	m_level       = 1;
	m_attackPower = 1;
	m_maxHealth   = 10;
	m_health      = m_maxHealth;
	m_inventory   = std::vector<Item>();
	m_x           = 0;
	m_y           = 0;
	m_moveTimer   = 0;
	m_speed       = 1;
}

Player::Player(int id, char32_t appearance, int x, int y, int health,
			   int maxHealth, int level, int attackPower, int speed) :
	Creature(id, appearance, x, y, health),
	m_experience(0),
	m_level(level),
	m_attackPower(attackPower),
	m_maxHealth(maxHealth),
	m_speed(speed),
	m_moveTimer(0) {}

void Player::moveUp() {
	if (m_moveTimer >= m_speed) {
		m_y--;
		m_moveTimer = 0;
	}
}

void Player::moveDown() {
	if (m_moveTimer >= m_speed) {
		m_y++;
		m_moveTimer = 0;
	}
}

void Player::moveLeft() {
	if (m_moveTimer >= m_speed) {
		m_x--;
		m_moveTimer = 0;
	}
}

void Player::moveRight() {
	if (m_moveTimer >= m_speed) {
		m_x++;
		m_moveTimer = 0;
	}
}

void Player::attack(Creature &other) {
	// TODO: Implement player attack
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
	while (experience >= getNextLevelExp()) {
		experience -= getNextLevelExp();
		newlevel++;
	}
	setLevel(newlevel);
}

int Player::getLevel() const {
	return m_level;
}

void Player::setLevel(int level) {
	m_level = level;
	// adapt health and attack power to level (linearly)
	//  1 health point per odd level
	//  1 attack power per 4th level
	if (m_level % 2 == 1) setMaxHealth(getMaxHealth() + 1);
	if (m_level % 4 == 0) setAttackPower(m_level / 4);

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
	// make it scale with level linearly
	return m_level * 10;
}

// move delay
int Player::getMoveTimer() const {
	return m_moveTimer;
}

void Player::setMoveTimer(int moveTimer) {
	m_moveTimer = moveTimer;
}

// speed of the player
int Player::getSpeed() const {
	return m_speed;
}

void Player::setSpeed(int speed) {
	m_speed = speed;
}