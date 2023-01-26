#include "Item.h"

// default constructor

Item::Item() :
	m_name(""), m_appearance(' '), m_value(0), m_type(ItemType::Food) {}

/**
 * @brief Construct a new Item object
 *
 *
 * @param name The name of the item.
 * @param appearance The character that will be used to represent the item on
 * the map.
 * @param value The value of the item.
 * @param type The type of item.
 */
Item::Item(std::string name, char32_t appearance, int value, ItemType type) :
	m_name(name), m_appearance(appearance), m_value(value), m_type(type) {}

/**
 * Copy constructor for Item class.
 *
 * @param other The other item to copy.
 */
Item::Item(const Item &other) :
	m_name(other.m_name),
	m_appearance(other.m_appearance),
	m_value(other.m_value),
	m_type(other.m_type) {}

/**
 * It returns the name of the item.
 *
 * @return The name of the item.
 */
std::string Item::getName() const {
	return m_name;
}

/**
 * This function sets the name of the item.
 *
 * @param name The name of the item.
 */
void Item::setName(std::string name) {
	m_name = name;
}

/**
 * `char32_t Item::getAppearance() const`
 *
 * The function returns a `char32_t` and is a member of the `Item` class. The
 * function is `const` and has no parameters
 *
 * @return The appearance of the item.
 */
char32_t Item::getAppearance() const {
	return m_appearance;
}

/**
 * `void Item::setAppearance(char32_t appearance)`
 *
 * The function is called `setAppearance` and it takes one parameter,
 * `appearance`, which is a `char32_t`. The function returns `void`, which means
 * it doesn't return anything
 *
 * @param appearance The character that will be used to represent the item on
 * the map.
 */
void Item::setAppearance(char32_t appearance) {
	m_appearance = appearance;
}

/**
 * This function returns the value of the item
 *
 * @return The value of the item.
 */
int Item::getValue() const {
	return m_value;
}

/**
 * This function sets the value of the item.
 *
 * @param value The value of the item.
 */
void Item::setValue(int value) {
	m_value = value;
}

/**
 * It returns the type of the item.
 *
 * @return The type of the item.
 */
ItemType Item::getType() const {
	return m_type;
}

/**
 * This function sets the type of the item to the type passed in.
 *
 * @param type The type of item.
 */
void Item::setType(ItemType type) {
	m_type = type;
}
