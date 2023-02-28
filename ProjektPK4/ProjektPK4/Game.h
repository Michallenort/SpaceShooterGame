#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Menu.h"

class Game
{
	sf::RenderWindow* window;
	Menu* menu;
public:
	Game();
	~Game();

	void update();
	void render();

	void run();
};

#endif
