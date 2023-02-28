#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameMode.h"
#include "SingleMode.h"
#include "MultiMode.h"

#define OPTIONS_NUMBER 4

class Menu
{
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Font titleFont;
	sf::Text titleText;

	sf::Vector2f mousePosition;

	Button* singleModeBtn;
	Button* multiModeBtn;
	Button* rankingBtn;
	Button* exitBtn;

	GameMode* mode = NULL;

	void constructBackground();
	void constructTitle(float width, float height);
	void constructButtons(float width, float height);
public:
	Menu(float width, float height);
	~Menu();

	void update(sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
};

#endif

