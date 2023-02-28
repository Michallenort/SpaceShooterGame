#include "RankingMode.h"

RankingMode::RankingMode(float width, float height, sf::RenderWindow* window)
{
	singleRankingButton = new Button(width / (RANKING_OPTIONS + 3) * 1, 800, 300, 100, "Single-Player",
		sf::Color(169, 169, 169), sf::Color(105, 105, 105), sf::Color::Blue);

	multiRankingButton = new Button(width / (RANKING_OPTIONS + 3) * 3, 800, 300, 100, "Multi-Player",
		sf::Color(169, 169, 169), sf::Color(105, 105, 105), sf::Color::Blue);

	returnButton = new Button(width / (RANKING_OPTIONS + 3) * 5, 800, 300, 100, "Return",
		sf::Color(169, 169, 169), sf::Color(105, 105, 105), sf::Color::Blue);

	singleResults = new SingleModeResults(window);
	multiResults = new MultiModeResults(window);

	rankingState = 0;
}

RankingMode::~RankingMode()
{
	delete singleRankingButton;
	delete multiRankingButton;
	delete returnButton;
	delete singleResults;
	delete multiResults;
}

void RankingMode::update(sf::RenderWindow* window)
{
	sf::Event event;

	while (window->pollEvent(event));
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}

	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	singleRankingButton->update(mousePosition);
	multiRankingButton->update(mousePosition);
	returnButton->update(mousePosition);

	if(singleRankingButton->isPressed())
	{
		rankingState = 1;
	}
	
	if (multiRankingButton->isPressed())
	{
		rankingState = 2;
	}
}

void RankingMode::render(sf::RenderWindow* window)
{
	window->clear();

	singleRankingButton->draw(window);
	multiRankingButton->draw(window);
	returnButton->draw(window);

	if (rankingState == 1)
	{
		singleResults->draw(window);

	}
	else if (rankingState == 2)
	{
		multiResults->draw(window);
	}

	window->display();
}

void RankingMode::run(sf::RenderWindow* window)
{
	while (window->isOpen())
	{
		update(window);
		render(window);

		if (returnButton->isPressed())
		{
			break;
		}
	}
}
