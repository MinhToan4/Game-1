#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>

// J97 MCK - HealthBar class for displaying player's health visually
class HealthBar
{
public:
	Texture t;			// Texture for health bar background
	Sprite s;			// Sprite to display health bar texture
	int max;			// Maximum health value
	RectangleShape bar; // Rectangle representing the filled portion of the health bar

	/**
	 * Constructor: Initializes the health bar with default values.
	 */
	HealthBar()
	{
		// Load texture to use as background for health bar
		t.loadFromFile("files/images/HealthBar.png");

		// Set texture to sprite
		s.setTexture(t);

		// Set initial color of bar to black
		bar.setFillColor(Color(0, 0, 0));
		max = 100; // Set maximum health value
	}

	/**
	 * Updates the health bar based on current health value.
	 * @param k Current health value.
	 */
	void update(int k)
	{
		if (k > 0 && k < max)
			// Set size of rectangle based on current health value
			// Height of bar decreases as health decreases
			bar.setSize(Vector2f(10, (max - k) * 70 / max));
	}

	/**
	 * Draws the health bar and background sprite to the provided window.
	 * @param window Reference to the render window.
	 */
	void draw(RenderWindow &window)
	{
		// Get center and size of window's view
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();

		// Set position of sprite slightly offset to the left of view's center
		s.setPosition(center.x - size.x / 2 - 10, center.y - size.y / 2 + 12);

		// Set position of rectangle (health bar) next to the sprite
		bar.setPosition(center.x - size.x / 2 + 15, center.y - size.y / 2 + 13);

		window.draw(s);	  // Draw sprite
		window.draw(bar); // Draw rectangle
	}
};

#endif // HEALTHBAR_H
