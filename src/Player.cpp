#include "Player.h"

Player::Player(int id, std::string name, char appearance, int x, int y,
			   int health, int maxHealth, int level, int attackPower) :
	Creature(id, name, appearance, x, y, health),
	m_maxHealth(maxHealth),
	m_level(level),
	m_attackPower(attackPower) {}

Player::~Player() {}

void Player::move() {
	// TODO: Implement player movement
}

void Player::attack(Creature &other) {
	// TODO: Implement player attack
}

wchar_t Player::getAppearance() const {
	return m_appearance;
}

void Player::setAppearance(wchar_t appearance) {
	m_appearance = appearance;
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
