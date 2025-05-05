#include "Engine.h"

void Engine::initVariables()
{
	_windowTitle = "Password Generator";
	_window = nullptr;
	_event = {};
	
}

void Engine::initWindow()
{
	_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600),
		_windowTitle, sf::Style::Close | sf::Style::Titlebar);
	_window->setFramerateLimit(60);
}

void Engine::init()
{
	initVariables();
	initWindow();
}

void Engine::update()
{
	this->handleInput();
}

void Engine::render()
{
	_window->clear();

	_window->display();
}

void Engine::handleInput()
{

	while (_window->pollEvent(_event))
	{
		switch (_event.type)
		{
		case sf::Event::Closed:
			_window->close();
			break;
		case sf::Event::KeyPressed:
			if (_event.key.code == sf::Keyboard::Escape)
			{
				_window->close();
			}
			break;
		default:
			break;
		}
	}
}

void Engine::run()
{
	init();

	if (!_window)
	{
		throw std::runtime_error("Window is not initialized!");
	}

	while (_window->isOpen())
	{
		update();
		render();
	}
}

Engine& Engine::getInstance()
{
	static Engine instance;
	return instance;
}