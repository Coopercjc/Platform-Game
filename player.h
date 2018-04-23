#pragma once

//Represents the ground tiles
struct Ground
{
	int dimension = 42;
	int x, y;
	int width, height;
};

//Represents the player character
struct Player
{
	int x, y;
	int lastx, lasty;

	float timer, delay = 0.25;
	bool walk;

	static constexpr int width =50, height = 55;

	bool jump;
	float energy = 15;
	bool end = false;

	float gravity, velocity = 0.5;

	int health = 1;

	int score = 0;
	int CoinTotal = 0;

	void Physics(Ground &ground);
	
	void Block(int &osszx);
	void Gravity();
	bool contact(Ground &ground);
};

//Represents the enemy entities
struct Enemy
{
	double x, y;
	int xx, yy;
	int counter, counter1;
	static constexpr int width = 42, height = 42;

	int max, max2, c;
	float orbit;
	bool maxi;

	bool dead;

	float gravity, velocity = 0.5;

	void Physics(Ground &ground);
	void Physics(int x, int y);
	void Gravity();
	void AI(double x1, double x2);
	void Orbit(int a, int b, int r);
	void Kill(Player &player);
	void Kill1(Player &player);
};

struct SCoin {
	bool Collected;
	int dimension = 42;
	int x, y;
	void Collect();
	int width, height;
	void Poof(Player & player);
};