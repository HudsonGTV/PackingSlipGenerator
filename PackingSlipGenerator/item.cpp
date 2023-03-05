#include "item.h"

Item::Item() {
	m_attributes = new std::vector<std::string>();
}

Item::~Item() {
	delete m_attributes;
}

/// <summary>
///		Sets amount of the item.
/// </summary>
/// <param name="quantity">Desired item quantity</param>
void Item::SetQuantity(int quantity) {
	m_quantity = quantity;
}

/// <summary>
///		Sets name of item.
/// </summary>
/// <param name="name">Desired item name</param>
void Item::SetName(std::string name) {
	m_name = name;
}

/// <summary>
///		Adds an attribute (property) of the item.
/// </summary>
/// <param name="attribute">Property to add to item</param>
void Item::AddAttribute(std::string attribute) {
	m_attributes->push_back(attribute);
}

/// <summary>
///		Gets the item quantity.
/// </summary>
/// <returns>Item Quantity</returns>
int Item::GetQuantity() {
	return m_quantity;
}

/// <summary>
///		Gets the name of the item.
/// </summary>
/// <returns>Name of item</returns>
std::string Item::GetName() {
	return m_name;
}

/// <summary>
///		Gets a pointer to the list (vector) of items.
/// </summary>
/// <returns>Pointer to list (vector) of items</returns>
std::vector<std::string> *Item::GetAttributes() {
	return m_attributes;
}
