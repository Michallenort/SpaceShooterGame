#include "Game.h"

Game::Game()
{
	window = new sf::RenderWindow(sf::VideoMode(1200, 900), "Space Shooter");
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(false);
	menu = new Menu(window->getSize().x, window->getSize().y);
}

Game::~Game()
{
	delete window;
	delete menu;
}

void Game::update()
{
	sf::Event event;

	while (window->pollEvent(event));
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}

	menu->update(window);
}

void Game::render()
{
	window->clear();

	menu->draw(window);

	window->display();
}

void Game::run()
{
	while (window->isOpen())
	{
		update();
		render();
	}
}

