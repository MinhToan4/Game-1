#ifndef BULLET_H
#define BULLET_H

#include "Entity.hpp"
#include <SFML/Audio.hpp>

/**
 * Bullet class inherits from Entity.
 * Represents a bullet object, handling movement and interactions with solid objects.
 * Uses AnimationManager for animations and updates state over time.
 */
class Bullet : public Entity
{
private:
    // Sound-related members
    sf::SoundBuffer buffer; // Holds audio data for explosion sound
    sf::Sound sound;        // Sound object to play the sound

    // Flag to ensure sound is played only once upon collision
    bool soundPlayed = false;

public:
    /**
     * Constructor: Initializes bullet with animation, level, position, and direction.
     * @param a AnimationManager reference.
     * @param lev Level reference containing solid objects.
     * @param x Initial x position.
     * @param y Initial y position.
     * @param dir Direction (true for left, false for right).
     */
    Bullet(AnimationManager &a, Level &lev, int x, int y, bool dir) : Entity(a, x, y)
    {
        // Set entity properties: name, speed, damage, animation
        option("Bullet", 0.3, 10, "move");

        // Set direction: left if dir is true, right otherwise
        if (dir)
        {
            dx = -0.3; // Move left
        }

        // Get list of solid objects for collision detection
        obj = lev.GetObjects("solid");

        // Load explosion sound
        if (!buffer.loadFromFile("files/ban.wav"))
        {
            std::cerr << "Error loading sound file!" << std::endl;
        }
        sound.setBuffer(buffer); // Associate buffer with sound
        sound.setVolume(70);     // Set volume
    }

    /**
     * Updates bullet's position and state over time.
     * @param time Time elapsed since last update.
     */
    void update(float time)
    {
        // Move the bullet
        x += dx * time;

        // Check for collisions with solid objects
        for (int i = 0; i < obj.size(); i++)
        {
            if (getRect().intersects(obj[i].rect))
            {
                Health = 0; // Destroy bullet on collision
            }
        }

        // If bullet is destroyed, play explosion
        if (Health <= 0)
        {
            anim.set("explode"); // Set explosion animation
            dx = 0;              // Stop movement

            // Play sound only once
            if (!soundPlayed)
            {
                sound.play();
                soundPlayed = true;
            }

            // Remove bullet after animation ends
            if (!anim.isPlaying())
            {
                life = false;
            }
        }

        // Update animation
        anim.tick(time);
    }
};

#endif // BULLET_H
