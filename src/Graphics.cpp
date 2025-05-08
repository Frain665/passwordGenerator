#include "Graphics.h"

graphics::TextField::TextField()
	: _isActive(false),
	_characterSize(24),
	_activeColor(sf::Color::White),
	_inactiveColor(sf::Color(180, 180, 180)),
	_maxLength(20)
{
	if (!_font.loadFromFile("PathToFont"))
	{
		std::cerr << "Failed to load font using the PathToFont path" << std::endl;
	}

	_text.setFont(_font);
	_text.setCharacterSize(_characterSize);
	_text.setFillColor(_inactiveColor);
	_text.setPosition(sf::Vector2f(50.f, 100.f));

	_background.setSize(sf::Vector2f(100.f, 50.f));
	_background.setFillColor(sf::Color::Transparent);
	_background.setOutlineThickness(2.f);
	_background.setOutlineColor(_inactiveColor);
}

void graphics::TextField::setPosition(sf::Vector2f position)
{
	_background.setPosition(position);
	_text.setPosition(position.x + 10.f, position.y + 10);
}

const std::string& graphics::TextField::getText() const
{
	return _inputString;
}

void graphics::TextField::setCharacterSize(unsigned int characterSize) 
{
	_characterSize = characterSize;
	_text.setCharacterSize(characterSize);
}

void graphics::TextField::setSize(float width, float height)
{
	_background.setSize(sf::Vector2f(width, height));
}

void graphics::TextField::setMaxLength(unsigned int length)
{
	_maxLength = length;
}

void graphics::TextField::setText(const std::string& text)
{
	_inputString = text;
	_text.setString(_inputString);
}

void graphics::TextField::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
		_isActive = _background.getGlobalBounds().contains(mousePos);

		_text.setFillColor(_isActive ? _activeColor : _inactiveColor);
		_background.setOutlineColor(_isActive ? _activeColor : _inactiveColor);
	}

	if (_isActive && event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode < 128)
		{
			if (event.text.unicode == '\b')
			{
				if (!_inputString.empty())
					_inputString.pop_back();
			}
			else if (_inputString.size() < _maxLength)
			{
				_inputString += static_cast<char>(event.text.unicode);
			}

			_text.setString(_inputString);
		}
	}
}

void graphics::TextField::render(sf::RenderTarget& target) const
{
	target.draw(_background);
	target.draw(_text);
}
