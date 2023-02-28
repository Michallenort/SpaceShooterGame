#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

class Textbox
{
	sf::Font font;
	sf::Text textbox;
	std::stringstream text;

	bool isSelected = false;
	bool hasLimit = false;
	int limit;



public:

	Textbox(int size, sf::Color color, bool sel, sf::Vector2f pos);


	void setFont(sf::Font& font);
	void setPosition(sf::Vector2f pos);
	void setLimit(bool hl);
	void setLimit(bool hl, int lim);
	void setSelected(bool sel);

	bool getSelected() const;
	std::string getText();

	void inputCharacter(int charTyped);
	void deleteCharacter();

	void draw(sf::RenderWindow* window);
	void update(sf::Event input);
};



#endif