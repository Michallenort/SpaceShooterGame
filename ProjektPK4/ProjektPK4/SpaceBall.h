#ifndef SPACEBALL_H
#define SPACEBALL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Obstacle.h"

class SpaceBall : public Obstacle
{
public:
	SpaceBall(sf::RenderWindow* window);
	~SpaceBall();

	int demage();

	void update();
	void draw(sf::RenderWindow* window);
};

#endif

