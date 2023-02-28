#ifndef SHOT_H
#define SHOT_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Shot
{
	sf::Sprite sprite;
	sf::Texture texture;

	float speedX;
	float speedY;
public:
	Shot(float x, float y, float speedX, float speedY);
	~Shot();

	sf::FloatRect getBounds() const;

	void update();
	void draw(sf::RenderWindow* window);
};

#endif

