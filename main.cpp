#include "game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
//include file operations
#include <sstream>
#include <fstream>
#include "menu.h"

using namespace sf;

//Helps animating camera
Clock clock1;
float timer1, delay1 = 0.01;
Camera camera;

//includes all in-game calculations
Game game;
int levelCounter = 4;
int alarm = 0;
int score = 0;

int temp = 0;
int dumb = 0;

int main()
{
	//this section will call the levels depending on the global variable counter
	if (levelCounter == 1) {
		game.Level1();
	}
	if (levelCounter == 2) {
		game.Level2();
	}
	if (levelCounter == 3) {
		game.Level3();
	}
	if (levelCounter == 4) {
		game.Level4();
	}
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	//Window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "JUMPMAN");
	sf::View view(sf::FloatRect(0, 0, WIDTH, HEIGHT));
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(200 * game.ground.dimension, HEIGHT));
	background.setFillColor(sf::Color(100, 100, 250));

	Menu menu(window.getSize().x, window.getSize().y);	//
	bool menuScreen = true;								//
	int option;											//This segment is new
	sf::Text menuTitle;									//
	sf::Font font4 = menu.getFont();						//
															//
	menuTitle.setFont(font4);							//	
	menuTitle.setString("2D Platform Game");			//
	menuTitle.setFillColor(sf::Color::Yellow);			//This segment is new
	menuTitle.setPosition(camera.osszx + 335, 175);

	//Setting Up Textures
	sf::Texture playerT1, playerT2, playerT3, playerT4, groundT,
		gameoverT, brickT, enemyT, enemyT1, circleBoiT, powerupT, coinsT, heartT, flagT;
	playerT1.loadFromFile("static1.png");
	playerT2.loadFromFile("walk2.png");
	playerT3.loadFromFile("static1-upgraded.png");
	playerT4.loadFromFile("walk2-upgraded.png");
	groundT.loadFromFile("groundbrick2.png");
	gameoverT.loadFromFile("gameover.png");
	brickT.loadFromFile("brick.png");
	enemyT.loadFromFile("kabutops.png");
	enemyT1.loadFromFile("ghost.png");
	circleBoiT.loadFromFile("circle.png");
	powerupT.loadFromFile("berry.png");
	heartT.loadFromFile("heart.png");
	flagT.loadFromFile("flag.png");
	coinsT.loadFromFile("coin1.png");

	//Linking Sprites to textures
	sf::Sprite playerS1(playerT1), playerS2(playerT2), playerS3(playerT3), playerS4(playerT4),
		groundS(groundT), gameoverS(gameoverT),
		brickS(brickT), enemyS(enemyT), enemyS1(enemyT1), circleBoiS(circleBoiT),
		powerupS(powerupT), heartS(heartT), flagS(flagT), coinsS(coinsT);

	//enables fonts for the word score printed out when the player dies
	sf::Text text;
	sf::Font font;
	font.loadFromFile("mariofont.ttf");


	//launching program
	while (window.isOpen())
	{
		game.player.lastx = game.player.x;
		game.player.lasty = game.player.y;

		//checking events
		sf::Event event;

		//Starts window at main menu

		//This whole while loop is new
		while (menuScreen) {

			option = menu.getSelectedOption();
			switch (option) {
			case 0:
				playerS1.setPosition(400, 275);
				break;

			case 1:
				playerS1.setPosition(400, 425);
				break;

			}

			while (window.pollEvent(event))
			{
				switch (event.type) {
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menu.moveUpMenu();
						option = menu.getSelectedOption();
						switch (option) {
						case 0:
							playerS1.setPosition(400, 275);
							break;

						case 1:
							playerS1.setPosition(400, 425);
							break;

						}
						break;

					case sf::Keyboard::Down:
						menu.moveDownMenu();
						option = menu.getSelectedOption();
						switch (option) {
						case 0:
							playerS1.setPosition(400, 275);
							break;

						case 1:
							playerS1.setPosition(400, 425);
							break;

						}
						break;

					case sf::Keyboard::Return:
						option = menu.getSelectedOption();
						if (option == 0) {
							menuScreen = false;
							view.setCenter((WIDTH / 2) + camera.osszx, HEIGHT / 2);

						}
						else if (option == 1) {
							window.close();

						}
					}
					break;
				case sf::Event::Closed:
					window.close();
					break;

				}
			}

			//clear window
			window.clear();
			window.draw(background);
			window.draw(playerS1);
			window.draw(menuTitle);
			menu.draw(window);

			window.display();


		}

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();


			//This segment is new
			switch (event.type) {
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					view.setCenter(WIDTH / 2, HEIGHT / 2);
					menuScreen = true;
					break;

				}
				break;

			}
		}

		//clear window
		window.clear();
		game.Loop();
		game.Circle(levelCounter);

		if (game.player.score != 0 && temp != game.player.score)
		{
			score+= 200;
			temp = game.player.score;
		}
		if (game.player.CoinTotal != 0 && dumb != game.player.CoinTotal)
		{
			if (game.player.CoinTotal < dumb)
				dumb = 0;
			score+= 100*(game.player.CoinTotal - dumb);
			dumb = game.player.CoinTotal;
		}

		//this section draws the background of the levels
		window.draw(background);
		if (game.player.health > 0)
		{
			if (game.player.x < game.player.lastx) {
				playerS3.setTextureRect(sf::IntRect(game.player.width, 0, -game.player.width, game.player.height));
				playerS4.setTextureRect(sf::IntRect(game.player.width, 0, -game.player.width, game.player.height));
			}

			else if (game.player.x > game.player.lastx) {
				playerS3.setTextureRect(sf::IntRect(0, 0, game.player.width, game.player.height));
				playerS4.setTextureRect(sf::IntRect(0, 0, game.player.width, game.player.height));
			}
		}
		//displays the level when the player has one life left
		else {
			if (game.player.x < game.player.lastx) {
				playerS1.setTextureRect(sf::IntRect(game.player.width, 0, -game.player.width, game.player.height));
				playerS2.setTextureRect(sf::IntRect(game.player.width, 0, -game.player.width, game.player.height));
			}

			else if (game.player.x > game.player.lastx) {
				playerS1.setTextureRect(sf::IntRect(0, 0, game.player.width, game.player.height));
				playerS2.setTextureRect(sf::IntRect(0, 0, game.player.width, game.player.height));
			}
		}
		//outputs the position of the player
		if (game.player.health > 0)
		{
			if (game.player.walk == true)
			{
				playerS4.setPosition(game.player.x, game.player.y);
				window.draw(playerS4);
			}
			else
			{
				playerS3.setPosition(game.player.x, game.player.y);
				window.draw(playerS3);
			}
		}
		//does the same thing if the player has one life left
		else
		{
			if (game.player.walk == true)
			{
				playerS2.setPosition(game.player.x, game.player.y);
				window.draw(playerS2);
			}
			else
			{
				playerS1.setPosition(game.player.x, game.player.y);
				window.draw(playerS1);
			}
		}
		//drawing the pieces of ground
		for (int y = game.ground.y; y < game.ground.y + game.ground.height; y += game.ground.dimension) {
			for (int x = game.ground.x; x < game.ground.x + game.ground.width; x += game.ground.dimension)
			{
				groundS.setPosition(x - 32, y - 35);
				window.draw(groundS);
			}
		}

		for (int y = game.ground2.y; y < game.ground2.y + game.ground2.height; y += game.ground2.dimension) {
			for (int x = game.ground2.x; x < game.ground2.x + game.ground2.width; x += game.ground2.dimension)
			{
				groundS.setPosition(x - 32, y - 35);
				window.draw(groundS);
			}
		}

		for (int y = game.ground3.y; y < game.ground3.y + game.ground3.height; y += game.ground3.dimension) {
			for (int x = game.ground3.x; x < game.ground3.x + game.ground3.width; x += game.ground3.dimension)
			{
				groundS.setPosition(x - 32, y - 35);
				window.draw(groundS);
			}
		}

		//drawing every brick found in the level
		for (int y = game.brick.y; y < game.brick.y + game.brick.height; y += game.brick.dimension) {
			for (int x = game.brick.x; x < game.brick.x + game.brick.width; x += game.brick.dimension)
			{
				brickS.setPosition(x, y);
				window.draw(brickS);
			}
		}

		for (int y = game.brick2.y; y < game.brick2.y + game.brick2.height; y += game.brick2.dimension) {
			for (int x = game.brick2.x; x < game.brick2.x + game.brick2.width; x += game.brick2.dimension)
			{
				brickS.setPosition(x, y);
				window.draw(brickS);
			}
		}

		for (int y = game.brick3.y; y < game.brick3.y + game.brick3.height; y += game.brick3.dimension) {
			for (int x = game.brick3.x; x < game.brick3.x + game.brick3.width; x += game.brick3.dimension)
			{
				brickS.setPosition(x, y);
				window.draw(brickS);
			}
		}

		for (int y = game.brick4.y; y < game.brick4.y + game.brick4.height; y += game.brick4.dimension) {
			for (int x = game.brick4.x; x < game.brick4.x + game.brick4.width; x += game.brick4.dimension)
			{
				brickS.setPosition(x, y);
				window.draw(brickS);
			}
		}

		for (int y = game.brick5.y; y < game.brick5.y + game.brick5.height; y += game.brick5.dimension) {
			for (int x = game.brick5.x; x < game.brick5.x + game.brick5.width; x += game.brick5.dimension)
			{
				brickS.setPosition(x, y);
				window.draw(brickS);
			}
		}

		for (int y = game.brick6.y; y < game.brick6.y + game.brick6.height; y += game.brick6.dimension) {
			for (int x = game.brick6.x; x < game.brick6.x + game.brick6.width; x += game.brick6.dimension)
			{
				brickS.setPosition(x, y);
				window.draw(brickS);
			}
		}

		for (int y = game.brick7.y; y < game.brick7.y + game.brick7.height; y += game.brick7.dimension) {
			for (int x = game.brick7.x; x < game.brick7.x + game.brick7.width; x += game.brick7.dimension)
			{
				brickS.setPosition(x, y);
				window.draw(brickS);
			}
		}

		for (int y = game.brick8.y; y < game.brick8.y + game.brick8.height; y += game.brick8.dimension) {
			for (int x = game.brick8.x; x < game.brick8.x + game.brick8.width; x += game.brick8.dimension)
			{
				brickS.setPosition(x, y);
				window.draw(brickS);
			}
		}

		for (int y = game.coin1.y; y < game.coin1.y + game.coin1.height; y += game.coin1.dimension) {
			for (int x = game.coin1.x; x < game.coin1.x + game.coin1.width; x += game.coin1.dimension)
			{
				coinsS.setPosition(x, y);
				window.draw(coinsS);
			}
		}

		for (int y = game.coin2.y; y < game.coin2.y + game.coin2.height; y += game.coin2.dimension) {
			for (int x = game.coin2.x; x < game.coin2.x + game.coin2.width; x += game.coin2.dimension)
			{
				coinsS.setPosition(x, y);
				window.draw(coinsS);
			}
		}

		for (int y = game.coin3.y; y < game.coin3.y + game.coin3.height; y += game.coin3.dimension) {
			for (int x = game.coin3.x; x < game.coin3.x + game.coin3.width; x += game.coin3.dimension)
			{
				coinsS.setPosition(x, y);
				window.draw(coinsS);
			}
		}

		for (int y = game.coin4.y; y < game.coin4.y + game.coin4.height; y += game.coin4.dimension) {
			for (int x = game.coin4.x; x < game.coin4.x + game.coin4.width; x += game.coin4.dimension)
			{
				coinsS.setPosition(x, y);
				window.draw(coinsS);
			}
		}

		for (int y = game.coin5.y; y < game.coin5.y + game.coin5.height; y += game.coin5.dimension) {
			for (int x = game.coin5.x; x < game.coin5.x + game.coin5.width; x += game.coin5.dimension)
			{
				coinsS.setPosition(x, y);
				window.draw(coinsS);
			}
		}

		for (int y = game.coin6.y; y < game.coin6.y + game.coin6.height; y += game.coin6.dimension) {
			for (int x = game.coin6.x; x < game.coin6.x + game.coin6.width; x += game.coin6.dimension)
			{
				coinsS.setPosition(x, y);
				window.draw(coinsS);
			}
		}

		for (int y = game.coin7.y; y < game.coin7.y + game.coin7.height; y += game.coin7.dimension) {
			for (int x = game.coin7.x; x < game.coin7.x + game.coin7.width; x += game.coin7.dimension)
			{
				coinsS.setPosition(x, y);
				window.draw(coinsS);
			}
		}

		for (int y = game.coin8.y; y < game.coin8.y + game.coin8.height; y += game.coin8.dimension) {
			for (int x = game.coin8.x; x < game.coin8.x + game.coin8.width; x += game.coin8.dimension)
			{
				coinsS.setPosition(x, y);
				window.draw(coinsS);
			}
		}

		for (int y = game.coin9.y; y < game.coin9.y + game.coin9.height; y += game.coin9.dimension) {
			for (int x = game.coin9.x; x < game.coin9.x + game.coin9.width; x += game.coin9.dimension)
			{
				coinsS.setPosition(x, y);
				window.draw(coinsS);
			}
		}

		for (int y = game.coin10.y; y < game.coin10.y + game.coin10.height; y += game.coin10.dimension) {
			for (int x = game.coin10.x; x < game.coin10.x + game.coin10.width; x += game.coin10.dimension)
			{
				coinsS.setPosition(x, y);
				window.draw(coinsS);
			}
		}

		for (int y = game.coin11.y; y < game.coin11.y + game.coin11.height; y += game.coin11.dimension) {
			for (int x = game.coin11.x; x < game.coin11.x + game.coin11.width; x += game.coin11.dimension)
			{
				coinsS.setPosition(x, y);
				window.draw(coinsS);
			}
		}

		for (int y = game.coin12.y; y < game.coin12.y + game.coin12.height; y += game.coin12.dimension) {
			for (int x = game.coin12.x; x < game.coin12.x + game.coin12.width; x += game.coin12.dimension)
			{
				coinsS.setPosition(x, y);
				window.draw(coinsS);
			}
		}



		if (levelCounter == 1) {
			flagS.setPosition(game.flag.x, game.flag.y);
			window.draw(flagS);
		}

		if (levelCounter == 2) {
			flagS.setPosition(game.flag.x, game.flag.y);
			window.draw(flagS);
		}

		if (levelCounter == 3) {
			flagS.setPosition(game.flag.x, game.flag.y);
			window.draw(flagS);
		}

		if (levelCounter == 4) {
			flagS.setPosition(game.flag.x, game.flag.y);
			window.draw(flagS);
		}


		sf::Text myText;
		std::stringstream ss;
		ss << score;
		myText.setFont(font4);
		myText.setString(ss.str().c_str());
		myText.setPosition(camera.osszx, 42);
		window.draw(myText);

		for (int x = 0; x < game.player.health * 21; x += 21)
		{
		heartS.setPosition(camera.osszx + x, 1);
		window.draw(heartS);
		}

		//outputs the enemies in the level
		enemyS.setPosition(game.enemy.x - 10, game.enemy.y - 12);
		window.draw(enemyS);

		enemyS1.setPosition(game.enemy1.x - 55, game.enemy1.y - 30);
		window.draw(enemyS1);

		circleBoiS.setPosition(game.circleBoi.x - 13, game.circleBoi.y - 30);
		window.draw(circleBoiS);

		//outputs the powerups in the level
		if (game.powerup.dead == false)
		{
			powerupS.setPosition(game.powerup.x, game.powerup.y);
			window.draw(powerupS);
		}

		//shows a gameover screen when the player loses all lives
		if (game.player.end == true && game.player.health <= 0)
		{
			window.clear();
			sf::Text moreText;
			moreText.setString("Score");
			moreText.setFont(font4);
			myText.setFont(font4);
			gameoverS.setPosition(camera.osszx + 100, 0);
			
				std::ofstream write;
				write.open("scoreboard.txt", std::ios_base::app);
				write << score;
				write.close();

			//All of the code within this if statement is new
			bool gameover = true;
			while (gameover) {

				window.clear();
				gameoverS.setPosition(camera.osszx + 100, 0);
				myText.setPosition(camera.osszx + 530, 400);
				moreText.setPosition(camera.osszx + 375, 400);
				window.draw(gameoverS);
				window.draw(myText);
				window.draw(moreText);

				while (window.pollEvent(event))
				{
					switch (event.type) {
					case sf::Event::KeyReleased:
						switch (event.key.code) {
						case sf::Keyboard::Return:
							menuScreen = true;
							game.player.health = 1;
							gameover = false;
							break;

						}
						break;

					}
				}

				window.display();
				
			}
		}
		//resets the level when the player dies
		else if (game.player.end == true)
		{
			view.setCenter(WIDTH / 2, HEIGHT / 2);
			camera.osszx = 0;
			game.player.health--;
			if (score < 500)
			{
				score = 0;
			}
			else
			{
				score -= 500;
			}

			game.player.end = false;
			if (levelCounter == 1)
				game.Level1();
			if (levelCounter == 2)
				game.Level2();
			if (levelCounter == 3)
				game.Level3();
			if (levelCounter == 4)
				game.Level4();
		}
		//this section will change the level when the player reaches a certain point in the level
		if (game.player.x > 2400 && levelCounter == 1) {
			if (game.player.CoinTotal == 12) {
				game.player.health++;
			}
			game.player.CoinTotal = 0;
			levelCounter++;
			window.clear();
			view.setCenter(WIDTH / 2, HEIGHT / 2);
			camera.osszx = 0;
			if (levelCounter == 2)
				game.Level2();
		}
		if (game.player.x > 2500 && levelCounter == 2) {
			if (game.player.CoinTotal == 12) {
				game.player.health++;
			}
			game.player.CoinTotal = 0;
			levelCounter++;
			window.clear();
			view.setCenter(WIDTH / 2, HEIGHT / 2);
			camera.osszx = 0;
			if (levelCounter == 3)
				game.Level3();
		}
		if (game.player.x > 2700 && levelCounter == 3) {
			if (game.player.CoinTotal == 12) {
				game.player.health++;
			}
			game.player.CoinTotal = 0;
			levelCounter++;
			window.clear();
			view.setCenter(WIDTH / 2, HEIGHT / 2);
			camera.osszx = 0;
			if (levelCounter == 4)
				game.Level4();
		}

		// window.draw(...);
		float time = clock1.getElapsedTime().asSeconds();
		clock1.restart();
		timer1 += time;

		//Animating the camera
		if (timer1> delay1)
		{
			camera.Shift(game.player);
			view.move(camera.x, 0);
			timer1 = 0;
		}
		//Preventing player from going out of range
		game.player.Block(camera.osszx);
		window.setView(view);

		//ending frame
		window.display();
	}
	return 0;
}