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
	bool end = false;

	float gravity, velocity = 0.5;

	int health = 1;

	void Physics(Ground &ground);
	
	void Block(int &osszx);
	void Gravity();

	int score = 0;
	int CoinTotal = 0;
};

//Represents the enemy entities
struct Enemy
{
	int x, y;
	static constexpr int width = 42, height = 42;

	int max, max2;
	bool maxi;

	bool dead;

	float gravity, velocity = 0.5;

	void Physics(Ground &ground);
	void Physics(int x, int y);
	void Gravity();
	void AI(int limit);
	//void AI(int limit, Player &player);
	void Kill(Player &player);
};