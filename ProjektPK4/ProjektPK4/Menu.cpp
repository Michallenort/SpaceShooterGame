#include "Menu.h"
#include "Button.h"
#include "SingleRegistration.h"
#include "MultiRegistration.h"
#include "RankingMode.h"

void Menu::constructBackground()
{
	if (!backgroundTexture.loadFromFile("Textures/space.jpg"))
	{
		std::cout << "Texture downloading error" << std::endl;
	}

	backgroundSprite.scale(0.58, 0.7);
	backgroundSprite.setTexture(backgroundTexture);
}

void Menu::constructTitle(float width, float height)
{
	if (!titleFont.loadFromFile("Fonts/titleFont.ttf"))
	{
		std::cout << "Font downloading error" << std::endl;
	}

	titleText.setFont(titleFont);
	titleText.setString("SPACE SHOOTER");
	titleText.setCharacterSize(125);
	titleText.setFillColor(sf::Color::White);
	titleText.setOrigin(
		titleText.getLocalBounds().width / 2,
		titleText.getLocalBounds().height / 2
	);
	titleText.setPosition(width / 2, height / 8);

}

void Menu::constructButtons(float width, float height)
{
	singleModeBtn = new Button(width / 2, height / (OPTIONS_NUMBER + 3) * 3, 300, 100, "Single-Player",
		sf::Color(169, 169, 169), sf::Color(105, 105, 105), sf::Color::Blue);

	multiModeBtn = new Button(width / 2, height / (OPTIONS_NUMBER + 3) * 4, 300, 100, "Multi-Player",
		sf::Color(169, 169, 169), sf::Color(105, 105, 105), sf::Color::Blue);

	rankingBtn = new Button(width / 2, height / (OPTIONS_NUMBER + 3) * 5, 300, 100, "Ranking",
		sf::Color(169, 169, 169), sf::Color(105, 105, 105), sf::Color::Blue);

	exitBtn = new Button(width / 2, height / (OPTIONS_NUMBER + 3) * 6, 300, 100, "Exit",
		sf::Color(169, 169, 169), sf::Color(105, 105, 105), sf::Color::Blue);
}

Menu::Menu(float width, float height)
{
	constructBackground();
	constructTitle(width, height);
	constructButtons(width, height);
}

Menu::~Menu()
{
	delete singleModeBtn;
	delete multiModeBtn;
	delete rankingBtn;
	delete exitBtn;
}

void Menu::update(sf::RenderWindow* window)
{
	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	singleModeBtn->update(mousePosition);
	multiModeBtn->update(mousePosition);
	rankingBtn->update(mousePosition);
	exitBtn->update(mousePosition);

	if (singleModeBtn->isPressed())
	{
		std::cout << "Welcome in single-player mode" << std::endl;
		SingleRegistration* registration = new SingleRegistration(window);
		registration->run(window);
		
		std::string playerName;
		playerName = registration->getPlayerName();
		std::cout << playerName << std::endl;
		SingleMode* mode = new SingleMode(window, playerName);
		mode->run(window);

		delete registration;
		delete mode;

	}

	if (multiModeBtn->isPressed())
	{
		std::cout << "Welcome in multi-player mode" << std::endl;
		MultiRegistration* registration = new MultiRegistration(window);
		registration->run(window);

		std::string playerName1 = registration->getPlayerName1();
		std::string playerName2 = registration->getPlayerName2();

		MultiMode* mode = new MultiMode(window, playerName1, playerName2);
		mode->run(window);
		delete registration;
		delete mode;
	}

	if (rankingBtn->isPressed())
	{
		RankingMode* mode = new RankingMode(window->getSize().x, window->getSize().y, window);
		mode->run(window);
		delete mode;
	}

	if (exitBtn->isPressed())
		window->close();
}

void Menu::draw(sf::RenderWindow* window)
{
	window->draw(backgroundSprite);
	window->draw(titleText);

	singleModeBtn->draw(window);
	multiModeBtn->draw(window);
	rankingBtn->draw(window);
	exitBtn->draw(window);
}