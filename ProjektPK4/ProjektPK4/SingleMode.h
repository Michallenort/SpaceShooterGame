#ifndef SINGLEMODE_H
#define SINGLEMODE_H

#include <iostream>
#include <list>
#include <thread>
#include <mutex>
#include <filesystem>
#include <fstream>
#include "GameMode.h"
#include "Player.h"
#include "Shot.h"
#include "Obstacle.h"
#include "Rock.h"
#include "Satellite.h"
#include "EnemyShip.h"
#include "SpaceBall.h"

class SingleMode : public GameMode
{
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Font font;
	sf::Text pointsText;
	sf::Text endText;

	Player* player;

	sf::Keyboard::Key controllingKeys[4] = {sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right};

	std::list<Shot*> shots;
	std::list<Obstacle*> obstacles;

	int spawnBreak;
	int spawnTimer;
	int obstacleType;

	int killedEnemies;

	bool threadExist;

	void constructBackground();
	void constructInformations(sf::RenderWindow* window);
	void constructSpawning();
public:
	SingleMode(sf::RenderWindow* window, std::string playerName);
	~SingleMode();

	void changeDifficulty();

	void updateEvents(sf::RenderWindow* window);
	void updateShots(sf::RenderWindow* window);
	void updateObstacles(sf::RenderWindow* window);
	void updateAttack();
	void updateInformations();

	void saveResultToFile();

	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
	void run(sf::RenderWindow* window);
};
#endif

