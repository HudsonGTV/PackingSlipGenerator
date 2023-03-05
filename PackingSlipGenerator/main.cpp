#include <iostream>

#include "slip.h"

int main() {

	std::cout << "PACKING SLIP GENERATE v1.0 BY HKG ELECTRONICS" << std::endl;

	// Create packingSlip and trigger customer info gathering
	PackingSlip *packingSlip = new PackingSlip("company_info.data");

	// Item add loop
	while(true) {

		// Item properties
		std::string itemName = "undefined";
		std::string itemQuantityS = "0";
		int itemQuantity = 0;

		// Prompt for item info
		std::cout << "Item Manager" << std::endl;
		std::cout << "  Item #" << packingSlip->GetItemCount() << std::endl;
		std::cout << "    Name: [ENTER to Finish]: ";
		std::getline(std::cin, itemName);

		// Exit loop when user presses ENTER
		if(itemName == "")
			break;

		// Loop until valid quantity is given
		while(itemQuantity < 1) {
			try {
				std::cout << "    Quantity: ";
				std::getline(std::cin, itemQuantityS);
				itemQuantity = std::stoi(itemQuantityS);
			} catch(std::invalid_argument e) {
				std::cout << "      [Error] Invalid number." << std::endl;
				continue;
			} catch(std::out_of_range e) {
				std::cout << "      [Error] Number out of range." << std::endl;
				continue;
			}
			if(itemQuantity < 1)
				std::cout << "      [Error] Enter number greater than 0." << std::endl;
		}

		// Create item with properties above
		Item *newItem = new Item();
		newItem->SetName(itemName);
		newItem->SetQuantity(itemQuantity);
		
		// Add item attribute loop
		for(int i = 1; true; ++i) {

			std::string attribute;

			// Get attribute
			std::cout << "    Attributes (Optional)" << std::endl;
			std::cout << "      Attribute #" << i << " Text [ENTER to Finish]: ";
			std::getline(std::cin, attribute);

			// Exit loop when user presses ENTER
			if(attribute == "")
				break;

			// Add attribute
			newItem->AddAttribute(attribute);

		}

		// Add item to packingSlip
		packingSlip->AddItem(newItem);

	}

	// Get and print packing slip
	std::string slip = packingSlip->GenerateSlip();
	std::cout << slip;

	delete packingSlip;

	return 0;

}
