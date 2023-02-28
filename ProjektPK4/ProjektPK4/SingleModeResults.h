#ifndef SINGLEMODERESULTS_H
#define SINGLEMODERESULTS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <ranges>

class SingleModeResults
{
	sf::RectangleShape table;
	sf::RectangleShape line1;
	sf::RectangleShape line2;
	std::pair<sf::Text, sf::Text> titles;
	std::vector<std::pair<std::string, int>> resultsArray;

	sf::Font font;
	std::vector<std::pair<sf::Text, sf::Text>> resultsToDraw;
	
public:
	void loadResults();
	void constructResults();

	SingleModeResults(sf::RenderWindow* window);
	~SingleModeResults();

	void update();
	void draw(sf::RenderWindow* window);
};

#endif

