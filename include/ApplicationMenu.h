#ifndef APPLICATION_MENU_HPP
#define APPLICATION_MENU_HPP

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>


class ApplicationMenu
{
private:
	ApplicationMenu();

	ApplicationMenu(const ApplicationMenu&) = delete;
	ApplicationMenu operator=(const ApplicationMenu&) = delete;

public:

	static ApplicationMenu getInstance();

};

#endif //APPLICATION_MENU_HPP