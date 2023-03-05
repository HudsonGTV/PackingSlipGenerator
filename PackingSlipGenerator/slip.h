#ifndef SLIP_H
#define SLIP_H

#include <vector>
#include <ctime>

#include "company.h"
#include "item.h"

class PackingSlip {

private:
	int m_padAmount = 80;
	std::time_t m_date = 0;
	Company *m_company = nullptr;
	Entity *m_customer = nullptr;
	std::string m_orderUID = "Not Specified";
	std::vector<Item *> m_items;

public:
	PackingSlip(std::string companyFileName);
	~PackingSlip();

	void AddItem(Item *item);
	void RemoveItem(Item *item);
	void DestroyItems();

	int GetItemCount();
	std::vector<Item *> GetItems();
	std::string GenerateSlip();

};

#endif
