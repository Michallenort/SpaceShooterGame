#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <thread>
#include <mutex>
#include <iostream>

class Player
{
	std::string name;
	int points;
	int hp;
	sf::RectangleShape hpToDisplay;
	sf::RectangleShape hpMax;

	sf::Sprite sprite;
	sf::Texture texture;
	sf::Keyboard::Key controllingKeys[4];

	int attackBreak = 10;

	bool canAttack = false;
public:

	Player(std::string name, sf::Keyboard::Key keys[4], std::string texturePath, float scaleX, float scaleY);
	~Player();

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;
	std::string getName() const;
	int getPoints() const;
	int getHp() const;
	bool getCanAttack() const;

	void setCanAttack(bool value);
	void setPosition(float x, float y);
	//void setAttackBreak(int value);

	//bool isAttackPossible();
	void allowToAttack();
	void addPoints(int newPoints);
	void deductHp(int lostHp);

	bool checkUpCollision(Player* player);
	bool checkDownCollision(Player* player);
	bool checkLeftCollision(Player* player);
	bool checkRightCollision(Player* player);

	void update(sf::RenderWindow* window);
	void update(sf::RenderWindow* window, Player* player);
	void draw(sf::RenderWindow* window);
};

#endif

