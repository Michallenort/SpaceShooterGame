#include "Rock.h"

Rock::Rock(sf::RenderWindow* window) : Obstacle("Textures/rock.png")
{
	sprite.scale(0.5, 0.5);

	hpMax.setSize(sf::Vector2f(texture.getSize().x * 0.5, 5));
	hpMax.setOrigin(hpMax.getSize().x / 2, hpMax.getSize().y / 2);
	hpMax.setFillColor(sf::Color(0, 125, 0));

	hpToDisplay.setSize(sf::Vector2f(texture.getSize().x * 0.5, 5));
	hpToDisplay.setOrigin(hpToDisplay.getSize().x / 2, hpToDisplay.getSize().y / 2);
	hpToDisplay.setFillColor(sf::Color(0, 255, 0));

	float posX = rand() % (window->getSize().x - texture.getSize().x) + (texture.getSize().x / 2);
	sprite.setPosition(sf::Vector2f(posX, 0.f));

	hpMax.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getGlobalBounds().height);
	hpToDisplay.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getGlobalBounds().height);

	hp = 50;
	killPoints = 5;
}

Rock::~Rock()
{

}

int Rock::demage()
{
	return 20;
}

void Rock::update()
{
	sprite.move(0.f, 5.f);
	hpMax.move(0.f, 5.f);
	hpToDisplay.move(0.f, 5.f);

	hpToDisplay.setSize(sf::Vector2f(texture.getSize().x * sprite.getScale().x * hp / 50, 5));
}

void Rock::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	window->draw(hpMax);
	window->draw(hpToDisplay);
}