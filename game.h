#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <time.h>
#include "player.h"

#define WIDTH 1000
#define HEIGHT 600
//#define sound
using namespace sf;

//Defines the powerups
struct PowerUp
{
	int x, y;
	static constexpr int width = 42, height = 42;

	bool dead;

	float gravity, velocity = 0.5;

	void Physics(Ground &ground);
	void Gravity();
	void AI();
	void Heal(Player &player);
};

//Defines the camera system to view the player as they move
class Camera
{
public:
	int x;
	int osszx;

	void Shift(Player &player);
};

//Defines the game, which includes the setup of the levels, populating the environment with all of the entities, and any other effects
class Game
{
public:
	void Level1();
	void Level2();
	void Loop();

	Player player;

	Ground ground;
	Ground ground2;
	Ground ground3;
	Ground brick;
	Ground brick2;
	Ground brick3;
	Ground brick4;
	Ground brick5;
	Ground brick6;
	Ground brick7;
	Ground brick8;

	Enemy enemy;
	Enemy enemy1;

	PowerUp powerup;

private:

#ifdef sound
	sf::SoundBuffer jumpsoundSB;
	sf::Sound jumpsound;
	sf::Music themesong;

	bool first = true;
#endif

	Clock clock;
	float timer = 0, delay = 0.01;
};
