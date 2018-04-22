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
	player.timer += time;

	if (timer > delay)
	{
		timer = 0;

		//Takes in the player's keyboard controls
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player.x -= 3;

		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			player.x += 3;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
#ifdef sound
			if (jumpsound.getStatus() != sf::Music::Status::Playing)
				jumpsound.play();
#endif

			player.jump = true;
		}

		//Creates the player's jump
		if (player.jump == true)
		{
			float energy = 15;
			player.y -= energy;
		}

		//Animates the player's walk
		if (player.timer > player.delay &&
			(player.x != player.lastx || player.y != player.lasty))
		{
			player.timer = 0;

			if (player.walk == false || player.jump == true)
				player.walk = true;
			else
				player.walk = false;
		}
		else if (player.x == player.lastx && player.y == player.lasty)
		{
			player.walk = false;
		}
		//Applies the gravity to the player, enemy, and the powerups
		player.Gravity();
		enemy.Gravity();
		powerup.Gravity();
		coin.Gravity();
		//Places the bricks in the environment and gives them collision
		
		enemy1.Physics(enemy1.x,enemy1.y);
		player.Physics(brick);
		player.Physics(brick2);
		player.Physics(brick3);
		player.Physics(brick4);
		player.Physics(brick5);
		player.Physics(brick6);
		player.Physics(brick7);
		player.Physics(brick8);
		player.Physics(ground);
		player.Physics(ground2);
		player.Physics(ground3);
		enemy.Physics(brick);
		enemy.Physics(brick2);
		enemy.Physics(brick3);
		enemy.Physics(brick4);
		enemy.Physics(brick5);
		enemy.Physics(brick6);
		enemy.Physics(brick7);
		enemy.Physics(brick8);
		enemy.Physics(ground);
		enemy.Physics(ground2);
		enemy.Physics(ground3);
		powerup.Physics(brick);
		powerup.Physics(brick2);
		powerup.Physics(brick3);
		powerup.Physics(brick4);
		powerup.Physics(brick5);
		powerup.Physics(brick6);
		powerup.Physics(brick7);
		powerup.Physics(brick8);
		powerup.Physics(ground);
		powerup.Physics(ground2);
		powerup.Physics(ground3);
		coin.Physics(brick);
		coin.Physics(brick2);
		coin.Physics(brick3);
		coin.Physics(brick4);
		coin.Physics(brick5);
		coin.Physics(brick6);
		coin.Physics(brick7);
		coin.Physics(brick8);
		coin.Physics(ground);
		coin.Physics(ground2);
		coin.Physics(ground3);


		//Gives the enemies and powerups their respective AI
		enemy.AI(300);
		enemy1.AI(300);
		powerup.AI();
		coin.AI();

		//Dictates whether the enemy or player has been healed or killed
		enemy.Kill(player);
		enemy1.Kill(player);
		powerup.Heal(player);
		coin.ScoreInc(player);
		//Ends the game
		if (player.y >HEIGHT)
		{
			player.end = true;
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

//Shifts the camera so that if follows the player
void Camera::Shift(Player &player)
{
	if (player.x > osszx + 700)
	{
		x = 4;
		osszx += x;
	} else
	{
		x = 0;
	}
}

//Specifies the collision detection for the powerups
void PowerUp::Physics(Ground &ground)
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

//Sets the value of gravity for the powerups
void PowerUp::Gravity()
{
	gravity += velocity;
	y += gravity;
}

//Makes the powerups move forward continuously
void PowerUp::AI()
{
	x += 2;
}

//Gives the player more health if they grab the powerup
void PowerUp::Heal(Player &player)
{
	if (x <= player.x + player.width &&
		x + width >= player.x &&
		y <= player.y + player.height &&
		y + height >= player.y && dead == false)
	{
		dead = true;
		player.health++;
	}
}


void Coin::Physics(Ground &ground)
{
	if (y >= ground.y - height
		&& y < ground.y + ground.dimension
		&& x + width > ground.x
		&& x < ground.x + ground.width)
	{
		gravity = 0;
		y = ground.y - height;
	}
}

void Coin::Gravity()
{
	gravity += velocity;
	y += gravity;
}

//Similar to powerups, coins will function and move on their own
void Coin::AI()
{
	x += 2;
}

//Coins should function like powerups, but move at a slower speed
void Coin::ScoreInc(Player &player)
{
	if (x <= player.x + player.width &&
		x + width >= player.x &&
		y <= player.y + player.height &&
		y + height >= player.y)
	{
//A coin will be added to the coin total, and the total score will increase
		if(player.CoinTotal != 11)
		{
			player.score += 100;
			player.CoinTotal++;

		}
//If the CoinTotal reaches a certain amount (like 100 in standard games), coin total is reset, and lives increases
		else 
			{
			player.score += 100;
			player.CoinTotal = 0;
			player.health++;
			}
	}
}

//Populates the environment with the player, enemies, bricks, and ground tiles
//creation of level 1
void Game::Level1()
{
	//places player on the floor
	player.x = 200;
	player.y = 500;

	enemy.x = 600;
	enemy.y = 100;
	enemy.dead = false;

	enemy1.x = 300;
	enemy1.y = 300;
	enemy.dead = false;

	powerup.x = 100;
	powerup.y = 100;
	powerup.dead = false;

	ground.x = 0;
	ground.y = HEIGHT - (2 * ground.dimension);
	ground.width = 100 * ground.dimension;
	ground.height = 2 * ground.dimension;

	brick.x = 100;
	brick.y = 320;
	brick.width = 4 * brick.dimension;
	brick.height = 1 * brick.dimension;

	coin1.x = 100;
	coin1.y = 370;
	coin1.width = 1 * coin1.dimension;
	coin1.height = 1 * coin1.dimension;

	coin2.x = 152;
	coin2.y = 370;
	coin2.width = 1 * coin2.dimension;
	coin2.height = 1 * coin2.dimension;

	coin3.x = 204;
	coin3.y = 370;
	coin3.width = 1 * coin3.dimension;
	coin3.height = 1 * coin3.dimension;

	coin4.x = 256;
	coin4.y = 370;
	coin4.width = 1 * coin4.dimension;
	coin4.height = 1 * coin4.dimension;

	coin5.x = 308;
	coin5.y = 370;
	coin5.width = 1 * coin5.dimension;
	coin5.height = 1 * coin5.dimension;


	brick2.x = 400;
	brick2.y = 150;
	brick2.width = 3 * brick.dimension;
	brick2.height = 1 * brick.dimension;


	brick3.x = 900;
	brick3.y = 320;
	brick3.width = 8 * brick.dimension;
	brick3.height = 1 * brick.dimension;

	coin6.x = 900;
	coin6.y = 370;
	coin6.width = 1 * coin6.dimension;
	coin6.height = 1 * coin6.dimension;

	coin7.x = 952;
	coin7.y = 370;
	coin7.width = 1 * coin7.dimension;
	coin7.height = 1 * coin7.dimension;

	coin8.x = 1004;
	coin8.y = 370;
	coin8.width = 1 * coin8.dimension;
	coin8.height = 1 * coin8.dimension;

	coin9.x = 1056;
	coin9.y = 370;
	coin9.width = 1 * coin9.dimension;
	coin9.height = 1 * coin9.dimension;

	coin10.x = 1108;
	coin10.y = 370;
	coin10.width = 1 * coin10.dimension;
	coin10.height = 1 * coin10.dimension;

	coin11.x = 1160;
	coin11.y = 370;
	coin11.width = 1 * coin11.dimension;
	coin11.height = 1 * coin11.dimension;

	coin12.x = 1212;
	coin12.y = 370;
	coin12.width = 1 * coin12.dimension;
	coin12.height = 1 * coin12.dimension;
}

//creation of level 2
void Game::Level2()
{
	player.x = 50;
	player.y = 500;

	ground.x = 0;
	ground.y = HEIGHT - (2 * ground.dimension);
	ground.width = 5 * ground.dimension;
	ground.height = 2 * ground.dimension;

	brick.x = 250;
	brick.y = 320;
	brick.width = 2 * brick.dimension;
	brick.height = 1 * brick.dimension;

	brick2.x = 450;
	brick2.y = 150;
	brick2.width = 2 * brick.dimension;
	brick2.height = 1 * brick.dimension;

	brick3.x = 700;
	brick3.y = 320;
	brick3.width = 2 * brick.dimension;
	brick3.height = 1 * brick.dimension;

	ground2.x = 850;
	ground2.y = HEIGHT - (2 * ground2.dimension);
	ground2.width = 5 * ground2.dimension;
	ground2.height = 2 * ground2.dimension;

	coin1.x = 850;
	coin1.y = HEIGHT - (2 * coin1.dimension) + 52;
	coin1.width = 1 * coin1.dimension;
	coin1.height = 1 * coin1.dimension;

	coin2.x = 902;
	coin2.y = HEIGHT - (2 * coin2.dimension) + 52;
	coin2.width = 1 * coin2.dimension;
	coin2.height = 1 * coin2.dimension;

	coin3.x = 954;
	coin3.y = HEIGHT - (2 * coin3.dimension) + 52;
	coin3.width = 1 * coin3.dimension;
	coin3.height = 1 * coin3.dimension;

	coin4.x = 1006;
	coin4.y = HEIGHT - (2 * coin4.dimension) + 52;
	coin4.width = 1 * coin4.dimension;
	coin4.height = 1 * coin4.dimension;

	brick4.x = 1225;
	brick4.y = 320;
	brick4.width = 1 * brick.dimension;
	brick4.height = 1 * brick.dimension;

	brick5.x = 1420;
	brick5.y = 320;
	brick5.width = 1 * brick.dimension;
	brick5.height = 1 * brick.dimension;

	brick6.x = 1620;
	brick6.y = 320;
	brick6.width = 1 * brick.dimension;
	brick6.height = 1 * brick.dimension;

	ground3.x = 1785;
	ground3.y = HEIGHT - (2 * ground2.dimension);
	ground3.width = 10 * ground2.dimension;
	ground3.height = 2 * ground2.dimension;

	coin5.x = 1785;
	coin5.y = HEIGHT - (2 * coin5.dimension) + 52;
	coin5.width = 1 * coin5.dimension;
	coin5.height = 1 * coin5.dimension;

	coin6.x = 1837;
	coin6.y = HEIGHT - (2 * coin6.dimension) + 52;
	coin6.width = 1 * coin6.dimension;
	coin6.height = 1 * coin6.dimension;

	coin7.x = 1889;
	coin7.y = HEIGHT - (2 * coin7.dimension) + 52;
	coin7.width = 1 * coin7.dimension;
	coin7.height = 1 * coin7.dimension;

	coin8.x = 1941;
	coin8.y = HEIGHT - (2 * coin8.dimension) + 52;
	coin8.width = 1 * coin8.dimension;
	coin8.height = 1 * coin8.dimension;

	coin9.x = 1993;
	coin9.y = HEIGHT - (2 * coin9.dimension) + 52;
	coin9.width = 1 * coin9.dimension;
	coin9.height = 1 * coin9.dimension;
}