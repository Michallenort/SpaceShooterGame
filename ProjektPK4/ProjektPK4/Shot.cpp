#include "Shot.h"

Shot::Shot(float x, float y, float speedX, float speedY)
{
	if (!texture.loadFromFile("Textures/fireball.png"))
	{
		std::cout << "Texture cannot be loaded from file!" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.scale(0.05f, 0.05f);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.rotate(180);
	sprite.setPosition(x, y);

	this->speedX = speedX;
	this->speedY = speedY;
}

Shot::~Shot()
{

}

sf::FloatRect Shot::getBounds() const
{
	return sprite.getGlobalBounds();
}

void Shot::update()
{
	sprite.move(speedX, speedY);
}

void Shot::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

