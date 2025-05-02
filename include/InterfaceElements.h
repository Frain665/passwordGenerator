#ifndef INTERFACE_ELEMENTS_HPP
#define INTERFACE_ELEMENTS_HPP

#include <iostream>


class InterfaceElements
{
private:
	void initVariables();
	

	InterfaceElements();

	InterfaceElements(const InterfaceElements&) = delete;
	InterfaceElements operator=(const InterfaceElements) = delete;
	
public:

	static InterfaceElements& getInstance();

	void renderInterfaceElements();

	void updateInterfaceElements();
};

#endif //INTERFACE_ELEMENTS_HPP