#ifndef MULTIMODE_H
#define MULTIMODE_H

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

class MultiMode : public GameMode
{
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Font font;
	sf::Text pointsText1;
	//sf::Text pointsText2;
	sf::Text endText;

	Player* player1;
	Player* player2;

	sf::Keyboard::Key controllingKeys1[4] = { sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right };
	sf::Keyboard::Key controllingKeys2[4] = { sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D };

	std::list<Shot*> shots;

	std::list<Obstacle*> obstacles;

	int spawnBreak;
	int spawnTimer;
	int obstacleType;

	int killedEnemies;

	bool threadExist1;
	bool threadExist2;

	void constructBackground();
	void constructInformations(sf::RenderWindow* window);
	void constructSpawning();
public:
	MultiMode(sf::RenderWindow* window, std::string playerName1, std::string playerName2);
	~MultiMode();

	void changeDifficulty();
	void updateEvents(sf::RenderWindow* window);
	void updateShooting1(sf::RenderWindow* window);
	void updateShooting2(sf::RenderWindow* window);
	void updateShots();
	void updateObstacles(sf::RenderWindow* window);
	void updateCollision1(sf::RenderWindow* window);
	void updateCollision2(sf::RenderWindow* window);
	void updateAttack();
	void updateInformations();

	void saveResultToFile();

	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
	void run(sf::RenderWindow* window);
};

#endif

