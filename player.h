#pragma once
#include "ground.h"

struct Ground
{
	int dimension = 42; 
	int x, y;
	int width, height; 
};

struct Mario
{
	int x, y;
	int lastx, lasty;

	float timer, delay = 0.25;
	bool walk;

	static constexpr int width = 50, height = 55;

	bool jump;
	bool end = false;

	float gravity, velocity = 0.5;

	int health = 1;

	void Physics(Ground &ground);
	void Block(int &osszx);
	void Gravity();
};

struct Enemy
{
	int x, y;
	static constexpr int width = 42, height = 42;

	int max, max2;
	bool maxi;

	bool dead;

	float gravity, velocity = 0.5;

	void Physics(Ground &ground);
	void Gravity();
	void AI(int limit);
	void Kill(Mario &mario);
};

