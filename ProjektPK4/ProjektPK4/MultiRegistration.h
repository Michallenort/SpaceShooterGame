#ifndef MULTIREGISTRATION_H
#define MULTIREGISTRATION_H

#include <iostream>
#include <regex>
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Textbox.h"

class MultiRegistration
{
	sf::RectangleShape externalShape1;
	sf::RectangleShape internalShape1;
	sf::RectangleShape externalShape2;
	sf::RectangleShape internalShape2;

	Textbox* textInput1;
	Textbox* textInput2;

	Button* admitButton;
	sf::Vector2f mousePosition;

	std::string playerName1;
	std::string playerName2;

	sf::Font font;
	sf::Text informationText1;
	sf::Text informationText2;
	sf::Text errorText1;
	sf::Text errorText2;
public:
	MultiRegistration(sf::RenderWindow* window);
	~MultiRegistration();

	std::string getPlayerName1() const;
	std::string getPlayerName2() const;

	bool isCorrect(std::string name);

	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
	void run(sf::RenderWindow* window);
};

#endif

