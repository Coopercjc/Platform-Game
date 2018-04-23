#include "player.h"
#include <math.h>

//Designs the gravity and the physics of the player.
//Also designs the collision detection of the bricks.
void Player::Physics(Ground &ground)
{
	int midway = ground.y;
	int midline = (ground.width / 2) + ground.x;
	//Checks if the player clips through the top of the block
	if (y + height >= ground.y
		&& y < midway
		&& x + width >= ground.x
		&& x < ground.x + ground.width)
	{
		gravity = 0;
		y = ground.y - height;
		jump = false;
	}
	//Checks if the player clips through the bottom of the block
	else if (y > midway
		&& y < ground.y + ground.dimension
		&& x + width > ground.x
		&& x < ground.x + ground.width)
	{
		gravity = 0;
		y = ground.y + ground.dimension;
		jump = false;
	}

	//Checks if the player clips through the left of the block
	if (y + height > ground.y
		&& y < ground.y + ground.height
		&& x < midline
		&& x + width >= ground.x)
	{
		gravity = 0;
		x = ground.x - width;
		y += 10;
		jump = false;
	}
	//Checks if the player clips through the right of the block
	else if (y + height > ground.y
		&& y < ground.y + ground.height
		&& x < ground.x + ground.width
		&& x + width >= midline)
	{
		gravity = 0;
		x = ground.x + ground.width;
		y += 10;
		jump = false;
	}

}

bool Player::contact(Ground &ground)
{
	bool output = false;
	if (y + height >= ground.y
		&& y < ground.y + ground.height
		&& x + width >= ground.x
		&& x < ground.x + ground.width)
	{
		output = true;
	}
	return output;
}


//Prevents the player from moving left off the screen
void Player::Block(int &osszx)
{
	if (osszx > x)
	{
		x = osszx;
	}
}

//Sets the value of the gravity for the player
void Player::Gravity()
{
	gravity += velocity;
	y += gravity;
}

//Sets the gravity so that the walking enemies fall once they fall off of a platform
void Enemy::Physics(Ground &ground)
{
	if (y >= ground.y - height
		&& y < ground.y + ground.dimension
		&& x + width > ground.x
		&& x < ground.x + ground.width && dead == false)
	{
		gravity = 0;
		y = ground.y - height;
		
	}
}

//Once the enemy is killed, it will fall through the ground
void Enemy::Physics(int a, int b) {
	x = a;
	y = b;

	if (dead) {
		gravity += velocity;
		y += gravity;
	}

	
}

void SCoin::Poof(Player &player)
{
	if (x <= player.x + player.width &&
		x + width >= player.x &&
		y <= player.y + player.height &&
		y + height >= player.y && player.lasty < player.y)
	{
		Collected = true;
		player.CoinTotal++;
	}
	else if (x <= player.x + player.width &&
		x + width >= player.x &&
		y <= player.y + player.height &&
		y + height >= player.y)
	{
		Collected = true;
		player.CoinTotal++;
	}

}

void SCoin::Collect() {

	if (Collected) {
		x = 5000;
		y = 5000;
	}
}

//Sets the value of gravity for the enemies
void Enemy::Gravity()
{
	gravity += velocity;
	y += gravity;
}

//Makes the enemy walk back and forth
void Enemy::AI(double x1, double x2)
{
	
	if (x > x1 && maxi == false)
	{
		x-= 0.1;
		if (x <= x1) {
			maxi = true;
		}
	}
	else if (x < x2 && maxi == true)
	{
		x+= 0.1;
		if (x >= x2) {
			maxi = false;
		}
	}
	
	/*if (max <= limit && dead == false)
	{
		x++;
		max++;;
	}
	else if (max2 <= limit && dead == false)
	{
		x--;
		max2++;
	}

	if (max2 > limit && maxi == false)
	{
		max = 0;
		maxi = true;
	}
	if (max > limit && maxi == true)
	{
		max2 = 0;
		maxi = false;
	}*/

}

void Enemy::Orbit(int a, int b, int r) {
	
	x = a + (r*cos(orbit));
	y = b + (r*sin(orbit));


	orbit += 0.0025;
}

//Determines whether the enemy is killed or if the player is killed by the enemy.
//If the enemy is killed then the player jumps off of it
void Enemy::Kill(Player &player)
{
	
	if (x <= player.x + player.width &&
		x + width >= player.x &&
		y <= player.y + player.height &&
		y + height >= player.y && player.lasty < player.y)
	{
		dead = true;
		if (counter == 0) {
			player.score++;
			counter++;
		}

	}
	else if (x <= player.x + player.width &&
		x + width >= player.x &&
		y <= player.y + player.height &&
		y + height >= player.y && dead == false)
	{
		player.end = true;
	}
}

void Enemy::Kill1(Player &player)
{

	if (x <= player.x + player.width &&
		x + width >= player.x &&
		y <= player.y + player.height &&
		y + height >= player.y && dead == false)
	{
		player.end = true;
		if (counter1 == 0) {
			player.score++;
			counter1++;
		}
	}
}