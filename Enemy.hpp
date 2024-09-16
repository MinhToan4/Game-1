#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.hpp"

// Hoa Hai Duong + Hoa Vo Sac T05
// ENEMY class inheriting from Entity
class ENEMY: public Entity
{
public:
    // Constructor initalize: animation + position
	ENEMY(AnimationManager &a, Level &lev, int x, int y):Entity(a, x, y)
	{
		// name, speed, health, and initial animation
		option("Enemy", 0.01, 15, "move");
	}

    // Update function to control the enemy's behavior
	void update(float time)
	{
		// Update position based on its velocity (speed) and time
		x += dx * time;

		// Increment the timer to track movement direction change
		timer += time;

		// Reverse direction every 3200 units of time (3,2s)
		if (timer > 3200) {
			dx *= -1; // Reverse direction
			timer = 0;
		}

		// health <= 0, play the death animation and stop movement
		if (Health <= 0) {
			anim.set("dead"); // Switch animation to "dead"
			dx = 0; // Stop movement

			// Track how long the enemy has been "dead"
			timer_end += time;

			// After 4000 units of time, mark the enemy as "dead" (life = false)
			if (timer_end > 4000) life = false;
		}

		// Update the animation based on elapsed time
		anim.tick(time);
	}
};

#endif // ENEMY_H

