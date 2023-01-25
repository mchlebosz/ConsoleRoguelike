#include "Enemy.h"

Enemy::Enemy(int id) : Creature() {
	m_id          = id;
	m_appearance  = U'X';
	m_type        = "None";
	m_dodgeChance = 0;
	m_attackPower = 1;
	m_items       = std::vector<Item>();
	m_health      = 10;
	m_x           = 0;
	m_y           = 0;
}

Enemy::Enemy(int id, char appearance, int x, int y, int health,
			 int attackPower) :
	Creature(id, appearance, x, y, health), m_attackPower(attackPower) {}

void Enemy::move() {
	// TODO: Implement enemy movement
}

void Enemy::attack(Creature &other) {
	// TODO: Implement enemy attack
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
