#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

enum class BtnStates { Normal, Hover, Pressed };

class Button
{
	BtnStates buttonState;

	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;

	sf::Color defaultColor;
	sf::Color hoverColor;
	sf::Color activeColor;
public:
	Button(float x, float y, float width,
		float height, std::string text,
		sf::Color defaultColor, sf::Color hoverColor,
		sf::Color activeColor);
	~Button();

	bool isPressed();

	void update(sf::Vector2f cursorPosition);
	void draw(sf::RenderWindow* window);

};

#endif