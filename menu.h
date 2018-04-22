#pragma once
#include "SFML/Graphics.hpp"

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void moveUpMenu();
	void moveDownMenu();
	int getSelectedOption();
	sf::Font getFont();

private:
	int selectedOption;
	sf::Font font;
	sf::Text options[3];
};
