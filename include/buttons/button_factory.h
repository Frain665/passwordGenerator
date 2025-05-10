#ifndef BUTTON_FACTORY
#define BUTTON_FACTORY

#include "Graphics.h"

#include <memory>

class ButtonFactory
{
public:
	virtual ~ButtonFactory() = default;

	virtual std::unique_ptr<graphics::Button> createButton(
		const std::string& text,
		const sf::Vector2f& position,
		const sf::Vector2f& size
	) const = 0;
};

#endif //BUTTON_FACTORY