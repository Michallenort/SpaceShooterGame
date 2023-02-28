#include "SingleModeResults.h"

void SingleModeResults::loadResults()
{
	std::filesystem::path path("Results/singleResults.txt");

	if (std::filesystem::exists(path))
	{
		std::fstream resultsFile("Results/singleResults.txt");

		if (resultsFile)
		{
			std::string line;

			while (getline(resultsFile, line))
			{
				std::stringstream stream;
				std::string tempString;
				int tempInt;
				stream << line;

				stream >> tempString >> tempInt;

				resultsArray.push_back(std::make_pair(tempString, tempInt));
			}


			std::ranges::sort(resultsArray,
				[](std::pair<std::string, int> a, std::pair<std::string, int> b)
				{
					return a.second > b.second;
				}
			);

			if (resultsArray.size() > 10)
			{
				resultsArray.erase(resultsArray.begin() + 10, resultsArray.end());
			}
		}

		resultsFile.close();
	}
	else
	{
		std::cout << "Path is not exists" << std::endl;
	}
}

void SingleModeResults::constructResults()
{
	for (int i = 0; i < resultsArray.size(); i++)
	{
		sf::Text text1, text2;

		text1.setFont(font);
		text1.setCharacterSize(30);
		text1.setString(std::to_string(i + 1) + "." + resultsArray[i].first);
		text1.setFillColor(sf::Color::White);
		text1.setOrigin(
			text1.getLocalBounds().width / 2.f,
			text1.getLocalBounds().height / 2.f
		);
		text1.setPosition(
			table.getGlobalBounds().left + (line1.getPosition().x - table.getGlobalBounds().left) / 2.f,
			line2.getPosition().y + 15.f + i * 50
		);	

		text2.setFont(font);
		text2.setCharacterSize(30);
		text2.setString(std::to_string(resultsArray[i].second));
		text2.setFillColor(sf::Color::White);
		text2.setOrigin(
			text2.getLocalBounds().width / 2.f,
			text2.getLocalBounds().height / 2.f
		);
		text2.setPosition(
			line1.getPosition().x + (table.getPosition().x + table.getGlobalBounds().width / 2 - line1.getPosition().x) / 2,
			line2.getPosition().y + 15.f + i * 50
		);

		resultsToDraw.push_back(std::make_pair(text1, text2));

	}
}

SingleModeResults::SingleModeResults(sf::RenderWindow* window)
{
	if (!font.loadFromFile("Fonts/minecraft_font.ttf"))
	{
		std::cout << "Font cannot be loaded from a file!" << std::endl;
	}

	table.setSize(sf::Vector2f(1000.f, 600.f));
	table.setOrigin(table.getSize().x / 2.f, table.getSize().y / 2.f);
	table.setFillColor(sf::Color::Black);
	table.setOutlineThickness(5.f);
	table.setOutlineColor(sf::Color::White);
	table.setPosition(sf::Vector2f(window->getSize().x / 2.f, table.getSize().y / 2.f + 50.f));

	line1.setSize(sf::Vector2f(5.f, 600.f));
	line1.setOrigin(line1.getSize().x / 2.f, line1.getSize().y / 2.f);
	line1.setFillColor(sf::Color::White);
	line1.setPosition(sf::Vector2f(table.getPosition().x + 150.f, table.getPosition().y));

	line2.setSize(sf::Vector2f(1000.f, 5.f));
	line2.setOrigin(line2.getSize().x / 2.f, line2.getSize().y / 2.f);
	line2.setFillColor(sf::Color::White);
	line2.setPosition(sf::Vector2f(table.getPosition().x, table.getPosition().y - 250.f));

	titles.first.setFont(font);
	titles.first.setCharacterSize(30);
	titles.first.setString("Names");
	titles.first.setFillColor(sf::Color::White);
	titles.first.setOrigin(
		titles.first.getLocalBounds().width / 2.f,
		titles.first.getLocalBounds().height / 2.f
	);
	titles.first.setPosition(
		table.getGlobalBounds().left + (line1.getPosition().x - table.getGlobalBounds().left) / 2.f,
		table.getGlobalBounds().top + (line2.getPosition().y - table.getGlobalBounds().top) / 2.f - 5.f
	);

	titles.second.setFont(font);
	titles.second.setCharacterSize(30);
	titles.second.setString("Points");
	titles.second.setFillColor(sf::Color::White);
	titles.second.setOrigin(
		titles.second.getLocalBounds().width / 2.f,
		titles.second.getLocalBounds().height / 2.f
	);
	titles.second.setPosition(
		line1.getPosition().x + (table.getPosition().x + table.getGlobalBounds().width / 2 - line1.getPosition().x) / 2,
		table.getGlobalBounds().top + (line2.getPosition().y - table.getGlobalBounds().top) / 2.f - 5.f
	);

	loadResults();
	constructResults();
}

SingleModeResults::~SingleModeResults()
{

}

void SingleModeResults::update()
{

}

void SingleModeResults::draw(sf::RenderWindow* window)
{
	window->draw(table);
	window->draw(line1);
	window->draw(line2);
	window->draw(titles.first);
	window->draw(titles.second);

	for (int i = 0; i < resultsToDraw.size(); i++)
	{
		window->draw(resultsToDraw[i].first);
		window->draw(resultsToDraw[i].second);
	}
}
