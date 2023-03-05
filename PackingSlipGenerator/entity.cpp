#include <iostream>
#include <stdexcept>

#include "entity.h"

Entity::~Entity() {
	delete m_address;
}

/// <summary>
///		Sets the name of the entity.
/// </summary>
/// <param name="name">The name to use</param>
void Entity::SetName(std::string name) {
	m_name = name;
}

/// <summary>
///		Sets the phone number of the entity.
/// </summary>
/// <param name="tel">Phone number to use</param>
void Entity::SetTelephone(std::string tel) {
	m_telephone = tel;
}

/// <summary>
///		Sets the address of the entity (deletes current one if it is already set).
/// </summary>
/// <param name="address">Pointer to address to use</param>
void Entity::SetAddress(Address *address) {
	if(!address)
		throw std::exception("NullPointerException");
	if(m_address)
		delete m_address;
	m_address = address;
}

/// <summary>
///		Alternative function to set the address without having to create an Address object beforehand.
/// </summary>
/// <param name="street">Street address</param>
/// <param name="city">City</param>
/// <param name="stateCode">2-letter state code</param>
/// <param name="zipCode">5-digit zipcode with optional 4-digit extension</param>
/// <param name="country">Full name of country</param>
void Entity::SetAddress(std::string street, std::string city, std::string stateCode, std::string zipCode, std::string country) {

	Address *addr = new Address();
	addr->street = street;
	addr->city = city;
	addr->stateCode = stateCode;
	addr->zipCode = zipCode;
	addr->country = country;

	this->SetAddress(addr);

}

/// <summary>
///		Gets the name of the entity.
/// </summary>
/// <returns>Name</returns>
std::string Entity::GetName() {
	return m_name;
}

/// <summary>
///		Gets the phone number of the entity.
/// </summary>
/// <returns>Phone number</returns>
std::string Entity::GetTelephone() {
	return m_telephone;
}

/// <summary>
///		Gets a pointer to the address object of the entity.
/// </summary>
/// <returns>Pointer to address</returns>
Address *Entity::GetAddress() {
	if(!m_address) {
		std::cout << "NullPointerException" << std::endl;
		throw std::exception("NullPointerException");
	}
	return m_address;
}
