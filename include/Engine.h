#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <string>

#include <SFMl/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "ApplicationMenu.h"

constexpr const int WINDOW_HEIGHT = 600;
constexpr const int WINDOW_WIDTH = 800;

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
	sf::ContextSettings _settings;

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