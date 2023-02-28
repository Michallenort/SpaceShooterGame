#ifndef ROCK_H
#define ROCK_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include  "Obstacle.h"

class Rock : public Obstacle
{
public:
	Rock(sf::RenderWindow* window);
	~Rock();

	int demage();

	void update();
	void draw(sf::RenderWindow* window);
};

#endif

