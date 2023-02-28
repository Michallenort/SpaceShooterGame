#include "MultiRegistration.h"

MultiRegistration::MultiRegistration(sf::RenderWindow* window)
{
	externalShape1.setFillColor(sf::Color::White);
	externalShape1.setSize(sf::Vector2f(window->getSize().x - 300.f, 75.f));
	externalShape1.setOrigin(externalShape1.getSize().x / 2.f, externalShape1.getSize().y / 2.f);
	externalShape1.setPosition(sf::Vector2f(window->getSize().x / 2.f, 150.f));

	internalShape1.setFillColor(sf::Color::Black);
	internalShape1.setSize(sf::Vector2f(externalShape1.getSize().x - 20.f, externalShape1.getSize().y - 20.f));
	internalShape1.setOrigin(internalShape1.getSize().x / 2.f, internalShape1.getSize().y / 2.f);
	internalShape1.setPosition(sf::Vector2f(window->getSize().x / 2.f, 150.f));

	externalShape2.setFillColor(sf::Color::White);
	externalShape2.setSize(sf::Vector2f(window->getSize().x - 300.f, 75.f));
	externalShape2.setOrigin(externalShape2.getSize().x / 2.f, externalShape2.getSize().y / 2.f);
	externalShape2.setPosition(sf::Vector2f(window->getSize().x / 2.f, 400.f));

	internalShape2.setFillColor(sf::Color::Black);
	internalShape2.setSize(sf::Vector2f(externalShape2.getSize().x - 20.f, externalShape2.getSize().y - 20.f));
	internalShape2.setOrigin(internalShape2.getSize().x / 2.f, internalShape2.getSize().y / 2.f);
	internalShape2.setPosition(sf::Vector2f(window->getSize().x / 2.f, 400.f));

	textInput1 = new Textbox(40, sf::Color::White, false, sf::Vector2f(175, 125));
	textInput1->setLimit(true, 30);

	textInput2 = new Textbox(40, sf::Color::White, false, sf::Vector2f(175, 375));
	textInput2->setLimit(true, 30);

	admitButton = new Button(900, 700, 300, 100, "Play", sf::Color(169, 169, 169), sf::Color(105, 105, 105), sf::Color::Blue);

	playerName1 = "";
	playerName2 = "";

	if (!font.loadFromFile("Fonts/minecraft_font.ttf"))
	{
		std::cout << "Font cannot be loaded from a file!" << std::endl;
	}

	informationText1.setFont(font);
	informationText1.setCharacterSize(30);
	informationText1.setString("Enter player's 1 name:");
	informationText1.setFillColor(sf::Color::White);
	informationText1.setOrigin(0, informationText1.getLocalBounds().height);
	informationText1.setPosition(
		externalShape1.getGlobalBounds().left,
		externalShape1.getGlobalBounds().top - 30.f
	);

	informationText2.setFont(font);
	informationText2.setCharacterSize(30);
	informationText2.setString("Enter player's 2 name:");
	informationText2.setFillColor(sf::Color::White);
	informationText2.setOrigin(0, informationText2.getLocalBounds().height);
	informationText2.setPosition(
		externalShape2.getGlobalBounds().left,
		externalShape2.getGlobalBounds().top - 30.f
	);

	errorText1.setFont(font);
	errorText1.setCharacterSize(30);
	errorText1.setString("Name 1 is incorrect!");
	errorText1.setFillColor(sf::Color::Red);
	errorText1.setPosition(
		externalShape1.getGlobalBounds().left,
		externalShape1.getGlobalBounds().top + externalShape1.getGlobalBounds().height + 30.f
	);

	errorText2.setFont(font);
	errorText2.setCharacterSize(30);
	errorText2.setString("Name 2 is incorrect!");
	errorText2.setFillColor(sf::Color::Red);
	errorText2.setPosition(
		externalShape2.getGlobalBounds().left,
		externalShape2.getGlobalBounds().top + externalShape2.getGlobalBounds().height + 30.f
	);
}

MultiRegistration::~MultiRegistration()
{
	delete textInput1;
	delete textInput2;
	delete admitButton;
}

std::string MultiRegistration::getPlayerName1() const
{
	return playerName1;
}

std::string MultiRegistration::getPlayerName2() const
{
	return playerName2;
}

bool MultiRegistration::isCorrect(std::string name)
{
	std::regex correctTemplate("^[a-zA-Z_.]{6,20}[@#!&%$][0-9]{4,6}$");

	if (std::regex_match(name, correctTemplate))
	{
		return true;
	}

	return false;
}


void MultiRegistration::update(sf::RenderWindow* window)
{
	sf::Event event;

	while (window->pollEvent(event));
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (event.type == sf::Event::TextEntered)
			textInput1->update(event);

		if (event.type == sf::Event::TextEntered)
			textInput2->update(event);
	}

	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	
	if (internalShape1.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!textInput1->getSelected())
		{
			textInput1->setSelected(true);

			if (textInput2->getSelected())
			{
				textInput2->setSelected(false);
			}
		}
	}

	if (internalShape2.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!textInput2->getSelected())
		{
			textInput2->setSelected(true);

			if (textInput1->getSelected())
			{
				textInput1->setSelected(false);
			}
		}
	}

	admitButton->update(mousePosition);
}

void MultiRegistration::render(sf::RenderWindow* window)
{
	window->clear();

	window->draw(externalShape1);
	window->draw(internalShape1);
	window->draw(externalShape2);
	window->draw(internalShape2);
	admitButton->draw(window);
	window->draw(informationText1);
	window->draw(informationText2);
	if (!isCorrect(textInput1->getText()))
	{
		window->draw(errorText1);
	}
	if (!isCorrect(textInput2->getText()))
	{
		window->draw(errorText2);
	}
	textInput1->draw(window);
	textInput2->draw(window);

	window->display();
}

void MultiRegistration::run(sf::RenderWindow* window)
{
	while (window->isOpen())
	{
		update(window);
		render(window);

		if (admitButton->isPressed() && isCorrect(textInput1->getText()) && isCorrect(textInput2->getText()))
		{
			playerName1 = textInput1->getText();
			playerName2 = textInput2->getText();
			break;
		}
	}
}
