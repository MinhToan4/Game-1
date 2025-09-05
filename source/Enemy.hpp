#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

int cnt = 0; // Global counter for score or enemy count

/**
 * ENEMY class inheriting from Entity.
 * Represents an enemy entity with movement, death, and sound effects.
 */
class ENEMY : public Entity
{
private:
	// To store the initial position for respawn
	float initial_x, initial_y;

	// Flag to indicate if the enemy is dead
	bool isDead = false;

	// Flag to control visibility (for hiding the enemy after death)
	bool isVisible = true;

	// Flag to ensure sound is played only once on death
	bool soundPlayed = false;

	// Sound-related members
	sf::SoundBuffer buffer; // Holds audio data
	sf::Sound sound;		// Sound object

public:
	/**
	 * Constructor: Initializes animation and position.
	 * @param a AnimationManager reference.
	 * @param lev Level reference.
	 * @param x Initial x position.
	 * @param y Initial y position.
	 */
	ENEMY(AnimationManager &a, Level &lev, int x, int y) : Entity(a, x, y)
	{
		// Save initial position for respawning later
		initial_x = x;
		initial_y = y;

		// Set name, speed, health, and initial animation
		option("Enemy", 0.01, 15, "move");

		// Load sound file into buffer
		if (!buffer.loadFromFile("files/siu.wav"))
		{
			// Handle error if the file cannot be loaded
			std::cerr << "Error loading sound file!" << std::endl;
			return;
		}
		sound.setBuffer(buffer); // Associate buffer with sound
		sound.setVolume(500);	 // Set volume level
	}

	/**
	 * Update function to control the enemy's behavior.
	 * @param time Time elapsed since last update.
	 */
	void update(float time)
	{
		// Update position based on velocity and time
		x += dx * time;

		// Increment timer to track movement direction change
		timer += time;

		// Reverse direction every 3200 units of time (3.2s)
		if (timer > 3200)
		{
			dx *= -1; // Reverse direction
			timer = 0;
		}

		// If health is less than or equal to 0, mark as dead
		if (Health <= 0 && !isDead)
		{
			anim.set("dead"); // Switch to death animation
			dx = 0;			  // Stop movement
			cnt++;			  // Increment score counter
			sound.play();	  // Play death sound
			isDead = true;	  // Mark as dead
			timer_end = 0;	  // Reset death timer
		}

		// If dead, count time to make disappear after 4 seconds
		if (isDead)
		{
			timer_end += time;
			if (timer_end > 4000)
			{
				life = false; // Remove enemy after 4 seconds
			}
		}

		// Update animation
		anim.tick(time);
	}
};

#endif // ENEMY_H
