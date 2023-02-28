#include "SpaceBall.h"

SpaceBall::SpaceBall(sf::RenderWindow* window) : Obstacle("Textures/spaceBall.png")
{
	sprite.scale(0.3, 0.3);

	hpMax.setSize(sf::Vector2f(texture.getSize().x * 0.3, 5));
	hpMax.setOrigin(hpMax.getSize().x / 2, hpMax.getSize().y / 2);
	hpMax.setFillColor(sf::Color(0, 125, 0));

	hpToDisplay.setSize(sf::Vector2f(texture.getSize().x * 0.3, 5));
	hpToDisplay.setOrigin(hpToDisplay.getSize().x / 2, hpToDisplay.getSize().y / 2);
	hpToDisplay.setFillColor(sf::Color(0, 255, 0));

	float posX = rand() % (window->getSize().x - texture.getSize().x) + (texture.getSize().x / 2);
	sprite.setPosition(sf::Vector2f(posX, 0.f));

	hpMax.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getGlobalBounds().height);
	hpToDisplay.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getGlobalBounds().height);

	hp = 60;
	killPoints = 6;
}

SpaceBall::~SpaceBall()
{

}

int SpaceBall::demage()
{
	return 30;
}

void SpaceBall::update()
{
	sprite.move(0.f, 5.f);
	hpMax.move(0.f, 5.f);
	hpToDisplay.move(0.f, 5.f);

	hpToDisplay.setSize(sf::Vector2f(texture.getSize().x * sprite.getScale().x * hp / 60, 5));
}

void SpaceBall::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	window->draw(hpMax);
	window->draw(hpToDisplay);
}