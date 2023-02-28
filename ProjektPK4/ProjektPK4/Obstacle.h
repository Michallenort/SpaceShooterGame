#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Obstacle
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	int hp;
	sf::RectangleShape hpToDisplay;
	sf::RectangleShape hpMax;
	int killPoints;

	int attackBreak = 0;
public:
	Obstacle(std::string path);
	~Obstacle();

	sf::FloatRect getBounds() const;
	int getHp() const;
	int getKillPoints() const;

	void deductHp(int lostHp);

	virtual int demage() = 0;

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow* window) = 0;
};

#endif