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
}

Player::Player(int id, char32_t appearance, int x, int y, int health,
			   int maxHealth, int level, int attackPower) :
	Creature(id, appearance, x, y, health),
	m_maxHealth(maxHealth),
	m_level(level),
	m_attackPower(attackPower) {}

Player::~Player() {}

void Player::moveUp() {
	m_y--;
}

void Player::moveDown() {
	m_y++;
}

void Player::moveLeft() {
	m_x--;
}

void Player::moveRight() {
	m_x++;
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
}

int Player::getLevel() const {
	return m_level;
}

void Player::setLevel(int level) {
	m_level = level;
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
