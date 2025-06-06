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
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

//A config through which you 
// can customize 
// the buttons 
// in the interface

enum class ButtonState { NORMAL, HOVERED, PRESSED, DISABLED };

struct ButtonConfig
{
	sf::Text title;

	sf::Color outlineColor;
	sf::Color normalColor;
	sf::Color hoverColor;
	sf::Color pressedColor;
	sf::Color disabledColor;

	std::string hoverSoundPath;
	std::string clickedSoundPath;

	std::function<void()> onClickAction;

	float outlineThickness;

	sf::Vector2f buttonSize;
	sf::Vector2f buttonPosition;

};

namespace graphics
{
	class Button
	{
		/*
			*Improvements for the future:
		1. audio processing

		2. animations

		3. Methods for resizing buttons

		4. Integration with the event system

		5. Performance optimization

		6. Multiplatform support

		7. Adding methods to get the current button state

		8. Checking for the necessary resources before creating the button

		9. ...
*/

	private:
		sf::RectangleShape _shape;
		ButtonConfig _config;
		ButtonState _state = ButtonState::NORMAL;
		bool _wasPressed = false;
		sf::Clock _clickTimer;
		float _clickDelay = 0.9f;

	public:
		explicit Button(const ButtonConfig& config);

		bool isClicked(const sf::Event& event) const;
		void setPosition(const sf::Vector2f& position);
		void setEnabled(bool enabled);
		sf::RectangleShape& getShape();
		ButtonConfig& getConfig();
		void render(sf::RenderTarget& target) const;
		void update(const sf::RenderWindow& window);
	};

	class TextField
	{
		/*
					*Improvements for the future:
				1. Add placeholder text

				2. Implement text selection

				3. Add multiline input support

				4. Optimize event handling
		*/

	private:
		sf::Clock _keyRepeatClock;
		sf::Font _font;

		sf::Text _text;
		sf::RectangleShape _background;

		sf::Color _activeColor;
		sf::Color _inactiveColor;

		bool _isActive;
		std::string _inputString;
		unsigned int _characterSize;
		unsigned int _maxLength;


	public:
		TextField();

		const std::string& getText() const;

		void setCharacterSize(unsigned int characterSize);
		void setSize(const float& width, const float& height);
		void setSize(const sf::Vector2f& size);
		void setMaxLength(unsigned int length);
		void setText(const std::string& text);
		void setPosition(sf::Vector2f position);

		void handleEvent(const sf::Event& event);
		void render(sf::RenderTarget& target) const;

	};
}



#endif //GRAPHICS_HPP