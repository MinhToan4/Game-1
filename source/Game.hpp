#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "level.hpp"
#include "Animation.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "MovingPlatform.hpp"
#include "HealthBar.hpp"
#include <SFML/Audio.hpp>
#include "Result.hpp"

using namespace sf;

/**
 * Main game function that initializes and runs the game loop.
 * Handles rendering, input, updates, and game logic.
 */
void RunGame()
{
	float timer_end = 0;
	int check_end = 0;

	// Load score image and create texture
	sf::Image imgscore;
	imgscore.loadFromFile("files/images/score.png");
	sf::Texture tscore;
	imgscore.createMaskFromColor(sf::Color(255, 255, 255));
	tscore.loadFromImage(imgscore);
	sf::Sprite sscore;
	sscore.setTexture(tscore);

	// Load background music
	SoundBuffer buffer; // Holds audio data
	if (!buffer.loadFromFile("files/nhachay.wav"))
	{
		std::cerr << "Failed to load sound file!" << std::endl;
		return;
	}
	Sound sound;			 // Create Sound object
	sound.setBuffer(buffer); // Associate buffer with sound
	sound.setLoop(true);	 // Loop the music
	sound.setVolume(65);	 // Set volume level

	// Load textures for game assets
	Texture enemy_t, moveplatform_t, megaman_t, bullet_t, bg;

	// Create game window
	RenderWindow window(VideoMode(450, 280), "2D Platformer Game");
	View view(FloatRect(200, 0, 450, 280)); // Set up camera view
	Result res_score;
	Level lvl; // Create level object

	// Load level and background based on score
	if (cnt > 5)
	{
		lvl.LoadFromFile("files/Level2.tmx");
		bg.loadFromFile("files/images/bg3.png");
		sound.play(); // Play background music
	}
	else
	{
		lvl.LoadFromFile("files/Level1.tmx");
		bg.loadFromFile("files/images/bg.png");
		sound.play(); // Play background music
	}

	// Load additional textures
	enemy_t.loadFromFile("files/images/enemy.png");
	moveplatform_t.loadFromFile("files/images/movingPlatform.png");
	megaman_t.loadFromFile("files/images/megaman.png");
	bullet_t.loadFromFile("files/images/bullet.png");

	// Set up animations for player and entities
	AnimationManager anim;
	anim.loadFromXML("files/anim_megaman.xml", megaman_t);
	anim.animList["jump"].loop = 0;

	AnimationManager anim2; // For bullets

	// Create bullet animations
	anim2.create("move", bullet_t, 7, 10, 8, 8, 1, 0);					  // Single frame for moving bullet
	anim2.create("explode", bullet_t, 27, 7, 18, 18, 4, 0.01, 29, false); // Explosion animation, no loop

	AnimationManager anim3;									   // For enemies
	anim3.create("move", enemy_t, 0, 0, 16, 16, 2, 0.002, 18); // Moving animation
	anim3.create("dead", enemy_t, 58, 0, 16, 16, 1, 0);		   // Death animation, single frame

	AnimationManager anim4; // For moving platforms
	anim4.create("move", moveplatform_t, 0, 0, 95, 22, 1, 0);

	// Create background sprite
	Sprite background(bg);
	background.setOrigin(bg.getSize().x / 2, bg.getSize().y / 2);

	// Manage all game entities
	std::list<Entity *> entities;
	std::list<Entity *>::iterator it;

	// Load enemies from level
	std::vector<Object> e = lvl.GetObjects("enemy");
	for (int i = 0; i < e.size(); i++)
	{
		entities.push_back(new ENEMY(anim3, lvl, e[i].rect.left, e[i].rect.top));
	}

	// Load moving platforms
	e = lvl.GetObjects("MovingPlatform");
	for (int i = 0; i < e.size(); i++)
	{
		entities.push_back(new MovingPlatform(anim4, lvl, e[i].rect.left, e[i].rect.top));
	}

	// Load player
	Object pl = lvl.GetObject("player");
	PLAYER Mario(anim, lvl, pl.rect.left, pl.rect.top);

	// Health bar for player
	HealthBar healthBar;

	// Time management
	Clock clock;
	sf::Text mytext;
	sf::Font font;
	font.loadFromFile("arial.ttf");
	mytext.setFont(font);
	mytext.setColor(sf::Color::Red);

	// Main game loop
	while (window.isOpen())
	{
		// Calculate time elapsed since last frame
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart(); // Reset clock for next frame

		time = time / 600; // Scale time for appropriate animation and movement speed

		if (time > 40)
			time = 40; // Cap time to maintain smooth frame rate

		Event event;
		// Process events
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				res_score.writescore(cnt);
				window.close();
			}

			// Handle key presses for shooting
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					entities.push_back(new Bullet(anim2, lvl, Mario.x + 18, Mario.y + 18, Mario.dir));
				}
			}
		}

		// Handle continuous key presses
		if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
			Mario.key["L"] = true;
		if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
			Mario.key["R"] = true;
		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
			Mario.key["Up"] = true;
		if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
			Mario.key["Down"] = true;
		if (Keyboard::isKeyPressed(Keyboard::Space))
			Mario.key["Space"] = true;
		if (Keyboard::isKeyPressed(Keyboard::P))
			res_score.fre = -1;
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			res_score.fre = 11;

		// Update entities
		for (it = entities.begin(); it != entities.end();)
		{
			Entity *b = *it;
			b->update(time); // Update entity state

			// Remove dead entities
			if (b->life == false)
			{
				it = entities.erase(it);
				delete b;
			}
			else
			{
				it++; // Move to next entity
			}
		}

		// Update player and health bar
		Mario.update(time);
		healthBar.update(Mario.Health);

		// Handle collisions
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// Enemy collision
			if ((*it)->Name == "Enemy")
			{
				Entity *enemy = *it;

				if (enemy->Health <= 0)
					continue; // Skip dead enemies

				if (Mario.getRect().intersects(enemy->getRect()))
				{ // Player collides with enemy
					if (Mario.dy > 0)
					{					   // Player is falling on enemy
						enemy->dx = 0;	   // Stop enemy movement
						Mario.dy = -0.2;   // Bounce player up
						enemy->Health = 0; // Defeat enemy
					}
					else if (!Mario.hit)
					{						// Player is hit
						Mario.Health -= 15; // Reduce health
						Mario.hit = true;	// Set hit flag
						// Push player back
						if (Mario.dir)
							Mario.x += 10;
						else
							Mario.x -= 10;
					}
				}

				// Check bullet-enemy collisions
				for (std::list<Entity *>::iterator it2 = entities.begin(); it2 != entities.end(); it2++)
				{
					Entity *bullet = *it2;
					if (bullet->Name == "Bullet" && bullet->Health > 0)
					{
						if (bullet->getRect().intersects(enemy->getRect()))
						{
							bullet->Health = 0; // Destroy bullet
							enemy->Health -= 5; // Damage enemy
						}
					}
				}
			}

			// Moving platform collision
			if ((*it)->Name == "MovingPlatform")
			{
				Entity *movPlat = *it;
				if (Mario.getRect().intersects(movPlat->getRect()))
				{
					if (Mario.dy > 0)
					{ // Player is falling
						if (Mario.y + Mario.h < movPlat->y + movPlat->h)
						{										 // Player on top
							Mario.y = movPlat->y - Mario.h + 12; // Position on platform
							Mario.x += movPlat->dx * time;		 // Move with platform
							Mario.dy = 0;						 // Stop falling
							Mario.STATE = PLAYER::stay;			 // Set state to stay
						}
					}
				}
			}
		}

		// Rendering
		view.setCenter(Mario.x, Mario.y); // Center view on player
		window.setView(view);
		sscore.setPosition(Mario.x - 190, Mario.y - 125);

		// Draw background
		background.setPosition(view.getCenter());
		window.draw(background);

		// Draw level
		lvl.Draw(window);

		// Draw entities
		for (it = entities.begin(); it != entities.end(); it++)
		{
			(*it)->draw(window);
		}

		// Position score text
		if (cnt < 10)
		{
			mytext.setPosition(Mario.x - 156, Mario.y - 108);
		}
		else
		{
			mytext.setPosition(Mario.x - 166, Mario.y - 108);
		}

		// Draw player, health bar, and score
		Mario.draw(window);
		healthBar.draw(window);
		std::stringstream ss;
		ss << cnt;
		sscore.setScale(0.5, 0.5);
		mytext.setString(ss.str().c_str());
		window.draw(sscore);
		window.draw(mytext);

		// Handle special screens
		if (res_score.fre == -1)
		{
			res_score.getmax();
			res_score.Draw1(window, "files/images/rank.png", Mario.x - 100, Mario.y - 100);
			res_score.Draw2(window, Mario.x - 10, Mario.y - 10);
		}
		if (Mario.Health <= 0)
		{
			check_end = 1;
			timer_end += time;
			if (timer_end >= 5000)
			{
				res_score.writescore(cnt);
				window.close();
			}
		}
		if (check_end == 1)
		{
			res_score.Draw1(window, "files/images/rip.jpg", Mario.x - 110, Mario.y - 100);
		}
		if (cnt == 5)
		{
			cnt++;
			window.close();
			sound.stop();
			RunGame(); // Restart game for next level
		}

		// Display rendered frame
		window.display();
	}
}

// End of game function
