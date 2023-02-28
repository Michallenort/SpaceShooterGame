#include "Textbox.h"

void Textbox::inputCharacter(int charTyped)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		text << static_cast<char>(charTyped);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		if (text.str().length() > 0)
		{
			deleteCharacter();
		}
	}
	textbox.setString(text.str() + "|");
}

void Textbox::deleteCharacter()
{
	std::string t = text.str();
	std::string newT = "";

	for (int i = 0; i < t.length() - 1; i++)
	{
		newT += t[i];
	}
	text.str("");
	text << newT;

	textbox.setString(text.str());
}



Textbox::Textbox(int size, sf::Color color, bool sel, sf::Vector2f pos)
{

	if (!font.loadFromFile("Fonts/minecraft_font.ttf"))
	{
		std::cout << "Font cannot be loaded from a file!" << std::endl;
	}

	textbox.setCharacterSize(size);
	textbox.setFillColor(color);
	textbox.setFont(font);
	textbox.setOrigin(
		textbox.getLocalBounds().width / 2.f,
		textbox.getLocalBounds().height / 2.f
	);
	textbox.setPosition(pos);

	isSelected = sel;

	if (sel)
	{
		textbox.setString("|");
	}
	else
	{
		textbox.setString("");
	}
}


void Textbox::setFont(sf::Font& font)
{
	textbox.setFont(font);
}

void Textbox::setPosition(sf::Vector2f pos)
{
	textbox.setPosition(pos);
}

void Textbox::setLimit(bool hl)
{
	hasLimit = hl;
}

void Textbox::setLimit(bool hl, int lim)
{
	hasLimit = hl;
	limit = lim;
}

void Textbox::setSelected(bool sel)
{
	isSelected = sel;
	if (!sel)
	{
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length(); i++)
		{
			newT += t[i];
		}
		textbox.setString(newT);
	}
}

bool Textbox::getSelected() const
{
	return isSelected;
}

std::string Textbox::getText()
{
	return text.str();
}

void Textbox::draw(sf::RenderWindow* window)
{
	window->draw(textbox);
}

void Textbox::update(sf::Event input)
{
	if (isSelected)
	{
		int charTyped = input.text.unicode;
		if (charTyped < 128)
		{
			if (hasLimit)
			{
				if (text.str().length() <= limit)
				{
					inputCharacter(charTyped);
				}
				else if (text.str().length() > limit && sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					deleteCharacter();
				}
			}
			else
			{
				inputCharacter(charTyped);
			}
		}
	}
}