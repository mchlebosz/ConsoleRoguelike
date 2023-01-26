/**
 * Creature::Creature(int id, char32_t appearance, int x, int y, int health) :
 * 	m_id(id), m_x(x), m_y(y), m_health(health), m_appearance(appearance) {}
 */
#include "Creature.h"

Creature::Creature() :
	m_id(0), m_x(0), m_y(0), m_health(0), m_appearance(U'C') {}

/**
 * Creature::Creature(int id, char32_t appearance, int x, int y, int health) :
 * 	m_id(id), m_x(x), m_y(y), m_health(health), m_appearance(appearance) {}
 *
 * @param id The unique ID of the creature.
 * @param appearance The character that will be used to represent the creature
 * on the map.
 * @param x The x coordinate of the creature.
 * @param y The y coordinate of the creature.
 * @param health The health of the creature.
 */
Creature::Creature(int id, char32_t appearance, int x, int y, int health) :
	m_id(id), m_x(x), m_y(y), m_health(health), m_appearance(appearance) {}

/**
 * This function returns the value of the private member variable m_id
 *
 * @return The id of the creature.
 */
int Creature::getId() const {
	return m_id;
}
/**
 * `getX` returns the value of the private member variable `m_x`
 *
 * @return The value of m_x.
 */
int Creature::getX() const {
	return m_x;
}

/**
 * Creature::Creature(int x, int y, int health, char32_t appearance) : m_x(x),
 * m_y(y), m_health(health), m_appearance(appearance) {}
 *
 * @param x The x coordinate of the creature.
 */
void Creature::setX(int x) {
	m_x = x;
}
/**
 * This function returns the value of the private member variable m_y.
 *
 * @return The y coordinate of the creature.
 */

int Creature::getY() const {
	return m_y;
}
/**
 * This function sets the y coordinate of the creature to the value of the
 * parameter y.
 *
 * @param y The y coordinate of the creature.
 */

void Creature::setY(int y) {
	m_y = y;
}
/**
 * The function returns the value of the private member variable m_health.
 *
 * @return The health of the creature.
 */

int Creature::getHealth() const {
	return m_health;
}
/**
 * This function sets the health of the creature to the value passed in.
 *
 * @param health The health of the creature.
 */

void Creature::setHealth(int health) {
	m_health = health;
}
/**
 * Creature::getAppearance() const returns the value of the private member
 * variable m_appearance
 *
 * @return The appearance of the creature.
 */

char32_t Creature::getAppearance() const {
	return m_appearance;
}
/**
 * Sets the appearance of the creature to the given appearance.
 *
 * @param appearance The character that will be used to represent the creature
 * on the map.
 */

void Creature::setAppearance(char32_t appearance) {
	m_appearance = appearance;
}
