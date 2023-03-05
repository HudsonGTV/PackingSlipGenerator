#include <iostream>
#include <fstream>
#include <chrono>

#include "slip.h"

/// <summary>
///		Prints 2 strings next to eachother and pads the second string by specified amount.
/// </summary>
/// <param name="str1">First String</param>
/// <param name="str2">Second String</param>
/// <param name="amount">Amount to pad</param>
/// <param name="padChar">Character to use for padding</param>
/// <returns>Padded strings</returns>
std::string PadStrings(std::string str1, std::string str2, int amount, char padChar = ' ') {

	// Ensure valid amount
	if(amount <= 0)
		throw std::exception("InvalidArgumentException");

	// String to be returned
	std::string out = str1;

	// Pad str2
	for(int i = 0; i < amount - str1.length(); ++i)
		out += padChar;

	return out + str2;

}

/// <summary>
///		Pads an int with specified character.
/// </summary>
/// <param name="number">Number to be padded</param>
/// <param name="amount">Amount to pad</param>
/// <param name="padChar">Character to use for padding</param>
/// <returns>Padded int</returns>
std::string PadInt(int number, int amount, char padChar = '0') {

	// Ensure valid amount
	if(amount <= 0)
		throw std::exception("InvalidArgumentException");

	// String to be returned
	std::string out = std::to_string(number);

	// Pad number
	int nLen = out.length();
	for(int i = 0; i < amount - nLen; ++i)
		out = padChar + out;

	return out;

}

/// <summary>
///		Formats date into format: MONTH DD, YYYY.
/// </summary>
/// <param name="time">Time to format</param>
/// <returns>Formatted date</returns>
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

/// <param name="companyFileName">File path of file to be opened</param>
PackingSlip::PackingSlip(std::string companyFileName) {

	// Get processing date
	std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
	m_date = std::chrono::system_clock::to_time_t(timeNow);

	// Process company info from file
	std::vector<std::string> companyFileData;

	// File input stream
	std::ifstream companyFileInput;
	companyFileInput.open(companyFileName, std::ios::in);

	// Read file into companyFileData
	if(companyFileInput.is_open()) {
		std::string fileLine;
		while(std::getline(companyFileInput, fileLine))
			companyFileData.push_back(fileLine);
		companyFileInput.close();
	} else std::cout << "[Error] Could not open file with name: " << companyFileName << std::endl;

	// Ensure file is formatted correctly
	if(companyFileData.size() != 8) {
		std::cout << "[Error] Invalid/missing data in file with name: " << companyFileName << std::endl;
		throw std::exception("InvalidFileFormatException");
	}

	// Set Default Info
	m_company = new Company();
	m_company->SetName(companyFileData[0]);
	m_company->SetAddress(companyFileData[1], companyFileData[2],
		companyFileData[3], companyFileData[4], companyFileData[5]);
	m_company->SetTelephone(companyFileData[6]);
	m_company->SetWebsite(companyFileData[7]);

	// Customer Info variables
	std::string cName;
	Address *cAddr = new Address();
	std::string cCountry;
	std::string cTel;

	// Prompt for customer info
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

/// <summary>
///		Adds item to list (vector).
/// </summary>
/// <param name="item">Pointer to the item to be added</param>
void PackingSlip::AddItem(Item *item) {
	// Ensure item is not nullptr
	if(!item)
		throw std::exception("NullPointerException");
	// Add item
	m_items.push_back(item);
}

/// <summary>
///		Removes item to list (vector).
/// </summary>
/// <param name="item">Pointer to the item to be removed</param>
void PackingSlip::RemoveItem(Item *item) {

	// Ensure item is not nullptr
	if(!item)
		throw std::exception("NullPointerException");

	// Search for and remove item in m_items vector
	for(int i = 0; i < m_items.size(); ++i) {
		if(m_items.at(i) == item) {
			m_items.erase(m_items.begin() + i);
			return;
		}
	}

	// No item found if it makes it to here
	throw std::exception("ItemNotFoundException");

}

/// <summary>
///		Destroys (deletes) all items in list (vector).
/// </summary>
void PackingSlip::DestroyItems() {
	// Free all items in vector
	for(Item *item : m_items)
		delete item;
	// Clear vector
	m_items.clear();
}

/// <summary>
///		Gets the number of items in the list (vector).
/// </summary>
/// <returns>Number of items in list</returns>
int PackingSlip::GetItemCount() {
	return m_items.size() + 1;
}

/*std::vector<Item *> PackingSlip::GetItems() {
	return m_items;
}*/

/// <summary>
///		Generates a printable packing slip.
/// </summary>
/// <returns>String containing packing slip data</returns>
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
