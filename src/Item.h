#pragma once

#include <string>
// Class representing an item that can be possessed by a creature

enum ItemType { Food, Weapon, RangedWeapon, Experience };
class Item {
public:
	// Default constructor
	Item();
	// Constructor taking the name, appearance, and value of the item
	Item(std::string name, char32_t appearance, int value, ItemType type);

	// copy constructor
	Item(const Item &other);

	virtual ~Item() = default;

	// Getters and setters for name
	std::string getName() const;
	void setName(std::string name);

	// Getters and setters for appearance
	char32_t getAppearance() const;
	void setAppearance(char32_t appearance);

	// Getters and setters for value
	int getValue() const;
	void setValue(int value);

	// Getters and setters for type
	ItemType getType() const;
	void setType(ItemType type);

protected:
	// Name of the item
	std::string m_name;
	// Appearance of the item
	char32_t m_appearance;
	// Value of the item
	int m_value;
	// type of item
	ItemType m_type;
};
