#include "MultiModeResults.h"

void MultiModeResults::loadResults()
{
	std::filesystem::path path("Results/multiResults.txt");

	if (std::filesystem::exists(path))
	{
		std::fstream resultsFile("Results/multiResults.txt");

		if (resultsFile)
		{
			std::string line;

			while (getline(resultsFile, line))
			{
				std::stringstream stream;
				std::string tempString1, tempString2;
				int tempInt;
				stream << line;

				stream >> tempString1 >> tempString2 >> tempInt;

				resultsArray.push_back(std::make_tuple(tempString1, tempString2, tempInt));
			}


			std::ranges::sort(resultsArray,
				[](std::tuple<std::string, std::string, int> a, std::tuple<std::string, std::string, int> b)
				{
					return std::get<2>(a) > std::get<2>(b);
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

void MultiModeResults::constructResults()
{
	for (int i = 0; i < resultsArray.size(); i++)
	{
		sf::Text text1, text2, text3;

		text1.setFont(font);
		text1.setCharacterSize(30);
		text1.setString(std::to_string(i + 1) + "." + std::get<0>(resultsArray[i]));
		text1.setFillColor(sf::Color::White);
		text1.setOrigin(
			text1.getLocalBounds().width / 2.f,
			text1.getLocalBounds().height / 2.f
		);
		text1.setPosition(
			table.getGlobalBounds().left + (line2.getPosition().x - table.getGlobalBounds().left) / 2.f,
			line3.getPosition().y + 15.f + i * 50
		);

		text2.setFont(font);
		text2.setCharacterSize(30);
		text2.setString(std::to_string(i + 1) + "." + std::get<1>(resultsArray[i]));
		text2.setFillColor(sf::Color::White);
		text2.setOrigin(
			text2.getLocalBounds().width / 2.f,
			text2.getLocalBounds().height / 2.f
		);
		text2.setPosition(
			line2.getPosition().x + (line1.getPosition().x - line2.getPosition().x) / 2.f,
			line3.getPosition().y + 15.f + i * 50
		);


		text3.setFont(font);
		text3.setCharacterSize(30);
		text3.setString(std::to_string(std::get<2>(resultsArray[i])));
		text3.setFillColor(sf::Color::White);
		text3.setOrigin(
			text3.getLocalBounds().width / 2.f,
			text3.getLocalBounds().height / 2.f
		);
		text3.setPosition(
			line1.getPosition().x + (table.getPosition().x + table.getGlobalBounds().width / 2 - line1.getPosition().x) / 2,
			line3.getPosition().y + 15.f + i * 50
		);

		resultsToDraw.push_back(std::make_tuple(text1, text2, text3));
	}
}

MultiModeResults::MultiModeResults(sf::RenderWindow* window)
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
	line1.setPosition(sf::Vector2f(table.getPosition().x + 300.f, table.getPosition().y));

	line2.setSize(sf::Vector2f(5.f, 600.f));
	line2.setOrigin(line2.getSize().x / 2.f, line2.getSize().y / 2.f);
	line2.setFillColor(sf::Color::White);
	line2.setPosition(sf::Vector2f(table.getGlobalBounds().left + (line1.getPosition().x - table.getGlobalBounds().left) / 2.f, table.getPosition().y));
	
	line3.setSize(sf::Vector2f(1000.f, 5.f));
	line3.setOrigin(line3.getSize().x / 2.f, line3.getSize().y / 2.f);
	line3.setFillColor(sf::Color::White);
	line3.setPosition(sf::Vector2f(table.getPosition().x, table.getPosition().y - 250.f));

	std::get<0>(titles).setFont(font);
	std::get<0>(titles).setCharacterSize(30);
	std::get<0>(titles).setString("Names 1");
	std::get<0>(titles).setFillColor(sf::Color::White);
	std::get<0>(titles).setOrigin(
		std::get<0>(titles).getLocalBounds().width / 2.f,
		std::get<0>(titles).getLocalBounds().height / 2.f
	);
	std::get<0>(titles).setPosition(
		table.getGlobalBounds().left + (line2.getPosition().x - table.getGlobalBounds().left) / 2.f,
		table.getGlobalBounds().top + (line3.getPosition().y - table.getGlobalBounds().top) / 2.f - 5.f
	);

	std::get<1>(titles).setFont(font);
	std::get<1>(titles).setCharacterSize(30);
	std::get<1>(titles).setString("Names 2");
	std::get<1>(titles).setFillColor(sf::Color::White);
	std::get<1>(titles).setOrigin(
		std::get<1>(titles).getLocalBounds().width / 2.f,
		std::get<1>(titles).getLocalBounds().height / 2.f
	);
	std::get<1>(titles).setPosition(
		line2.getPosition().x + (line1.getPosition().x - line2.getPosition().x) / 2.f,
		table.getGlobalBounds().top + (line3.getPosition().y - table.getGlobalBounds().top) / 2.f - 5.f
	);

	std::get<2>(titles).setFont(font);
	std::get<2>(titles).setCharacterSize(30);
	std::get<2>(titles).setString("Points");
	std::get<2>(titles).setFillColor(sf::Color::White);
	std::get<2>(titles).setOrigin(
		std::get<2>(titles).getLocalBounds().width / 2.f,
		std::get<2>(titles).getLocalBounds().height / 2.f
	);
	std::get<2>(titles).setPosition(
		line1.getPosition().x + (table.getPosition().x + table.getGlobalBounds().width / 2 - line1.getPosition().x) / 2,
		table.getGlobalBounds().top + (line3.getPosition().y - table.getGlobalBounds().top) / 2.f - 5.f
	);

	loadResults();
	constructResults();
}

MultiModeResults::~MultiModeResults()
{

}

void MultiModeResults::update()
{

}

void MultiModeResults::draw(sf::RenderWindow* window)
{
	window->draw(table);
	window->draw(line1);
	window->draw(line2);
	window->draw(line3);
	window->draw(std::get<0>(titles));
	window->draw(std::get<1>(titles));
	window->draw(std::get<2>(titles));

	for (int i = 0; i < resultsToDraw.size(); i++)
	{
		window->draw(std::get<0>(resultsToDraw[i]));
		window->draw(std::get<1>(resultsToDraw[i]));
		window->draw(std::get<2>(resultsToDraw[i]));
	}
}
