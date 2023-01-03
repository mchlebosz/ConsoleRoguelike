#include "Item.h"

Item::Item(std::string name, std::string appearance, int value) :
	m_name(name), m_appearance(appearance), m_value(value) {}

Item::~Item() {}

std::string Item::getName() const {
	return m_name;
}

void Item::setName(std::string name) {
	m_name = name;
}

std::string Item::getAppearance() const {
	return m_appearance;
}

void Item::setAppearance(std::string appearance) {
	m_appearance = appearance;
}

int Item::getValue() const {
	return m_value;
}

void Item::setValue(int value) {
	m_value = value;
}
