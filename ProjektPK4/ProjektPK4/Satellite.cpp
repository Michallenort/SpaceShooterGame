#include "Satellite.h"

Satellite::Satellite(sf::RenderWindow* window) : Obstacle("Textures/satellite.png")
{
	sprite.scale(0.4, 0.4);

	hpMax.setSize(sf::Vector2f(texture.getSize().x * 0.4, 5));
	hpMax.setOrigin(hpMax.getSize().x / 2, hpMax.getSize().y / 2);
	hpMax.setFillColor(sf::Color(0, 125, 0));

	hpToDisplay.setSize(sf::Vector2f(texture.getSize().x * 0.4, 5));
	hpToDisplay.setOrigin(hpToDisplay.getSize().x / 2, hpToDisplay.getSize().y / 2);
	hpToDisplay.setFillColor(sf::Color(0, 255, 0));

	float posX = rand() % (window->getSize().x - texture.getSize().x) + (texture.getSize().x / 2);
	sprite.setPosition(sf::Vector2f(posX, 0.f));

	hpMax.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getGlobalBounds().height);
	hpToDisplay.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getGlobalBounds().height);

	hp = 30;
	killPoints = 3;
}

Satellite::~Satellite()
{

}

int Satellite::demage()
{
	return 10;
}

void Satellite::update()
{
	sprite.move(0.f, 5.f);
	hpMax.move(0.f, 5.f);
	hpToDisplay.move(0.f, 5.f);

	hpToDisplay.setSize(sf::Vector2f(texture.getSize().x * sprite.getScale().x * hp / 30, 5));
}

void Satellite::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	window->draw(hpMax);
	window->draw(hpToDisplay);
}