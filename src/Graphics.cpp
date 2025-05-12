#include "Graphics.h"
#include <exceptions.h>

graphics::TextField::TextField()
	: _isActive(false),
	_characterSize(24),
	_activeColor(sf::Color::White),
	_inactiveColor(sf::Color(180, 180, 180)),
	_maxLength(20)
{
	if (!_font.loadFromFile("resources/fonts/defaultFont.otf"))
	{
		throw FontException("resources/fonts/defaultFont.otf");
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
		auto mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
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

graphics::Button::Button(const ButtonConfig& config)
	:_config(config)
{
	_shape.setSize(_config.buttonSize);
	_shape.setPosition(_config.buttonPosition);
	_shape.setFillColor(_config.normalColor);
	_shape.setOutlineThickness(_config.outlineThickness);
	_shape.setOutlineColor(_config.outlineColor);

	_config.title.setPosition(
		_config.buttonPosition.x + _config.buttonSize.x / 2 - _config.title.getGlobalBounds().width / 2,
		_config.buttonPosition.y + _config.buttonSize.y / 2 - _config.title.getGlobalBounds().height / 2
	);
}

bool graphics::Button::isClicked(const sf::Event& event) const
{
	return false;
}

void graphics::Button::setPosition(const sf::Vector2f& position)
{
	_config.buttonPosition = position;
	_shape.setPosition(position);
	_config.title.setPosition(
		position.x + _shape.getSize().x / 2 - _config.title.getGlobalBounds().width / 2,
		position.y + _shape.getSize().y / 2 - _config.title.getGlobalBounds().height / 2
	);
}

void graphics::Button::setEnabled(bool enabled)
{
	_state = enabled ? ButtonState::NORMAL : ButtonState::DISABLED;
}

sf::RectangleShape& graphics::Button::getShape()
{
	return _shape;
}

void graphics::Button::render(sf::RenderTarget& target) const
{
	target.draw(_shape);
	target.draw(_config.title);
}

void graphics::Button::update(const sf::RenderWindow& window)
{
	if (_state == ButtonState::DISABLED) return;

	auto mousePos = sf::Mouse::getPosition(window);
	bool contains = _shape.getGlobalBounds().contains(
		static_cast<float>(mousePos.x),
		static_cast<float>(mousePos.y)
	);

	if (contains)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			_state = ButtonState::PRESSED;
			_wasPressed = true;
		}
		else
		{
			_state = _wasPressed ? ButtonState::PRESSED : ButtonState::HOVERED;
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && _wasPressed)
		{
			if (_config.onClickAction) _config.onClickAction();
			_wasPressed = false;
		}
	}
	else
	{
		_state = ButtonState::NORMAL;
		_wasPressed = false;
	}

	switch (_state)
	{
	case ButtonState::HOVERED:
		_shape.setFillColor(_config.hoverColor);
		break;
	case ButtonState::PRESSED:
		_shape.setFillColor(_config.pressedColor);
		break;
	case ButtonState::DISABLED:
		_shape.setFillColor(_config.disabledColor);
		break;
	default:
		_shape.setFillColor(_config.normalColor);
	}
}
