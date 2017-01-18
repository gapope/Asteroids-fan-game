/*****************************************************************************
 *	Greg Pope							ICS3U	November-January, 2016/2017  *
 *																			 *
 *	A series of functions relating to the laser objects for the game		 *
 *	Asteroids																 *
 *****************************************************************************/

#include <allegro.h>
#include <alfont.h> 
#include "asteroids.h"

//Function for creating laser projectiles
Laser fireLaser(float angle, int ship_x, int ship_y) {
	Laser laser;
	
	//Loading sound file from datafile
	DATAFILE *laserShot = NULL;
	laserShot = load_datafile_object("asteroids.dat", "laser_Shot");
	
	//Error checking
	if (laserShot->dat == NULL) {
		allegro_message("Error loading laser_Shot.wav");
	}
	else {
		laser.onScreen = true;
		laser.angle = angle;
	
		//Laser movement based on stored angle
		switch ((int) laser.angle) {
			case 0:		laser.pos.x = ship_x + ((shipStopped->w ) / 2) - 2; //up
						laser.pos.y = ship_y;
						break;
			case 32:	laser.pos.x = ship_x + (shipStopped->w ) - 6; //Up, right
						laser.pos.y = ship_y - 3;
						break;
			case 64:	laser.pos.x = ship_x + ((shipStopped->w) / 2); //Right
						laser.pos.y = ship_y  + ((shipStopped->h) / 2) - 8;
						break;
			case 96:	laser.pos.x = ship_x + (shipStopped->w) - 7; //Down, right
						laser.pos.y = ship_y + (shipStopped->h) - 14;
						break;
			case 128:	laser.pos.x = ship_x + ((shipStopped->w) / 2) - 2; //Down
						laser.pos.y = ship_y + (shipStopped->h) - 7; 
						break;
			case 160:	laser.pos.x = ship_x; //Down, left
						laser.pos.y = ship_y + (shipStopped->h) - 13;
						break;
			case 192:	laser.pos.x = ship_x; //Left
						laser.pos.y = ship_y  + ((shipStopped->h) / 2) - 8;
						break;
			case 224:	laser.pos.x = ship_x + 4; //Up, left
						laser.pos.y = ship_y;
						break;
		}
	
		//Playing sound for shot
		play_sample((SAMPLE*) laserShot->dat, 255, 127, 1000, 0);
	}
	
	return laser;
}
END_OF_FUNCTION(fireLaser);

//Functrion for moving lasers that have been fired
Laser moveLaser(Laser laser) {
	switch ((int) laser.angle) {
		case 0:		laser.pos.y -= 8; //Up
					break;
		case 32:	laser.pos.x += 4; //Up, right
					laser.pos.y -= 4;
					break;
		case 64:	laser.pos.x += 8; //Right
					break;
		case 96:	laser.pos.x += 4; //Down, right
					laser.pos.y += 4;
					break;
		case 128:	laser.pos.y += 8; //Down
					break;
		case 160:	laser.pos.x -= 4; //Down, left
					laser.pos.y += 4;
					break;
		case 192:	laser.pos.x -= 8; //Left
					break;
		case 224:	laser.pos.x -= 4; //Up, left
					laser.pos.y -= 4;
					break;
	}
	
	//Checking if laser has left the screen
	if (laser.pos.x < 0 || laser.pos.x > 800 || laser.pos.y < 0 || laser.pos.y > 600) {
		laser.onScreen = false;
	}
	
	return laser;
}
END_OF_FUNCTION(moveLaser);
