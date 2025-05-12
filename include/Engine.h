#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <optional>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "Graphics.h"
#include "exceptions.h"
#include "buttons/default_button_factory.h"
#include "AnchoredElement.h"

class Engine
{
private:
	void init();
	void initVariables();
	void uploadResources();
	void initWindow();
	
	Engine() = default;
	Engine operator=(const Engine&) = delete;
	Engine(const Engine&) = delete;

	std::unique_ptr<sf::RenderWindow> _window;
	sf::Event _event{};
	sf::VideoMode _videoMode;
	std::string _windowTitle;

	std::optional<AnchoredElement> _anchor;

	const std::string _fontPath = RESOURCES_DIR "fonts/defaultFont.otf";
	sf::Font _font;

	std::vector<std::unique_ptr<graphics::Button>> _buttons;

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