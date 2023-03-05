#include "item.h"

Item::Item() {
	m_attributes = new std::vector<std::string>();
}

Item::~Item() {
	delete m_attributes;
}

void Item::SetQuantity(int quantity) {
	m_quantity = quantity;
}

void Item::SetName(std::string name) {
	m_name = name;
}

void Item::AddAttribute(std::string attribute) {
	m_attributes->push_back(attribute);
}

int Item::GetQuantity() {
	return m_quantity;
}

std::string Item::GetName() {
	return m_name;
}

std::vector<std::string> *Item::GetAttributes() {
	return m_attributes;
}
