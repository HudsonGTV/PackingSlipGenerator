#ifndef ENTITY_H
#define ENTITY_H

#include "address.h"

class Entity {

private:
	std::string m_name = "null";
	std::string m_telephone = "N/A";
	Address *m_address = nullptr;

public:
	~Entity();

	void SetName(std::string name);
	void SetTelephone(std::string tel);
	void SetAddress(Address *address);
	void SetAddress(std::string street, std::string city, 
		std::string state, std::string zipCode, 
		std::string country);

	std::string GetName();
	std::string GetTelephone();

	Address *GetAddress();

};

#endif
