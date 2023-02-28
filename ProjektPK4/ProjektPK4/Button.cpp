#include <iostream>
#include "Button.h"

Button::Button(float x, float y, float width,
	float height, std::string text,
	sf::Color defaultColor, sf::Color hoverColor,
	sf::Color activeColor)
{
	buttonState = BtnStates::Normal;

	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));
	shape.setOrigin(shape.getSize().x / 2.f, shape.getSize().y / 2.f);

	if (!this->font.loadFromFile("Fonts/minecraft_font.ttf"))
	{
		std::cout << "Font cannot be loaded from a file!" << std::endl;
	}
	
	this->text.setFont(font);
	this->text.setCharacterSize(30);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setOrigin(
		this->text.getLocalBounds().width / 2.f,
		this->text.getLocalBounds().height / 2.f
	);
	this->text.setPosition(
		shape.getPosition().x,
		shape.getPosition().y
	);

	this->defaultColor = defaultColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	shape.setFillColor(defaultColor);
}

Button::~Button()
{
}

bool Button::isPressed()
{
	if (buttonState == BtnStates::Pressed)
		return true;

	return false;
}

void Button::update(sf::Vector2f cursorPosition)
{
	buttonState = BtnStates::Normal;

	if (this->shape.getGlobalBounds().contains(cursorPosition))
	{
		buttonState = BtnStates::Hover;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			buttonState = BtnStates::Pressed;
		}
	}

	switch (buttonState)
	{
	case BtnStates::Normal:
		shape.setFillColor(defaultColor);
		break;
	case BtnStates::Hover:
		shape.setFillColor(hoverColor);
		break;
	case BtnStates::Pressed:
		shape.setFillColor(activeColor);
		break;
	default:
		shape.setFillColor(sf::Color(169, 169, 169));
		break;
	}
}

void Button::draw(sf::RenderWindow* window)
{
	window->draw(this->shape);
	window->draw(this->text);
}
