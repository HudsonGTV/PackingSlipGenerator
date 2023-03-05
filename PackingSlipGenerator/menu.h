#ifndef MENU_H
#define MENU_H

class Menu {

private:
	std::string m_title = "Undefined";

public:
	Menu(std::string title);

	void DisplayMenu(std::string buffer);

};

#endif
