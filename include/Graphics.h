#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <iostream>
#include <string>
#include <functional>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

//#include <SFML/System/Vector2.hpp>

//A config through which you 
// can customize 
// the buttons 
// in the interface

enum class ButtonState { NONE, NORMAL, HOVERED, PRESSED, DISABLED };

struct ButtonConfig
{
	sf::Text title;

	sf::Vector2f size;
	sf::Vector2f position;

	sf::Color outLineColor;
	sf::Color normalColor;
	sf::Color hoverColor;
	sf::Color pressedColor;
	sf::Color disabledColor;

	std::string hoverSoundPath;
	std::string clickedSoundPath;

	std::function<void()> onClickAction;

	unsigned int outlineThickness;
	unsigned int buttonSize;

	float buttonPosition;

};

namespace graphics
{
	class Button
	{
	private:
		void initVariables();

		sf::RectangleShape _shape;
		ButtonConfig _config;
		ButtonState _state;

	public:
		explicit Button();

		bool isClicked(const sf::Event& event) const;
		void setPosition(const sf::Vector2f& position);
		void render(sf::RenderTarget& target);
		void update(const sf::RenderWindow& window);
	};

	class TextField
	{
	private:
		sf::Text _text;
		sf::Texture _background;
		bool _isActive;

	public:
		TextField();

		void setText(const std::string& text);
		void handleEvent(const sf::Event& event);
		void render(sf::RenderTarget& target) const;

	};
}



#endif //GRAPHICS_HPP