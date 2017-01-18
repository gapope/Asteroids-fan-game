/*****************************************************************************
 *	Greg Pope							ICS3U	November-January, 2016/2017  *
 *																			 *
 *	A series of functions relating to the asteroid objects for the game		 *
 *	Asteroids																 *
 *****************************************************************************/

#include <allegro.h>
#include <alfont.h> 
#include <math.h>
#include "asteroids.h"

//Function for spawning asteroids
Asteroid genAsteroid(int type) {
	Asteroid newAsteroid;
	int hold = 0;
	
	//-1 indicates the asteroid is new rather than one which has split, picks 
	//a random asteroid size to start with
	if (type == -1) {
		type = rand() % 3 + 1;
	}

	//Stores asteroid size
	newAsteroid.type = type;
	
	//Determining x co-ordinate for new asteroid
	newAsteroid.pos.x = rand() % 850 - 50;
	
	//Determining y co-ordinate for new asteroid and flight angle
	if (newAsteroid.pos.x <= 0 || newAsteroid.pos.x >= 800) { 
		//Asteroid spawned off of right/left side of screen, can be any y-value 
		//within screen dimentions
		newAsteroid.pos.y = rand() % 600;
		
		//Piscks between all rightward angles
		newAsteroid.angle = rand() % 4 - 3;
		if (newAsteroid.pos.x >= 800) { //If on right side, asteroid must fly left
			newAsteroid.angle *= -1;
		}
	}
	else {
		//Asteroid spawned within x-limits of screen, must be out of view above 
		//or below
		hold = rand() % 2;
		
		if (hold == 0) { //Above
			newAsteroid.pos.y = -50;
			hold = rand() % 3;
			
			//Picking random angle
			if (hold == 0) { //Down, right
				newAsteroid.angle = 3;
			}
			else if (hold == 1) { //Down
				newAsteroid.angle = 4;
			}
			else if (hold == 2) { //Down, left
				newAsteroid.angle = -3;
			}
		}
		else if (hold == 1) { //Below
			newAsteroid.pos.y = 650;
			//Picks between all upward angles
			newAsteroid.angle = rand() % 1 - 1;
		}	
	}
	
	//Making asteroid real
	newAsteroid.onScreen = true;
	
	return newAsteroid;
}
END_OF_FUNCTION(genAsteroid);

//Function for creating new asteroids from asteroids that are hit by lasers
Asteroid splitAsteroid(int order, Asteroid asteroid) {
	
	//Changing asteroid type (smaller by onw)
	asteroid.type++;
	
	//Ensuring asteroids don't spawn on top of eachother
	if (order == 1) {
		asteroid.pos.x += 15;
		asteroid.pos.y += 15;
	}
	else {
		asteroid.pos.x -= 15;
		asteroid.pos.y -= 15;
	}
	
	//Determining asteroid angle, completely random to lower predictability
	asteroid.angle = rand() % 4 - 3;
	
	//Making asteroid interactible
	asteroid.onScreen = true;
	
	return asteroid;
}
END_OF_FUNCTION(splitAsteroid)

//Function for moving asteroids that have been spawned
Asteroid moveAsteroid(Asteroid asteroid) {
	if (asteroid.angle == -3) { //Down, left
		asteroid.pos.y += 3;
		asteroid.pos.x -= 3;
	}
	else if (asteroid.angle == -2) { //Left
		asteroid.pos.x += 5;
	}
	else if (asteroid.angle == -1) { //Up, left
		asteroid.pos.y -= 3;
		asteroid.pos.x -= 3;
	}
	else if (asteroid.angle == 0) { //Up
		asteroid.pos.y += 5;
	}
	else if (asteroid.angle == 1) { //Up, right
		asteroid.pos.y -= 3;
		asteroid.pos.x += 3;
	}
	else if (asteroid.angle == 2) { //Right
		asteroid.pos.x += 6;
	}
	else if (asteroid.angle == 3) { //Down, right
		asteroid.pos.y += 3;
		asteroid.pos.x += 3;
	}
	else if (asteroid.angle == 4) { //Down
		asteroid.pos.y += 5;
	}
	
	//Checking if asteroid has left screen
	if ((asteroid.pos.x < -50 || asteroid.pos.x > 850 || asteroid.pos.y < -50 || asteroid.pos.y > 650)) {
		asteroid.onScreen = false;
	}
	
	return asteroid;	
}
END_OF_FUNCTION(moveAsteroid);

//Function for checking collision between an asteroid and another object
bool checkCollision(int typeA, int typeO, Coordinate asteroid, Coordinate object) {
	//Creating bounding box for asteroid
	int asteroid_bb_left = 0;
	int asteroid_bb_top = 0;
	int asteroid_bb_right = 0;
	int asteroid_bb_bottom = 0;
	if (typeA == 1) {
		asteroid_bb_left = asteroid.x + 9;
		asteroid_bb_top = asteroid.y + 6;
		asteroid_bb_right = (asteroid_bb_left + largeAsteroid->w) - 10;
		asteroid_bb_bottom = (asteroid_bb_top + largeAsteroid->h) - 9;
	}
	else if (typeA == 2) {
		asteroid_bb_left = asteroid.x + 5;
		asteroid_bb_top = asteroid.y + 4;
		asteroid_bb_right = (asteroid_bb_left + medAsteroid->w) - 5;
		asteroid_bb_bottom = (asteroid_bb_top + medAsteroid->h) - 5;	
	}
	else if (typeA == 3) {
		asteroid_bb_left = asteroid.x + 2;
		asteroid_bb_top = asteroid.y + 2;
		asteroid_bb_right = (asteroid_bb_left + smallAsteroid->w - 2);
		asteroid_bb_bottom = (asteroid_bb_top + smallAsteroid->h - 2);	
	}
	
	//Creating bounding box for object
	int object_bb_left = object.x;
	int object_bb_top = object.y;
	int object_bb_right = 0;
	int object_bb_bottom = 0;
	if (typeO == 0) { //Bounding for laser
		object_bb_right = (object_bb_left + laserSprite->w) - 2;
		object_bb_bottom = (object_bb_top + laserSprite->h) - 3;
	}
	else { //Bounding for ship
		object_bb_right = (object_bb_left + (shipStopped->w));
		object_bb_bottom = (object_bb_top + (shipStopped->h));
	}
	
	//Checking for intersction between asteroid and object boundingboxes
	if (object_bb_bottom < asteroid_bb_top || object_bb_top > asteroid_bb_bottom || object_bb_right < asteroid_bb_left || object_bb_left > asteroid_bb_right) {
		return false;
	}	
	else {
		return true;
	}
}
END_OF_FUNCTION(checkCollision);
