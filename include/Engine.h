#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <memory>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Graphics.h"

class Engine
{
private:
	void init();
	void initVariables();
	void initWindow();

	Engine() = default;
	Engine operator=(const Engine&) = delete;
	Engine(const Engine&) = delete;

	std::unique_ptr<sf::RenderWindow> _window;
	sf::Event _event;
	sf::VideoMode _videoMode;
	std::string _windowTitle;

public:
	static Engine& getInstance();

	~Engine()
	{
		if (_window && _window->isOpen())
		{
			_window->close();
		}
	}
	
	void handleInput();
	void run();
	void render();
	void update();
};

#endif //ENGINE_HPP