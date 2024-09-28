#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.hpp"

// thien ly oi!!!!!
// ENEMY class inheriting from Entity
class ENEMY : public Entity
{
private:
    // To store the initial position for respawn
    float initial_x, initial_y;

    // Timer to track respawn after death
    float timer_respawn = 0;

    // Flag to indicate if the enemy is dead
    bool isDead = false;

    // Flag to control visibility (for hiding the enemy after death)
    bool isVisible = true;

public:
    // Constructor initialize: animation + position
    ENEMY(AnimationManager &a, Level &lev, int x, int y) : Entity(a, x, y)
    {
        // Save initial position for respawning later
        initial_x = x;
        initial_y = y;

        // Name, speed, health, and initial animation
        option("Enemy", 0.01, 15, "move");
    }

    // Update function to control the enemy's behavior
    void update(float time)
    {
        // If the enemy is dead, track time to respawn
        if (isDead)
        {
            // Hide the enemy after it dies
            isVisible = false; // Make the enemy invisible

            // Track the time after death to manage respawn
            timer_respawn += time;

            // Respawn after 3 seconds (3000 units of time)
            if (timer_respawn > 3000)
            {
                respawn(); // Call the respawn function
            }

            return; // Skip the rest of the update logic while dead
        }

        // Update position based on its velocity (speed) and time
        x += dx * time;

        // Increment the timer to track movement direction change
        timer += time;

        // Reverse direction every 3200 units of time (3.2s)
        if (timer > 3200)
        {
            dx *= -1; // Reverse direction
            timer = 0;
        }

        // If health is less than or equal to 0, mark the enemy as dead
        if (Health <= 0)
        {
            anim.set("dead"); // Switch animation to "dead"
            dx = 0; // Stop movement

            // Track how long the enemy has been "dead"
            timer_end += time;

            // After 4000 units of time, switch the state to "dead"
            if (timer_end > 4000)
            {
                isDead = true; // Mark enemy as dead
                timer_respawn = 0; // Start the respawn timer
            }
        }

        // Update the animation based on elapsed time
        anim.tick(time);
    }

    // Respawn the enemy with full health at the initial position
    void respawn()
    {
        Health = 15;        // Reset health
        x = initial_x;      // Reset to initial x position
        y = initial_y;      // Reset to initial y position
        anim.set("move");   // Set animation to "move"
        dx = 0.01;          // Reset speed
        isDead = false;     // Bring the enemy back to life
        isVisible = true;   // Make the enemy visible again
        timer_respawn = 0;  // Reset respawn timer
        timer_end = 0;      // Reset death timer
    }

};

#endif // ENEMY_H

