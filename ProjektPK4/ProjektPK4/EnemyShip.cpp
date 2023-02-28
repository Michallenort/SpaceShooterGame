#include "EnemyShip.h"

EnemyShip::EnemyShip(sf::RenderWindow* window) : Obstacle("Textures/spaceShip.png")
{
	sprite.rotate(180);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, /*sprite.getGlobalBounds().height*/0);
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

	hp = 20;
	killPoints = 5;
}

EnemyShip::~EnemyShip()
{

}

int EnemyShip::demage()
{
	return 10;
}

void EnemyShip::update()
{
	sprite.move(0.f, 5.f);
	hpMax.move(0.f, 5.f);
	hpToDisplay.move(0.f, 5.f);

	hpToDisplay.setSize(sf::Vector2f(texture.getSize().x * sprite.getScale().x * hp / 20, 5));
}

void EnemyShip::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	window->draw(hpMax);
	window->draw(hpToDisplay);
}