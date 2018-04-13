#include "game.h"
#include <SFML/Graphics.hpp>
using namespace sf;

//Helps animating camera
Clock clock1;
float timer1, delay1 = 0.01;
Camera camera;
//includes all in-game calculations
Game game;

int main()
{

	game.Setup();
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	//Window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Super Mario");
	sf::View view(sf::FloatRect(0, 0, WIDTH, HEIGHT));
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(200 * game.ground.dimension, HEIGHT));
	background.setFillColor(sf::Color(100, 100, 250));


	//Setting Up Textures
	sf::Texture marioT1, marioT2, groundT, 
		gameoverT, brickT, enemyT, mushroomT, coinsT, heartT;
	marioT1.loadFromFile("images/sFront.png");
	marioT2.loadFromFile("images/walk.png");
	groundT.loadFromFile("images/groundbrick.png");
	gameoverT.loadFromFile("images/gameover.png");
	brickT.loadFromFile("images/brick.png");
	enemyT.loadFromFile("images/eStand.png");
	mushroomT.loadFromFile("images/mushroom.png");
	heartT.loadFromFile("images/heart.png");

	//Linking Sprites to textures
	sf::Sprite marioS1(marioT1), marioS2(marioT2),
		groundS(groundT), gameoverS(gameoverT),
		brickS(brickT), enemyS(enemyT), 
		mushroomS(mushroomT), heartS(heartT);

	//launching program
	while (window.isOpen())
	{
		game.mario.lastx = game.mario.x;
		game.mario.lasty = game.mario.y;

		//checking events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//clear window
		window.clear();
		game.Loop();

		// draw everything here...
		window.draw(background);
		if (game.mario.x < game.mario.lastx) {
			marioS1.setTextureRect(sf::IntRect(game.mario.width,
				0, -game.mario.width, game.mario.height));
			marioS2.setTextureRect(sf::IntRect(game.mario.width,
				0, -game.mario.width, game.mario.height));
		}
		else if (game.mario.x > game.mario.lastx) {
			marioS1.setTextureRect(sf::IntRect(0, 0, game.mario.width, 
				game.mario.height));
			marioS2.setTextureRect(sf::IntRect(0, 0, game.mario.width,
				game.mario.height));
		}
		if (game.mario.walk == true)
		{
			marioS2.setPosition(game.mario.x,
				game.mario.y); window.draw(marioS2);
		}
		else {
			marioS1.setPosition(game.mario.x,
				game.mario.y); window.draw(marioS1);
		}
		for (int y = game.ground.y; 
			y<game.ground.y + game.ground.height; 
			y += game.ground.dimension)
			for (int x = game.ground.x;
				x <game.ground.x + game.ground.width; 
				x += game.ground.dimension)
			{
				groundS.setPosition(x, y);  window.draw(groundS);
			}

		//drawing bricks
		for (int y = game.brick.y;
			y<game.brick.y + game.brick.height;
			y += game.brick.dimension)
			for (int x = game.brick.x; 
				x < game.brick.x + game.brick.width;
				x += game.brick.dimension)
			{
				brickS.setPosition(x, y);  window.draw(brickS);
			}

		for (int y = game.brick2.y; 
			y<game.brick2.y + game.brick2.height; 
			y += game.brick2.dimension)
			for (int x = game.brick2.x;
				x < game.brick2.x + game.brick2.width;
				x += game.brick2.dimension)
			{
				brickS.setPosition(x, y);  window.draw(brickS);
			}

		for (int y = game.brick3.y; 
			y<game.brick3.y + game.brick3.height;
			y += game.brick3.dimension)
			for (int x = game.brick3.x;
				x < game.brick3.x + game.brick3.width;
				x += game.brick3.dimension)
			{
				brickS.setPosition(x, y);  window.draw(brickS);
			}

		for (int x = 0; x < game.mario.health * 21; x += 21)
		{
			heartS.setPosition(camera.osszx + x, 1);  window.draw(heartS);
		}
		enemyS.setPosition(game.enemy.x,
			game.enemy.y);  window.draw(enemyS);
		if (game.mushroom.dead == false)
		{ mushroomS.setPosition(game.mushroom.x, game.mushroom.y); 
		window.draw(mushroomS); 
		}

		if (game.mario.end == true && game.mario.health <= 0)
		{
			window.clear();
			gameoverS.setPosition(camera.osszx + 100, 0);
			window.draw(gameoverS);
		}
		else if (game.mario.end == true)
		{
			view.setCenter(WIDTH / 2, HEIGHT / 2);
			camera.osszx = 0;
			game.mario.health--;

			game.mario.end = false;

			game.Setup(); 
		}
		// window.draw(...);
		float time = clock1.getElapsedTime().asSeconds();
		clock1.restart();
		timer1 += time;
		//Animating the camera
		if (timer1> delay1) 
		{

			camera.Shift(game.mario);
			view.move(camera.x, 0);

			timer1 = 0;
		}
		//Preventing mario from going out of range
		game.mario.Block(camera.osszx); 
		window.setView(view);
		//ending frame
		window.display();
	}
	return 0;
}