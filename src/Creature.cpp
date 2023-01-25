#include "Creature.h"

Creature::Creature() :
	m_id(0), m_x(0), m_y(0), m_health(0), m_appearance(U'C') {}

Creature::Creature(int id, char32_t appearance, int x, int y, int health) :
	m_id(id), m_x(x), m_y(y), m_health(health), m_appearance(appearance) {}

int Creature::getId() const {
	return m_id;
}
int Creature::getX() const {
	return m_x;
}

void Creature::setX(int x) {
	m_x = x;
}

int Creature::getY() const {
	return m_y;
}

void Creature::setY(int y) {
	m_y = y;
}

int Creature::getHealth() const {
	return m_health;
}

void Creature::setHealth(int health) {
	m_health = health;
}

char32_t Creature::getAppearance() const {
	return m_appearance;
}

void Creature::setAppearance(char32_t appearance) {
	m_appearance = appearance;
}
