#include "MultiMode.h"

void MultiMode::constructBackground()
{
	if (!backgroundTexture.loadFromFile("Textures/space.jpg"))
	{
		std::cout << "Texture downloading error" << std::endl;
	}

	backgroundSprite.scale(0.58, 0.7);
	backgroundSprite.setTexture(backgroundTexture);
}

void MultiMode::constructInformations(sf::RenderWindow* window)
{
	if (!this->font.loadFromFile("Fonts/minecraft_font.ttf"))
	{
		std::cout << "Font cannot be loaded from a file!" << std::endl;
	}

	pointsText1.setFont(font);
	pointsText1.setCharacterSize(30);
	pointsText1.setString("POINTS: " + std::to_string(0));
	pointsText1.setFillColor(sf::Color::Yellow);
	pointsText1.setStyle(sf::Text::Bold);
	pointsText1.setPosition(5, 5);

	//pointsText2.setFont(font);
	//pointsText2.setCharacterSize(30);
	//pointsText2.setString("POINTS: " + std::to_string(0));
	//pointsText2.setFillColor(sf::Color::Yellow);
	//pointsText2.setStyle(sf::Text::Bold);
	//pointsText2.setOrigin(pointsText1.getLocalBounds().width, 0);
	//pointsText2.setPosition(window->getSize().x - 5, 5);

	endText.setFont(font);
	endText.setCharacterSize(120);
	endText.setString("GAME OVER");
	endText.setFillColor(sf::Color::Red);
	endText.setStyle(sf::Text::Bold);
	endText.setOrigin(
		endText.getLocalBounds().width / 2.f,
		endText.getLocalBounds().height / 2.f
	);
	endText.setPosition(window->getSize().x / 2, window->getSize().y / 2);

}

void MultiMode::constructSpawning()
{
	spawnBreak = 120;
	spawnTimer = 120;
	obstacleType = 0;
	killedEnemies = 0;
}

MultiMode::MultiMode(sf::RenderWindow* window, std::string playerName1, std::string playerName2)
{
	constructBackground();
	constructInformations(window);
	constructSpawning();

	player1 = new Player(playerName1, controllingKeys1, "Textures/spaceShip1.png", 0.3f, 0.3f);
	player1->setPosition(window->getSize().x / 3, window->getSize().y / 1.5);

	player2 = new Player(playerName2, controllingKeys2, "Textures/spaceShip2.png", 0.188f, 0.218f);
	player2->setPosition(window->getSize().x / 3 * 2, window->getSize().y / 1.5);

	threadExist1 = false;
	threadExist2 = false;
}

MultiMode::~MultiMode()
{
	delete player1;
	delete player2;

	for (auto& i : shots)
		delete i;

	for (auto& i : obstacles)
		delete i;
}

void MultiMode::changeDifficulty()
{
	if (killedEnemies == 5 && spawnBreak > 30)
	{
		spawnBreak -= 5;
		killedEnemies = 0;
	}
}

void MultiMode::updateEvents(sf::RenderWindow* window)
{
	sf::Event event;

	while (window->pollEvent(event));
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void MultiMode::updateShooting1(sf::RenderWindow* window)
{

	if (player1->getCanAttack())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player1->setCanAttack(false);
			threadExist1 = false;
			shots.push_back(new Shot(player1->getPosition().x - (player1->getBounds().width / 2.1), player1->getPosition().y - 25, 0.f, -15.0f));
			shots.push_back(new Shot(player1->getPosition().x + (player1->getBounds().width / 2.1), player1->getPosition().y - 25, 0.f, -15.0f));
		}
	}
	else if (threadExist1 == false)
	{
		std::thread t1(&Player::allowToAttack, player1);

		t1.detach();
		threadExist1 = true;
	}	
}

void MultiMode::updateShooting2(sf::RenderWindow* window)
{
	if (player2->getCanAttack())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			player2->setCanAttack(false);
			threadExist2 = false;
			shots.push_back(new Shot(player2->getPosition().x - (player2->getBounds().width / 2.1), player2->getPosition().y - 25, 0.f, -15.0f));
			shots.push_back(new Shot(player2->getPosition().x + (player2->getBounds().width / 2.1), player2->getPosition().y - 25, 0.f, -15.0f));
		}
	}
	else if (threadExist2 == false)
	{
		std::thread t2(&Player::allowToAttack, player2);

		t2.detach();
		threadExist2 = true;
	}
}

void MultiMode::updateShots()
{
	for (auto it = shots.begin(); it != shots.end();)
	{
		(*it)->update();

		if ((*it)->getBounds().top + (*it)->getBounds().height < 0.f)
		{
			delete* it;
			it = shots.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void MultiMode::updateObstacles(sf::RenderWindow* window)
{

	if (spawnTimer >= spawnBreak)
	{
		obstacleType = rand() % 4;

		switch (obstacleType)
		{
		case 0:
		{
			obstacles.push_back(new Rock(window));
			break;
		}
		case 1:
		{
			obstacles.push_back(new Satellite(window));
			break;
		}
		case 2:
		{
			obstacles.push_back(new EnemyShip(window));
			break;
		}
		case 3:
		{
			obstacles.push_back(new SpaceBall(window));
			break;
		}
		}

		spawnTimer = 0;
	}

	spawnTimer++;

	for (auto it = obstacles.begin(); it != obstacles.end(); it++)
	{
		(*it)->update();
	}
}

void MultiMode::updateCollision1(sf::RenderWindow* window)
{
	for (auto it = obstacles.begin(); it != obstacles.end();)
	{
		if ((*it)->getBounds().top >= window->getSize().y)
		{
			delete* it;
			it = obstacles.erase(it);
		}
		else if ((*it)->getBounds().intersects(player1->getBounds()))
		{
			player1->deductHp((*it)->demage());

			delete* it;
			it = obstacles.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void MultiMode::updateCollision2(sf::RenderWindow* window)
{
	for (auto it = obstacles.begin(); it != obstacles.end();)
	{
		if ((*it)->getBounds().top >= window->getSize().y)
		{
			delete* it;
			it = obstacles.erase(it);
		}
		else if ((*it)->getBounds().intersects(player2->getBounds()))
		{
			player2->deductHp((*it)->demage());

			delete* it;
			it = obstacles.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void MultiMode::updateAttack()
{
	for (auto obstaclesIt = obstacles.begin(); obstaclesIt != obstacles.end();)
	{
		bool isKilled = false;

		for (auto shotsIt = shots.begin(); shotsIt != shots.end() && isKilled == false;)
		{
			if ((*obstaclesIt)->getBounds().intersects((*shotsIt)->getBounds()))
			{
				(*obstaclesIt)->deductHp(20);

				delete* shotsIt;
				shotsIt = shots.erase(shotsIt);
			}
			else
			{
				shotsIt++;
			}

			if ((*obstaclesIt)->getHp() <= 0)
			{
				killedEnemies++;

				player1->addPoints((*obstaclesIt)->getKillPoints());

				isKilled = true;

				delete* obstaclesIt;
				obstaclesIt = obstacles.erase(obstaclesIt);
			}
		}

		if (!isKilled)
		{
			obstaclesIt++;
		}
	}
}

void MultiMode::updateInformations()
{
	pointsText1.setString("POINTS: " + std::to_string(player1->getPoints()));

}

void MultiMode::saveResultToFile()
{
	std::filesystem::path recordsPath("Results");
	if (std::filesystem::exists(recordsPath))
	{
		std::fstream filePath("Results/multiResults.txt", std::fstream::out | std::ios::app);

		if (filePath)
		{
			filePath << player1->getName() << " " << player2->getName() << " " << player1->getPoints() << std::endl;
		}

		filePath.close();
	}
	else
	{
		std::cout << "Path is not exist!" << std::endl;

		std::filesystem::create_directory("Results");
		std::fstream filePath("Results/multiResults.txt", std::fstream::out);

		if (filePath)
		{
			filePath << player1->getName() << " " << player2->getName() << " " << player1->getPoints() << std::endl;
		}

		filePath.close();
	}
}

void MultiMode::update(sf::RenderWindow* window)
{
	if (player1->getHp() > 0 || player2->getHp() > 0)
	{
		changeDifficulty();
		updateEvents(window);
		updateShots();
		updateObstacles(window);
		updateAttack();
		updateInformations();
	}

	if (player1->getHp() > 0 && player2->getHp() > 0)
	{
		player1->update(window, player2);
		updateShooting1(window);
		updateCollision1(window);
		player2->update(window, player1);
		updateShooting2(window);
		updateCollision2(window);
	}
	else if (player1->getHp() > 0 && player2->getHp() <= 0)
	{
		player1->update(window);
		updateShooting1(window);
		updateCollision1(window);
	}
	else if (player1->getHp() <= 0 && player2->getHp() > 0)
	{
		player2->update(window);
		updateShooting2(window);
		updateCollision2(window);
	}
}

void MultiMode::render(sf::RenderWindow* window)
{
	window->clear();

	if (player1->getHp() > 0 || player2->getHp() > 0)
	{
		window->draw(backgroundSprite);
		window->draw(pointsText1);

		for (auto& i : shots)
			i->draw(window);

		for (auto& i : obstacles)
			i->draw(window);
	}

	if (player1->getHp() > 0)
	{	
		player1->draw(window);
	}

	if (player2->getHp() > 0)
	{
		player2->draw(window);
	}

	if(player1->getHp() <= 0 && player2->getHp() <= 0)
	{
		window->draw(endText);
	}

	window->display();
}

void MultiMode::run(sf::RenderWindow* window)
{
	while (window->isOpen())
	{
		update(window);
		render(window);

		if (player1->getHp() <= 0 && player2->getHp() <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			saveResultToFile();
			break;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			saveResultToFile();
			break;
		}
	}
}

