#include <iostream>
#include <chrono>

#include "slip.h"

std::string PadStrings(std::string str1, std::string str2, int amount, char padChar = ' ') {

	if(amount <= 0)
		throw std::exception("InvalidArgumentException");

	std::string out = str1;

	// Pad str2
	for(int i = 0; i < amount - str1.length(); ++i)
		out += padChar;

	return out + str2;

}

std::string PadInt(int number, int amount, char padChar = '0') {

	if(amount <= 0)
		throw std::exception("InvalidArgumentException");

	std::string out = std::to_string(number);

	int nLen = out.length();
	for(int i = 0; i < amount - nLen; ++i)
		out = padChar + out;

	return out;

}

std::string GetFormattedDate(std::time_t time) {

	// Month names
	std::string months[12] = {
		"January", "February", "March", "April", "May", "June", 
		"July", "August", "September", "October", "November", "December"
	};

	// Time in computer's timezone
	struct std::tm tm;
	localtime_s(&tm, &time);

	// Format date
	std::string formattedDate = months[tm.tm_mon] + " ";
	formattedDate += PadInt(tm.tm_mday, 2) + ", ";
	formattedDate += std::to_string(tm.tm_year + 1900);

	return formattedDate;

}

PackingSlip::PackingSlip(std::string companyFileName) {

	// Get processing date
	std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
	m_date = std::chrono::system_clock::to_time_t(timeNow);

	// Set Default Info
	m_company = new Company();
	m_company->SetName("HKG ELECTRONICS");
	m_company->SetAddress("REDACTED", "REDACTED", 
		"REDACTED", "REDACTED", "United States");
	m_company->SetTelephone("REDACTED");
	m_company->SetWebsite("REDACTED");

	// Prompt for customer info
	std::string cName;
	Address *cAddr = new Address();
	std::string cCountry;
	std::string cTel;

	std::cout << "Customer Info" << std::endl;
	std::cout << "  Name: ";
	std::getline(std::cin, cName);

	std::cout << "  Address Info" << std::endl;
	std::cout << "    Street: ";
	std::getline(std::cin, cAddr->street);
	std::cout << "    City: ";
	std::getline(std::cin, cAddr->city);
	std::cout << "    State Code: ";
	std::getline(std::cin, cAddr->stateCode);
	std::cout << "    Zip Code: ";
	std::getline(std::cin, cAddr->zipCode);
	std::cout << "    Country Name [ENTER for " 
		<< m_company->GetAddress()->country << "]: ";
	std::getline(std::cin, cCountry);
	if(cCountry == "")
		cAddr->country = m_company->GetAddress()->country;
	else cAddr->country = cCountry;

	std::cout << "  Telephone [ENTER FOR NONE]: ";
	std::getline(std::cin, cTel);
	if(cTel == "")
		cTel = "N/A";

	// Get Purchase Order UID
	std::cout << "Purchase Order UID: ";
	std::getline(std::cin, m_orderUID);

	// Set Customer Info
	m_customer = new Entity();
	m_customer->SetName(cName);
	m_customer->SetAddress(cAddr);
	m_customer->SetTelephone(cTel);

}

PackingSlip::~PackingSlip() {
	delete m_company;
	delete m_customer;
	DestroyItems();
}

void PackingSlip::AddItem(Item *item) {
	if(!item)
		throw std::exception("NullPointerException");
	m_items.push_back(item);
}

void PackingSlip::RemoveItem(Item *item) {

	if(!item)
		throw std::exception("NullPointerException");

	for(int i = 0; i < m_items.size(); ++i) {
		if(m_items.at(i) == item)
			m_items.erase(m_items.begin() + i);
	}

	throw std::exception("ItemNotFoundException");

}

void PackingSlip::DestroyItems() {
	for(Item *item : m_items)
		delete item;
	m_items.clear();
}

int PackingSlip::GetItemCount() {
	return m_items.size() + 1;
}

std::vector<Item *> PackingSlip::GetItems() {
	return m_items;
}

std::string PackingSlip::GenerateSlip() {

	std::string buffer = PadStrings("", "PACKING LIST\n", m_padAmount);

	/* Company section */

	Address *companyAddr = m_company->GetAddress();
	Address *customerAddr = m_customer->GetAddress();

	// Company name
	buffer += m_company->GetName() + "\n";

	// Company address
	buffer += companyAddr->street + "\n";
	buffer += companyAddr->city + ", ";
	buffer += companyAddr->stateCode + " ";
	buffer += companyAddr->zipCode + "\n";
	if(companyAddr->country != customerAddr->country)
		buffer += companyAddr->country + "\n";

	// Company phone number
	buffer += "TEL: " + m_company->GetTelephone() + "\n";

	// Company website
	buffer += "WWW: " + m_company->GetWebsite() + "\n\n\n";

	/* SOLD TO AND SHIP TO SECTION */

	buffer += PadStrings("SOLD TO:", "SHIP TO:\n", m_padAmount);
	buffer += PadStrings(m_customer->GetName(), customerAddr->street + "\n", m_padAmount);
	buffer += PadStrings("", customerAddr->city + ", ", m_padAmount);
	buffer += customerAddr->stateCode + " " + customerAddr->zipCode + "\n";

	if(companyAddr->country != customerAddr->country)
		buffer += PadStrings("", customerAddr->country, m_padAmount) + "\n";

	buffer += "TEL: " + m_customer->GetTelephone() + "\n\n\n";

	/* DATE/PURCHASE ORDER NUMBER */

	buffer += PadStrings("Date:", "Purchase Order(s):\n", m_padAmount);
	buffer += PadStrings(GetFormattedDate(m_date), m_orderUID + "\n\n\n\n\n\n", m_padAmount);

	/* ITEMS */

	int indent = 8;

	buffer += PadStrings("QTY", "ITEM\n", indent);

	// Generate Item List
	for(Item *item : m_items) {
		buffer += PadStrings(std::to_string(item->GetQuantity()), item->GetName() + "\n\n\n", indent);
		for(std::string attr : *item->GetAttributes())
			buffer += PadStrings("", attr + "\n", indent);
		buffer += "\n\n\n\n\n";
	}

	return buffer;
}
