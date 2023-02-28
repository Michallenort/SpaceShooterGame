#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <SFML/Graphics.hpp>

class GameMode
{
public:
	virtual void update(sf::RenderWindow* window) = 0;
	virtual void render(sf::RenderWindow* window) = 0;
	virtual void run(sf::RenderWindow* window) = 0;
};

#endif

