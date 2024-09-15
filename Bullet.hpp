#ifndef BULLET_H
#define BULLET_H

#include "Entity.hpp"

//song gio J97&MCK
//Bullet class inherits from Entity class, extends function of Entity
//represent a bullet object, handling movement and interactions with solid objects
//use an AnimationManager for animations and updates the bullet's state over time
class Bullet:public Entity
{
public:
	// Level &lev: reference to game level, contains objects like walls, bullet can collide with
	// x, y: position
	// bool dir: direction of the bullet
	// Entity(a, x, y) initializes base class Entity with animation manager and position
	Bullet(AnimationManager &a, Level &lev,int x,int y,bool dir):Entity(a,x,y)
	{
		//"Bullet" name of entity
		//0.3 speed
		//10 dame
		//"move" current animation status
		option("Bullet", 0.3, 10, "move");
		
		//dir == true, bullet moves to left, horizontal velocity dx, speed = 0,3
		//dir == fale, bullet moves to right
		if (dir) dx=-0.3;
		
		//retrieves a list of "soild" objects form game level, bullet may collide with
   		obj = lev.GetObjects("solid");
	}
	
	//update bullet's position and state over time
	void update(float time)
	{
		//moves bullet
		x+=dx*time;
		
		//check collisions between bullet and soild objects
		//getRect() gets rectangle of bullet's bounding box, obj[i].rect is bounding box of solid object
		//bullet -> soild object -> Health = 0 -> bullet destruction
		for (int i=0;i<obj.size();i++)
			if (getRect().intersects(obj[i].rect))
		        {Health=0;}
		
		//Health <= 0 -> animation to "explode", simulating bullet exploding
		//dx = 0 -> stops bullet's movement
		if (Health<=0) {
			anim.set("explode");
			dx=0;
			
			//explosion animation finishes
			// life = false: bullet removed from the game
		    if (anim.isPlaying()==false) life=false;
		}

		//updates animation frame based on elapsed time (time)
		anim.tick(time);
	}

};

#endif BULLET_H
