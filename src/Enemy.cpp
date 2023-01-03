#include "Enemy.h"

Enemy::Enemy(int id, std::string name, char appearance, int x, int y,
			 int health, int attackPower) :
	Creature(id, name, appearance, x, y, health), m_attackPower(attackPower) {}

Enemy::~Enemy() {}

void Enemy::move() {
	// TODO: Implement enemy movement
}

void Enemy::attack(Creature &other) {
	// TODO: Implement enemy attack
}

wchar_t Enemy::getAppearance() const {
	return m_appearance;
}

void Enemy::setAppearance(wchar_t appearance) {
	m_appearance = appearance;
}

std::string Enemy::getType() const {
	return m_type;
}

void Enemy::setType(std::string type) {
	m_type = type;
}

int Enemy::getDodgeChance() const {
	return m_dodgeChance;
}

void Enemy::setDodgeChance(int dodgeChance) {
	m_dodgeChance = dodgeChance;
}

int Enemy::getAttackPower() const {
	return m_attackPower;
}

void Enemy::setAttackPower(int attackPower) {
	m_attackPower = attackPower;
}

std::vector<Item> Enemy::getItems() const {
	return m_items;
}

void Enemy::setItems(std::vector<Item> items) {
	m_items = items;
}

void Enemy::addToItems(Item item) {
	m_items.push_back(item);
}
