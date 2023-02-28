#ifndef SINGLEREGISTRATION_H
#define SINGLEREGISTRATION_H

#include <iostream>
#include <regex>
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Textbox.h"

class SingleRegistration
{
	sf::RectangleShape externalShape;
	sf::RectangleShape internalShape;

	Textbox* textInput;
	Button* admitButton;
	sf::Vector2f mousePosition;

	std::string playerName;

	sf::Font font;
	sf::Text informationText;
	sf::Text errorText;
public:
	SingleRegistration(sf::RenderWindow* window);
	~SingleRegistration();

	std::string getPlayerName() const;

	bool isCorrect(std::string name);

	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
	void run(sf::RenderWindow* window);
};

#endif

