#ifndef SATELITE_H
#define SATELITE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Obstacle.h"

class Satellite : public Obstacle
{
public:
	Satellite(sf::RenderWindow* window);
	~Satellite();

	int demage();

	void update();
	void draw(sf::RenderWindow* window);
};

#endif

