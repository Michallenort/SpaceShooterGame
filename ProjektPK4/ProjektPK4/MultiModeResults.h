#ifndef MULTIMODERESULTS_H
#define MULTIMODERESULTS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>
#include <algorithm>
#include <ranges>

class MultiModeResults
{
	sf::RectangleShape table;
	sf::RectangleShape line1;
	sf::RectangleShape line2;
	sf::RectangleShape line3;
	std::tuple<sf::Text, sf::Text, sf::Text> titles;

	std::vector<std::tuple<std::string, std::string, int>> resultsArray;

	sf::Font font;
	std::vector<std::tuple<sf::Text, sf::Text, sf::Text>> resultsToDraw;

public:
	void loadResults();
	void constructResults();

	MultiModeResults(sf::RenderWindow* window);
	~MultiModeResults();

	void update();
	void draw(sf::RenderWindow* window);
};

#endif

