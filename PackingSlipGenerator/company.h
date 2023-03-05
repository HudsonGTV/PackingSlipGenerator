#ifndef COMPANY_H
#define COMPANY_H

#include "entity.h"

class Company: public Entity {

private:
	std::string m_website = "null";

public:
	void SetWebsite(std::string website);

	std::string GetWebsite();

};

#endif
