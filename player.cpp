#include "player.h"

void Mario::Physics(Ground &ground)
{
	if (y >= ground.y - height 
		&& y < ground.y + ground.dimension 
		&& x + width > ground.x 
		&& x < ground.x + ground.width)
	{
		gravity = 0;
		y = ground.y - height;
		jump = false;
	}
}
void Mario::Block(int &osszx)
{
	if (osszx > x)
	{
		x = osszx;
	}
}
void Mario::Gravity()
{
	gravity += velocity;
	y += gravity;
}
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
void Enemy::Gravity()
{
	gravity += velocity;
	y += gravity;
}
void Enemy::AI(int limit)
{
	if (max <= limit && dead == false)
	{
		x++;
		max++;
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
	}
}
void Enemy::Kill(Mario &mario)
{
	if (x <= mario.x + mario.width &&
		x + width >= mario.x &&
		y <= mario.y + mario.height &&
		y + height >= mario.y && mario.lasty < mario.y)
	{
		dead = true;
	}
	else if (x <= mario.x + mario.width &&
		x + width >= mario.x &&
		y <= mario.y + mario.height &&
		y + height >= mario.y && dead == false)
	{
		mario.end = true;
	}
}
