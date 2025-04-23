#include "Engine.h"

void Engine::initVariables()
{
	this->_isOpen = false;

	this->_windowTitle = "Password Generator";
}

void Engine::initWindow()
{
	this->_settings.antialiasingLevel = 4;
	this->_videoMode.height = WINDOW_HEIGHT;
	this->_videoMode.width = WINDOW_WIDTH;
	this->_window = std::make_unique<sf::RenderWindow>(this->_videoMode,
		this->_windowTitle, sf::Style::Close | sf::Style::Titlebar, this->_settings);
	this->_window->setFramerateLimit(60);
}

void Engine::update()
{
	this->handleInput();

}

void Engine::render()
{
	this->_window->clear();

	//this->_window->draw(/*some code*/);

	this->_window->display();
}

void Engine::handleInput()
{
	sf::Event event;

	switch (event.type)
	{
	case sf::Event::Closed:
		this->_window->close();
		this->_isOpen = false;
		break;
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Escape)
			this->_window->close();
		this->_isOpen = false;
		break;
	default:
		break;
	}
}

void Engine::run()
{
	while (this->_isOpen)
	{
		this->update();
		this->render();
	}
}

Engine::Engine()
{
	this->initVariables();
	this->initWindow();
}

Engine& Engine::getInstance()
{
	static Engine instance;
	return instance;
}