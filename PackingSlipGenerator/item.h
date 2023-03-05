#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

class Item {

private:
	int m_quantity = 0;
	std::string m_name = "null";
	std::vector<std::string> *m_attributes = nullptr;

public:
	Item();
	~Item();

	void SetQuantity(int quantity);
	void SetName(std::string name);
	void AddAttribute(std::string attribute);

	int GetQuantity();
	std::string GetName();
	std::vector<std::string> *GetAttributes();

};

#endif
