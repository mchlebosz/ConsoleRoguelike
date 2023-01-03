#include "Creature.h"

Creature::Creature() :
	m_id(0), m_name(""), m_x(0), m_y(0), m_health(0), m_appearance(L'\0') {}

Creature::Creature(int id, std::string name, wchar_t appearance, int x, int y,
				   int health) :
	m_id(id),
	m_name(name),
	m_x(x),
	m_y(y),
	m_health(health),
	m_appearance(appearance) {}

Creature::~Creature() {}

int Creature::getId() const {
	return m_id;
}

std::string Creature::getName() const {
	return m_name;
}

void Creature::setName(std::string name) {
	m_name = name;
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

wchar_t Creature::getAppearance() const {
	return m_appearance;
}

void Creature::setAppearance(wchar_t appearance) {
	m_appearance = appearance;
}
