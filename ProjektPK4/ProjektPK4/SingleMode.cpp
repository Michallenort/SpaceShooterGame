#include "SingleMode.h"

void SingleMode::constructBackground()
{
	if (!backgroundTexture.loadFromFile("Textures/space.jpg"))
	{
		std::cout << "Texture downloading error" << std::endl;
	}

	backgroundSprite.scale(0.58, 0.7);
	backgroundSprite.setTexture(backgroundTexture);
}

void SingleMode::constructInformations(sf::RenderWindow* window)
{
	if (!this->font.loadFromFile("Fonts/minecraft_font.ttf"))
	{
		std::cout << "Font cannot be loaded from a file!" << std::endl;
	}

	pointsText.setFont(font);
	pointsText.setCharacterSize(30);
	pointsText.setString("POINTS: " + std::to_string(0));
	pointsText.setFillColor(sf::Color::Yellow);	
	pointsText.setStyle(sf::Text::Bold);
	pointsText.setPosition(5, 5);

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

void SingleMode::constructSpawning()
{
	spawnBreak = 120;
	spawnTimer = 120;
	obstacleType = 0;
	killedEnemies = 0;
}

SingleMode::SingleMode(sf::RenderWindow* window, std::string playerName)
{
	constructBackground();
	constructInformations(window);
	constructSpawning();

	player = new Player(playerName, controllingKeys, "Textures/spaceShip1.png", 0.3f, 0.3f);
	player->setPosition(window->getSize().x / 2, window->getSize().y / 1.5);

	threadExist = false;
}

SingleMode::~SingleMode()
{
	delete player;

	for (auto& i : shots)
		delete i;

	for (auto& i : obstacles)
		delete i;
}

void SingleMode::changeDifficulty()
{
	if (killedEnemies == 5 && spawnBreak > 30)
	{
		spawnBreak -= 5;
		killedEnemies = 0;
	}
}

void SingleMode::updateEvents(sf::RenderWindow* window)
{
	sf::Event event;

	while (window->pollEvent(event));
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void SingleMode::updateShots(sf::RenderWindow* window)
{
	if (player->getCanAttack())
	{		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player->setCanAttack(false);
			threadExist = false;
			shots.push_back(new Shot(player->getPosition().x - (player->getBounds().width / 2.1), player->getPosition().y - 25, 0.f, -15.0f));
			shots.push_back(new Shot(player->getPosition().x + (player->getBounds().width / 2.1), player->getPosition().y - 25, 0.f, -15.0f));
		}
	}
	else if(threadExist == false)
	{	
		std::thread t1(&Player::allowToAttack, player);
		t1.detach();
		threadExist = true;
	}


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

void SingleMode::updateObstacles(sf::RenderWindow* window)
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

	for (auto it = obstacles.begin(); it != obstacles.end();)
	{
		(*it)->update();

		if ((*it)->getBounds().top >= window->getSize().y)
		{
			delete* it;
			it = obstacles.erase(it);
		}
		else if ((*it)->getBounds().intersects(player->getBounds()))
		{
			player->deductHp((*it)->demage());

			delete* it;
			it = obstacles.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void SingleMode::updateAttack()
{	
	for (auto obstaclesIt = obstacles.begin(); obstaclesIt != obstacles.end();)
	{
		bool isKilled = false;

		for(auto shotsIt = shots.begin(); shotsIt != shots.end() && isKilled == false;)
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

				player->addPoints((*obstaclesIt)->getKillPoints());

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

void SingleMode::updateInformations()
{
	pointsText.setString("POINTS: " + std::to_string(player->getPoints()));

}

void SingleMode::saveResultToFile()
{
	std::filesystem::path recordsPath("Results");
	if (std::filesystem::exists(recordsPath))
	{
		std::fstream filePath("Results/singleResults.txt", std::fstream::out | std::ios::app);

		if (filePath)
		{
			filePath << player->getName() << " " << player->getPoints() << std::endl;
			std::cout << "Result saved succesfully" << std::endl;
		}

		filePath.close();
	}
	else
	{
		std::cout << "Path is not exist!" << std::endl;

		std::filesystem::create_directory("Results");
		std::fstream filePath("Results/singleResults.txt", std::fstream::out);

		if (filePath)
		{
			filePath << player->getName() << " " << player->getPoints() << std::endl;
			std::cout << "Result saved succesfully" << std::endl;
		}
		
		filePath.close();
	}
}

void SingleMode::update(sf::RenderWindow* window)
{
	if (player->getHp() > 0)
	{
		changeDifficulty();
		updateEvents(window);

		player->update(window);

		updateShots(window);
		updateObstacles(window);
		updateAttack();
		updateInformations();
	}
}

void SingleMode::render(sf::RenderWindow* window)
{
	window->clear();

	if (player->getHp() > 0)
	{
		window->draw(backgroundSprite);
		window->draw(pointsText);

		player->draw(window);

		for (auto& i : shots)
			i->draw(window);

		for (auto& i : obstacles)
			i->draw(window);
	}
	else
	{
		window->draw(endText);
	}

	window->display();
}

void SingleMode::run(sf::RenderWindow* window)
{
	while (window->isOpen())
	{
		update(window);
		render(window);

		if (player->getHp() <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
