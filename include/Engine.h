#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <memory>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "InterfaceElements.h"

class Engine
{
private:
	void initVariables();
	void initWindow();

	Engine();
	
	Engine operator=(const Engine&) = delete;
	Engine(const Engine&) = delete;

	std::unique_ptr<sf::RenderWindow> _window;
	
	sf::VideoMode _videoMode;

	std::string _windowTitle;

	bool _isOpen;

public:
	static Engine& getInstance();
	
	void handleInput();

	void run();

	void render();

	void update();
};

#endif //ENGINE_HPP