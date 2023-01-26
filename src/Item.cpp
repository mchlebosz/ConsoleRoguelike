#include "Item.h"

// default constructor
Item::Item() :
	m_name(""), m_appearance(' '), m_value(0), m_type(ItemType::Food) {}

Item::Item(std::string name, char32_t appearance, int value, ItemType type) :
	m_name(name), m_appearance(appearance), m_value(value), m_type(type) {}

Item::Item(const Item &other) :
	m_name(other.m_name),
	m_appearance(other.m_appearance),
	m_value(other.m_value),
	m_type(other.m_type) {}

std::string Item::getName() const {
	return m_name;
}

void Item::setName(std::string name) {
	m_name = name;
}

char32_t Item::getAppearance() const {
	return m_appearance;
}

void Item::setAppearance(char32_t appearance) {
	m_appearance = appearance;
}

int Item::getValue() const {
	return m_value;
}

void Item::setValue(int value) {
	m_value = value;
}

ItemType Item::getType() const {
	return m_type;
}

void Item::setType(ItemType type) {
	m_type = type;
}
