#pragma once

#include <string>

// Class representing an item that can be possessed by a creature
class Item {
public:
	// Constructor taking the name, appearance, and value of the item
	Item(std::string name, std::u32string appearance, int value);

	virtual ~Item() = default;

	// Getters and setters for name
	std::string getName() const;
	void setName(std::string name);

	// Getters and setters for appearance
	std::u32string getAppearance() const;
	void setAppearance(std::u32string appearance);

	// Getters and setters for value
	int getValue() const;
	void setValue(int value);

protected:
	// Name of the item
	std::string m_name;
	// Appearance of the item
	std::u32string m_appearance;
	// Value of the item
	int m_value;
};
