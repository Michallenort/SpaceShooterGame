#ifndef RANKINGMODE_H
#define RANKINGMODE_H

#include <SFML/Graphics.hpp>
#include "GameMode.h"
#include "Button.h"
#include "SingleModeResults.h"
#include "MultiModeResults.h"

#define RANKING_OPTIONS 3

class RankingMode : public GameMode
{
	Button* singleRankingButton;
	Button* multiRankingButton;
	Button* returnButton;

	sf::Vector2f mousePosition;

	SingleModeResults* singleResults;
	MultiModeResults* multiResults;

	int rankingState;
public:
	RankingMode(float width, float height, sf::RenderWindow* window);
	~RankingMode();

	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
	void run(sf::RenderWindow* window);
};

#endif
