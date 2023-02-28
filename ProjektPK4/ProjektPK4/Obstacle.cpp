#include "Obstacle.h"

Obstacle::Obstacle(std::string path)
{
	if (!texture.loadFromFile(path))
	{
		std::cout << "Texture cannot be loaded from file!" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height);
	//sprite.setPosition(sf::Vector2f(x, y));


	hp = 0;
	killPoints = 0;
}

Obstacle::~Obstacle()
{

}

sf::FloatRect Obstacle::getBounds() const
{
	return sprite.getGlobalBounds();
}


int Obstacle::getHp() const
{
	return hp;
}

int Obstacle::getKillPoints() const
{
	return killPoints;
}

void Obstacle::deductHp(int lostHp)
{
	hp -= lostHp;
}

