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

struct Mushroom
{
	int x, y;
	static constexpr int width = 42, height = 42;

	bool dead;

	float gravity, velocity = 0.5;

	void Physics(Ground &ground);
	void Gravity();
	void AI();
	void Heal(Mario &mario);
};

class Camera
{
public:
	int x;
	int osszx;

	void Shift(Mario &mario);
};

class Game
{
public:
	void Setup();
	void Loop();

	Mario mario;

	Ground ground;
	Ground brick;
	Ground brick2;
	Ground brick3;

	Enemy enemy;

	Mushroom mushroom;

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