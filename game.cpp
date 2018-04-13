#include "game.h"


void Game::Loop()
{
#ifdef sound
	if (first) 
	{
		jumpsoundSB.loadFromFile("audio/jumpsound.ogg");
		jumpsound.setBuffer(jumpsoundSB);
		themesong.openFromFile("audio/themesong.ogg");

		first = false;
	}
#endif

	float time = clock.getElapsedTime().asSeconds();
	clock.restart();
	timer += time;
	mario.timer += time;

	if (timer > delay)
	{ 
		timer = 0;

		//Keyboard Controls
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			mario.x -= 3;

		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			mario.x += 3;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
#ifdef sound
			if (jumpsound.getStatus() != sf::Music::Status::Playing)
				jumpsound.play();
#endif

			mario.jump = true;
		}

		//The actual jump
		if (mario.jump == true)
		{
			float energy = 15; 
			mario.y -= energy;
		}

		//Walking animations
		if (mario.timer > mario.delay && 
			(mario.x != mario.lastx || mario.y != mario.lasty))
		{
			mario.timer = 0;

			if (mario.walk == false || mario.jump == true)
				mario.walk = true;
			else
				mario.walk = false;
		}
		else if (mario.x == mario.lastx && mario.y == mario.lasty)
		{
			mario.walk = false;
		}
		//Gravity
		mario.Gravity();
		enemy.Gravity();
		mushroom.Gravity();
		//Bricks
		mario.Physics(brick);
		mario.Physics(brick2);
		mario.Physics(brick3);
		mario.Physics(ground);
		enemy.Physics(brick);
		enemy.Physics(brick2);
		enemy.Physics(brick3);
		enemy.Physics(ground);
		mushroom.Physics(brick);
		mushroom.Physics(brick2);
		mushroom.Physics(brick3);
		mushroom.Physics(ground);

		//Adding AI
		enemy.AI(300);
		mushroom.AI();

		//Healing or Killing
		enemy.Kill(mario);
		mushroom.Heal(mario);
		//End of game 
		if (mario.y >HEIGHT)
		{
			mario.end = true;
#ifdef sound	
			themesong.stop();
#endif
		}
	}

#ifdef sound
	if (themesong.getStatus() != sf::Music::Status::Playing)
		themesong.play();
#endif

}
void Camera::Shift(Mario &mario)
{
	if (mario.x > osszx + 700)
	{
		x = 4;
		osszx += x;
	}
	else if (mario.x < (osszx + 100) && osszx > 0) 
	{
	x = -4;
	osszx -= x;
	}
	else
	{
		x = 0;
	}
}
void Mushroom::Physics(Ground &ground)
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
void Mushroom::Gravity()
{
	gravity += velocity;
	y += gravity;
}
void Mushroom::AI()
{
	x += 3;
}
void Mushroom::Heal(Mario &mario)
{
	if (x <= mario.x + mario.width &&
		x + width >= mario.x &&
		y <= mario.y + mario.height &&
		y + height >= mario.y && dead == false)
	{
		dead = true;
		mario.health++;
	}
}
void Game::Setup()
{
	mario.x = 200;
	mario.y = 500;

	enemy.x = 600;
	enemy.y = 100;
	enemy.dead = false;

	mushroom.x = 100;
	mushroom.y = 100;
	mushroom.dead = false;

	ground.x = 0;
	ground.y = HEIGHT - (2 * ground.dimension);
	ground.width = 30 * ground.dimension;
	ground.height = 2 * ground.dimension;

	brick.x = 100;
	brick.y = 320;
	brick.width = 4 * brick.dimension;
	brick.height = 1 * brick.dimension;

	brick2.x = 400;
	brick2.y = 150;
	brick2.width = 3 * brick.dimension;
	brick2.height = 1 * brick.dimension;


	brick3.x = 1900;
	brick3.y = 320;
	brick3.width = 8 * brick.dimension;
	brick3.height = 1 * brick.dimension;

}