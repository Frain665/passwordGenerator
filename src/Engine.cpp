#include "Engine.h"
#include <AnchoredElement.h>

void Engine::initVariables()
{
	_windowTitle = "Password Generator";
	_window = nullptr;
	_event = {};
	
}

void Engine::uploadResources()
{
	if (!_font.loadFromFile(_fontPath))
	{
		throw FontException(_fontPath);
	}

	DefaultButtonFactory defaultButtonFactory(_font);

	auto startButton = defaultButtonFactory.createButton("Generate", { 300, 100 });

	_buttons.push_back(std::move(startButton));

	AnchoredElement anchor(
		AnchorHorizontal::RIGHT,
		AnchorVertical::BOTTOM,
		{ -20, -20 },
		{ 100, 50 },
		[&startButton](const sf::Vector2f& pos, const sf::Vector2f& size) {
			startButton->getShape().setPosition(pos);
			startButton->getShape().setSize(size);
		}
	);

	_anchor = anchor;
}

void Engine::initWindow()
{
	_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600),
		_windowTitle, sf::Style::Close | sf::Style::Titlebar);
	_window->setFramerateLimit(60);

	if (!_window)
	{
		throw WindowNotInitializedException("Game::initWindow() -> ");
	}
}

void Engine::init()
{
	initVariables();
	uploadResources();

	try
	{
		initWindow();
	}
	catch (const WindowNotInitializedException& exception)
	{
		std::cerr << "CRITICAL: " << exception.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	catch (const FileLoadException& exception)
	{
		std::cerr << "RESOURCE ERROR: " << exception.what() << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cerr << "UNKNOWN ERROR: " << exception.what() << std::endl;
	}
}

void Engine::update()
{
	this->handleInput();

	for (auto const& button : _buttons)
	{
		button->update(*_window);
	}
}

void Engine::render()
{
	_window->clear();

	for (auto const& button : _buttons)
	{
		button->render(*_window);
	}

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
		case sf::Event::Resized:
			_anchor.update(_window->getSize());
		default:
			break;
		}
	}
}

void Engine::run()
{
	init();

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