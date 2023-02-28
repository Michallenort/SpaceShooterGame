#include "SingleRegistration.h"

SingleRegistration::SingleRegistration(sf::RenderWindow* window)
{
	externalShape.setFillColor(sf::Color::White);
	externalShape.setSize(sf::Vector2f(window->getSize().x - 300.f, 75.f));
	externalShape.setOrigin(externalShape.getSize().x / 2.f, externalShape.getSize().y / 2.f);
	externalShape.setPosition(sf::Vector2f(window->getSize().x / 2.f, 300.f));

	internalShape.setFillColor(sf::Color::Black);
	internalShape.setSize(sf::Vector2f(externalShape.getSize().x - 20.f, externalShape.getSize().y - 20.f));
	internalShape.setOrigin(internalShape.getSize().x / 2.f, internalShape.getSize().y / 2.f);
	internalShape.setPosition(sf::Vector2f(window->getSize().x / 2.f, 300.f));

	textInput = new Textbox(40, sf::Color::White, true, sf::Vector2f(175, 275));
	textInput->setLimit(true, 30);

	admitButton = new Button(900, 700, 300, 100, "Play", sf::Color(169, 169, 169), sf::Color(105, 105, 105), sf::Color::Blue);

	playerName = "";

	if (!font.loadFromFile("Fonts/minecraft_font.ttf"))
	{
		std::cout << "Font cannot be loaded from a file!" << std::endl;
	}

	informationText.setFont(font);
	informationText.setCharacterSize(30);
	informationText.setString("Enter player's name:");
	informationText.setFillColor(sf::Color::White);
	informationText.setOrigin(0, informationText.getLocalBounds().height);
	informationText.setPosition(
		externalShape.getGlobalBounds().left,
		externalShape.getGlobalBounds().top - 30.f
	);

	errorText.setFont(font);
	errorText.setCharacterSize(30);
	errorText.setString("Name is incorrect!");
	errorText.setFillColor(sf::Color::Red);
	errorText.setPosition(
		externalShape.getGlobalBounds().left,
		externalShape.getGlobalBounds().top + externalShape.getGlobalBounds().height + 30.f
	);
}

SingleRegistration::~SingleRegistration()
{
	delete textInput;
	delete admitButton;
}

std::string SingleRegistration::getPlayerName() const
{
	return playerName;
}

bool SingleRegistration::isCorrect(std::string name)
{
	std::regex correctTemplate("^[a-zA-Z._]{6,20}[@#!&%$][0-9]{4,6}$");

	if (std::regex_match(name, correctTemplate))
	{
		return true;
	}

	return false;
}

void SingleRegistration::update(sf::RenderWindow* window)
{
	sf::Event event;

	while (window->pollEvent(event));
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (event.type == sf::Event::TextEntered)
			textInput->update(event);
	}

	mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	admitButton->update(mousePosition);
}

void SingleRegistration::render(sf::RenderWindow* window)
{
	window->clear();

	window->draw(externalShape);
	window->draw(internalShape);
	admitButton->draw(window);
	window->draw(informationText);
	if (!isCorrect(textInput->getText()))
	{
		window->draw(errorText);
	}
		
	textInput->draw(window);

	window->display();
}

void SingleRegistration::run(sf::RenderWindow* window)
{
	while (window->isOpen())
	{
		update(window);
		render(window);

		if (admitButton->isPressed() && isCorrect(textInput->getText()))
		{
			playerName = textInput->getText();
			break;
		}
	}
}