#include <iostream>
#include "Player.h"

Player::Player(std::string name, sf::Keyboard::Key keys[4],std::string texturePath, float scaleX, float scaleY)
{
	this->name = name;

	points = 0;
	hp = 100;

	if (!texture.loadFromFile(texturePath))
	{
		std::cout << "Texture cannot be loaded from file!" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.scale(scaleX, scaleY);

	for (int i = 0; i < 4; i++)
	{
		controllingKeys[i] = keys[i];
	}

	hpMax.setSize(sf::Vector2f(texture.getSize().x * scaleX, 5));
	hpMax.setOrigin(hpMax.getSize().x / 2, hpMax.getSize().y / 2);
	hpMax.setFillColor(sf::Color(125, 0, 0));

	hpToDisplay.setSize(sf::Vector2f(texture.getSize().x * scaleX, 5));
	hpToDisplay.setOrigin(hpToDisplay.getSize().x / 2, hpToDisplay.getSize().y / 2);
	hpToDisplay.setFillColor(sf::Color(255, 0, 0));
}

Player::~Player()
{

}

sf::Vector2f Player::getPosition() const
{
	return sprite.getPosition();
}

sf::FloatRect Player::getBounds() const
{
	return sprite.getGlobalBounds();
}

std::string Player::getName() const
{
	return name;
}

int Player::getPoints() const
{
	return points;
}

int Player::getHp() const
{
	return hp;
}

bool Player::getCanAttack() const
{
	return canAttack;
}

void Player::setCanAttack(bool value)
{
	canAttack = value;
}

void Player::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
	hpMax.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getGlobalBounds().height / 2);
	hpToDisplay.setPosition(sprite.getPosition().x, sprite.getPosition().y - sprite.getGlobalBounds().height / 2);
}

void Player::allowToAttack()
{
	if (canAttack == false)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		canAttack = true;
	}
}

void Player::addPoints(int newPoints)
{
	points += newPoints;
}

void Player::deductHp(int lostHp)
{
	hp -= lostHp;
}

bool Player::checkUpCollision(Player* player)
{
	if (getPosition().x - (getBounds().width / 2) < player->getPosition().x + (player->getBounds().width / 2)
		&& getPosition().x - (getBounds().width / 2) > player->getPosition().x - (player->getBounds().width / 2))
	{
		if (getPosition().y - (getBounds().height / 2) < player->getPosition().y + (player->getBounds().height / 2)
			&& getPosition().y - (getBounds().height / 2) > player->getPosition().y - (player->getBounds().height / 2))
			return true;
		else
			return false;
	}
	else if (getPosition().x + (getBounds().width / 2) > player->getPosition().x - (player->getBounds().width / 2)
		&& getPosition().x + (getBounds().width / 2) < player->getPosition().x + (player->getBounds().width / 2))
	{
		if (getPosition().y - (getBounds().height / 2) < player->getPosition().y + (player->getBounds().height / 2)
			&& getPosition().y - (getBounds().height / 2) > player->getPosition().y - (player->getBounds().height / 2))
			return true;
		else
			return false;
	}
	else if (getPosition().x == player->getPosition().x)
	{
		if (getPosition().y - (getBounds().height / 2) < player->getPosition().y + (player->getBounds().height / 2)
			&& getPosition().y - (getBounds().height / 2) > player->getPosition().y - (player->getBounds().height / 2))
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Player::checkDownCollision(Player* player)
{
	if (getPosition().x - (getBounds().width / 2) < player->getPosition().x + (player->getBounds().width / 2)
		&& getPosition().x - (getBounds().width / 2) > player->getPosition().x - (player->getBounds().width / 2))
	{
		if (getPosition().y + (getBounds().height / 2) > player->getPosition().y - (player->getBounds().height / 2)
			&& getPosition().y + (getBounds().height / 2) < player->getPosition().y + (player->getBounds().height / 2))
			return true;
		else
			return false;
	}
	else if (getPosition().x + (getBounds().width / 2) > player->getPosition().x - (player->getBounds().width / 2)
		&& getPosition().x + (getBounds().width / 2) < player->getPosition().x + (player->getBounds().width / 2))
	{
		if (getPosition().y + (getBounds().height / 2) > player->getPosition().y - (player->getBounds().height / 2)
			&& getPosition().y + (getBounds().height / 2) < player->getPosition().y + (player->getBounds().height / 2))
			return true;
		else
			return false;
	}
	else if (getPosition().x == player->getPosition().x)
	{
		if (getPosition().y + (getBounds().height / 2) > player->getPosition().y - (player->getBounds().height / 2)
			&& getPosition().y + (getBounds().height / 2) < player->getPosition().y + (player->getBounds().height / 2))
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Player::checkLeftCollision(Player* player)
{
	if (getPosition().y - (getBounds().height / 2) < player->getPosition().y + (player->getBounds().height / 2)
		&& getPosition().y - (getBounds().height / 2) > player->getPosition().y - (player->getBounds().height / 2))
	{
		if (getPosition().x - (getBounds().width / 2) < player->getPosition().x + (player->getBounds().width / 2)
			&& getPosition().x - (getBounds().width / 2) > player->getPosition().x - (player->getBounds().width / 2))
			return true;
		else
			return false;
	}
	else if (getPosition().y + (getBounds().height / 2) > player->getPosition().y - (player->getBounds().height / 2)
		&& getPosition().y + (getBounds().height / 2) < player->getPosition().y + (player->getBounds().height / 2))
	{
		if (getPosition().x - (getBounds().width / 2) < player->getPosition().x + (player->getBounds().width / 2)
			&& getPosition().x - (getBounds().width / 2) > player->getPosition().x - (player->getBounds().width / 2))
			return true;
		else
			return false;
	}
	else if (getPosition().y == player->getPosition().y)
	{
		if (getPosition().x - (getBounds().width / 2) < player->getPosition().x + (player->getBounds().width / 2)
			&& getPosition().x - (getBounds().width / 2) > player->getPosition().x - (player->getBounds().width / 2))
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Player::checkRightCollision(Player* player)
{
	if (getPosition().y - (getBounds().height / 2) < player->getPosition().y + (player->getBounds().height / 2)
		&& getPosition().y - (getBounds().height / 2) > player->getPosition().y - (player->getBounds().height / 2))
	{
		if (getPosition().x + (getBounds().width / 2) > player->getPosition().x - (player->getBounds().width / 2)
			&& getPosition().x + (getBounds().width / 2) < player->getPosition().x + (player->getBounds().width / 2))
			return true;
		else
			return false;
	}
	else if (getPosition().y + (getBounds().height / 2) > player->getPosition().y - (player->getBounds().height / 2)
		&& getPosition().y + (getBounds().height / 2) < player->getPosition().y + (player->getBounds().height / 2))
	{
		if (getPosition().x + (getBounds().width / 2) > player->getPosition().x - (player->getBounds().width / 2)
			&& getPosition().x + (getBounds().width / 2) < player->getPosition().x + (player->getBounds().width / 2))
			return true;
		else
			return false;
	}
	else if (getPosition().y == player->getPosition().y)
	{
		if (getPosition().x + (getBounds().width / 2) > player->getPosition().x - (player->getBounds().width / 2)
			&& getPosition().x + (getBounds().width / 2) < player->getPosition().x + (player->getBounds().width / 2))
			return true;
		else
			return false;
	}
	else
		return false;
}

void Player::update(sf::RenderWindow* window)
{
	if (sf::Keyboard::isKeyPressed(controllingKeys[0]) && (getPosition().y - (getBounds().height / 2)) > 0.f)
	{
		sprite.move(0.f, -10.f);
		hpMax.move(0.f, -10.f);
		hpToDisplay.move(0.f, -10.f);
	}
		
	if (sf::Keyboard::isKeyPressed(controllingKeys[1]) && (getPosition().y + (getBounds().height / 2)) < window->getSize().y)
	{
		sprite.move(0.f, 10.f);
		hpMax.move(0.f, 10.f);
		hpToDisplay.move(0.f, 10.f);
	}

	if (sf::Keyboard::isKeyPressed(controllingKeys[2]) && (getPosition().x - (getBounds().width / 2)) > 0.f)
	{
		sprite.move(-10.f, 0.f);
		hpMax.move(-10.f, 0.f);
		hpToDisplay.move(-10.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(controllingKeys[3]) && (getPosition().x + (getBounds().width / 2)) < window->getSize().x)
	{
		sprite.move(10.f, 0.f);
		hpMax.move(10.f, 0.f);
		hpToDisplay.move(10.f, 0.f);
	}

	hpToDisplay.setSize(sf::Vector2f(texture.getSize().x * sprite.getScale().x * hp / 100, 5));
}

void Player::update(sf::RenderWindow* window, Player* player)
{
	if (sf::Keyboard::isKeyPressed(controllingKeys[0]) && (getPosition().y - (getBounds().height / 2)) > 0.f && !checkUpCollision(player))
	{
		sprite.move(0.f, -10.f);
		hpMax.move(0.f, -10.f);
		hpToDisplay.move(0.f, -10.f);
	}

	if (sf::Keyboard::isKeyPressed(controllingKeys[1]) && (getPosition().y + (getBounds().height / 2)) < window->getSize().y && !checkDownCollision(player))
	{
		sprite.move(0.f, 10.f);
		hpMax.move(0.f, 10.f);
		hpToDisplay.move(0.f, 10.f);
	}

	if (sf::Keyboard::isKeyPressed(controllingKeys[2]) && (getPosition().x - (getBounds().width / 2)) > 0.f && !checkLeftCollision(player))
	{
		sprite.move(-10.f, 0.f);
		hpMax.move(-10.f, 0.f);
		hpToDisplay.move(-10.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(controllingKeys[3]) && (getPosition().x + (getBounds().width / 2)) < window->getSize().x && !checkRightCollision(player))
	{
		sprite.move(10.f, 0.f);
		hpMax.move(10.f, 0.f);
		hpToDisplay.move(10.f, 0.f);
	}

	hpToDisplay.setSize(sf::Vector2f(texture.getSize().x * sprite.getScale().x * hp / 100, 5));
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	window->draw(hpMax);
	window->draw(hpToDisplay);
}
