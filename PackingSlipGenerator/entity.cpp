#include <iostream>
#include <stdexcept>

#include "entity.h"

Entity::~Entity() {
	delete m_address;
}

void Entity::SetName(std::string name) {
	m_name = name;
}

void Entity::SetTelephone(std::string tel) {
	m_telephone = tel;
}

void Entity::SetAddress(Address *address) {
	if(!address)
		throw std::exception("NullPointerException");
	if(m_address)
		delete m_address;
	m_address = address;
}

void Entity::SetAddress(std::string street, std::string city, std::string stateCode, std::string zipCode, std::string country) {

	Address *addr = new Address();
	addr->street = street;
	addr->city = city;
	addr->stateCode = stateCode;
	addr->zipCode = zipCode;
	addr->country = country;

	this->SetAddress(addr);

}

std::string Entity::GetName() {
	return m_name;
}

std::string Entity::GetTelephone() {
	return m_telephone;
}

Address *Entity::GetAddress() {
	if(!m_address) {
		std::cout << "NullPointerException" << std::endl;
		throw std::exception("NullPointerException");
	}
	return m_address;
}
