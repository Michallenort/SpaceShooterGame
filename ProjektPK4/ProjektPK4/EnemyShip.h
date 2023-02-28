#ifndef ENEMY_SHIP
#define ENEMY_SHIP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Obstacle.h"

class EnemyShip : public Obstacle
{
public:

	EnemyShip(sf::RenderWindow* window);
	~EnemyShip();

	int demage();

	void update();
	void draw(sf::RenderWindow* window);
};

#endif

