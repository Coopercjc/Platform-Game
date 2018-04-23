#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "menu.h"



Menu::Menu(float width, float height) {
	if (!font.loadFromFile("mariofont.ttf")) {
		std::cout << "Font not loaded" << std::endl;
	}

	options[0].setFont(font);
	options[0].setFillColor(sf::Color::Red);
	options[0].setString("Play");
	options[0].setPosition(sf::Vector2f((width / 2) - 25, (height * 2) / 4));

	options[1].setFont(font);
	options[1].setFillColor(sf::Color::White);
	options[1].setString("Exit");
	options[1].setPosition(sf::Vector2f((width / 2) - 25, (height * 3) / 4));


	selectedOption = 0;
}

void Menu::draw(sf::RenderWindow &window) {
	for (int i = 0; i < 2; i++) {
		window.draw(options[i]);
	}
}

Menu::~Menu()
{
}

void Menu::moveUpMenu() {
	if (selectedOption - 1 >= 0) {
		options[selectedOption].setFillColor(sf::Color::White);
		selectedOption--;
		options[selectedOption].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDownMenu() {
	if (selectedOption + 1 < 2) {
		options[selectedOption].setFillColor(sf::Color::White);
		selectedOption++;
		options[selectedOption].setFillColor(sf::Color::Red);
	}
}

int Menu::getSelectedOption() {
	return selectedOption;
}

sf::Font Menu::getFont() {
	return font;
}