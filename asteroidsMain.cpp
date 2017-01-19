/*****************************************************************************
 *	Greg Pope							ICS3U	November-January, 2016/2017  *
 *																			 *
 *	Asteroids; a game involving a ship which flies around and destroys 		 *
 *	asteroids whcih split into smaller parts.								 *
 *****************************************************************************/

#include <allegro.h>
#include <alfont.h> 
#include <stdlib.h>
#include "asteroids.h"
#include "asteroids_data.h"


//Defining global variables which were defined as external in header
int score[10], numOfScores, points;
char name[10][20];

//Global bitmap declarations
BITMAP *playButton;
BITMAP *playAgainButton;
BITMAP *highsButton;
BITMAP *creditsButton;
BITMAP *quitButton;
BITMAP *menuButton;
BITMAP *shipStopped;
BITMAP *shipMoving;
BITMAP *laserSprite;
BITMAP *smallAsteroid;
BITMAP *medAsteroid;
BITMAP *largeAsteroid;

//Creating movement timer (also used for typing)
volatile long speed_counterA = 0;

void increment_speed_counterA() {
	speed_counterA++;
}
END_OF_FUNCTION(increment_speed_counterA); 

//Creating laser timer
volatile long speed_counterB = 0;

void increment_speed_counterB() {
	speed_counterB++;
}
END_OF_FUNCTION(increment_speed_counterB); 

//Creating asteroid timer
volatile long speed_counterC = 0;

void increment_speed_counterC() {
	speed_counterC++;
}
END_OF_FUNCTION(increment_speed_counterC); 


int main() {
	//Initializations
	allegro_init();
	alfont_init();
	set_color_depth(desktop_color_depth());
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_keyboard();
	install_mouse();
	install_timer();
	
	//Movement timer
	LOCK_VARIABLE(speed_counterA);
	LOCK_FUNCTION(increment_speed_counterA);
	install_int_ex(increment_speed_counterA, BPS_TO_TIMER(60));
	//Laser firing timer
	LOCK_VARIABLE(speed_counterB);
	LOCK_FUNCTION(increment_speed_counterB);
	install_int_ex(increment_speed_counterB, BPS_TO_TIMER(60));
	//Asteroid generation timer
	LOCK_VARIABLE(speed_counterC);
	LOCK_FUNCTION(increment_speed_counterC);
	install_int_ex(increment_speed_counterC, BPS_TO_TIMER(60));
	
	//Randomizing seed
	srand(time(0));
	
	//Creating/loading BITMAPs formain game
	BITMAP *buffer = create_bitmap(800, 600);
	shipStopped = loadImage("shipStopped");
	shipMoving = loadImage("shipMoving");
	laserSprite = loadImage("laser");
	smallAsteroid = loadImage("small_Asteroid");
	medAsteroid = loadImage("med_Asteroid");
	largeAsteroid = loadImage("large_Asteroid");
	
	//General use variables for screen control
	int onScreen = 0, i = 0, j = 0;
	bool quit = false;
	 
	//Retrieving and sorting scores
	numOfScores = getHighs();
	sortHighs();

	//Loads main screen
	onScreen = changeScreen(0);
	
	while (!quit) {
		//If there was an issue loading datafile, error is returned
		if (onScreen == -1) {
			return 1;
		}
		else if (onScreen == 0) {	
			while (onScreen == 0) {
				//Primary check is for quitting program, other buttons lead to separate screens
				if ((mouse_b & 1) && mouse_x > 400 - 75 && 
				mouse_x < 400 + 75 && mouse_y > 450 && mouse_y < 4505 + quitButton->h) { //For clicking Quit
					quit = true;
					onScreen = -2;
				}
				else if ((mouse_b & 1) && mouse_x > 400 - 75 && 
				mouse_x < 400 + 75 && mouse_y > 150 && mouse_y < 150 + playButton->h) { //For clicking Play
					onScreen = changeScreen(2);
				}
				else if ((mouse_b & 1) && mouse_x > 400 - 75 && 
				mouse_x < 400 + 75 && mouse_y > 250 && mouse_y < 250 + highsButton->h) { //For clicking Highscores
					onScreen = changeScreen(3);
				}
				else if((mouse_b & 1) && mouse_x > 400 - 75 && 
				mouse_x < 400 + 75 && mouse_y > 350 && mouse_y < 350 + creditsButton->h) { //For clicking Credits
					onScreen = changeScreen(4);
				}
			}
		}
		else if (onScreen == 2) { //Difficulty choice screen
			if ((mouse_b & 1) && mouse_x > 600 - (playButton->w / 2) && 
				mouse_x < 600 + (playButton->w / 2) && mouse_y > 192 && mouse_y < 192 + playButton->h) {
					onScreen = changeScreen(1);
		}
			else if ((mouse_b & 1) && mouse_x > 635 && mouse_x < 775 && 
			mouse_y > 575 - menuButton->h && mouse_y < 575) { //Returns to main menu
				onScreen = changeScreen(0);
			}
		}
		else if (onScreen == 3) { //Highscore screen
			if ((mouse_b & 1) && mouse_x > 635 && mouse_x < 775 && 
			mouse_y > 575 - menuButton->h && mouse_y < 575) { //Returns to main menu
				onScreen = changeScreen(0);
			}
		}
		else if (onScreen == 4) { //Credit screen
			if ((mouse_b & 1) && mouse_x > 635 && mouse_x < 775 && 
			mouse_y > 575 - menuButton->h && mouse_y < 575) { //Returns to main menu
				onScreen = changeScreen(0);
			}
		}
		else if (onScreen == 51) { //Game over screen
			//If user score is a highscore a click will lead to highscore screens, 
			//otherwise buttons are displayed for playing again and main menu
            if (points <= score[9]) {
                if ((mouse_b & 1) && mouse_x > 25 && mouse_x < 175 &&
                    mouse_y > 575 - menuButton->h && mouse_y < 575) { //Begins a new game
                    onScreen = changeScreen(1);
                }
                else if ((mouse_b & 1) && mouse_x > 635 && mouse_x < 775 &&
                         mouse_y > 575 - menuButton->h && mouse_y < 575) { //Returns to main menu
                    onScreen = changeScreen(0);
                }
            }
            else {
                if (mouse_b & 1) {
                	//Adding new highschore to array
                	score[9] = points;
                	strcpy(name[9], "\0");
                	
                	if (numOfScores < 10) {
                		numOfScores++;
					}
                    onScreen = changeScreen(52);
                }
            }
		}
        else if (onScreen == 52) { //Highscore name collection screen
        	int len = 0;
			//Text entering for highscore name, moves to next screen on enter
			//Makes sure the user cannot enter an empty string
            while (!key[KEY_ENTER] || strcmp(name[9], "\0") == 0) {
				if (speed_counterA % 3 == 0) {
			        len = enterKeys(buffer, len);
				}
			}
            onScreen = changeScreen(53);
        }
        else if (onScreen == 53) { //Highscore display screen
            if ((mouse_b & 1) && mouse_x > 25 && mouse_x < 175 &&
                mouse_y > 575 - menuButton->h && mouse_y < 575) { //Begins a new game
                onScreen = changeScreen(1);
            }
            else if ((mouse_b & 1) && mouse_x > 635 && mouse_x < 775 &&
                     mouse_y > 575 - menuButton->h && mouse_y < 575) { //Returns to main menu
                onScreen = changeScreen(0);
            }
        }
		else if (onScreen == 1) { //Game screen
			//Defining 
			Laser laser[50];
			Asteroid asteroid[10];
		
			//Initializing lasers and asteroids
			for (i = 0; i < 50; i++) {
				laser[i].pos.x = 0;
				laser[i].pos.y = 0;
				laser[i].angle = 0;
				laser[i].onScreen = false;
			}
			for (i = 0; i < 10; i++) {
				asteroid[i].pos.x = 0;
				asteroid[i].pos.y = 0;
				asteroid[i].angle = 0;
				asteroid[i].onScreen = false;
			}
		
			//Game specific variables, reset for every new game
			int move = 0, lasers= 0, asteroids = 0;
			float angle = 0;
			bool collide = false;
		
			points = 0;
		
			//Spawning ship when game screen loads
			Coordinate ship;
			ship.x = 400 - (shipStopped->w / 2);
			ship.y = 300 - (shipStopped->h / 2);
		
			//Reseting game timers
			speed_counterA = 0;
			speed_counterB = 0;
			speed_counterC = 0;
		
			while (onScreen == 1) { //Game screen
				while (speed_counterA > 0) {
			
					//Ship movement
					if (key[KEY_UP] && key[KEY_RIGHT]){
						ship.y -= 3;
						ship.x += 3;
						angle = 32;
					}
					else if (key[KEY_UP] && key[KEY_LEFT]){
						ship.y -= 3;
						ship.x -= 3;
						angle = 224;
					}
					else if (key[KEY_DOWN] && key[KEY_RIGHT]) {
						ship.y += 3;
						ship.x += 3;
						angle = 96;
					}
					else if (key[KEY_DOWN] && key[KEY_LEFT]) {
						ship.y += 3;
						ship.x -= 3;
						angle = 160;
					}
					else if (key[KEY_UP]){
						ship.y -= 6;
						angle = 0;
					}
					else if (key[KEY_RIGHT]) {
						ship.x += 6;
						angle = 64;
					}
					else if (key[KEY_LEFT]) {
						ship.x -= 6;
						angle = 192;
					}
					else if (key[KEY_DOWN]) {
						ship.y += 6;
						angle = 128;
					}
					clear_keybuf();
				
					//Laser movement
					for (i = 0; i < 50; i++) {
						laser[i] = moveLaser(laser[i]);
					}
				
					//Asteroid movement
					for (i = 0; i < 10; i++) {
						asteroid[i] = moveAsteroid(asteroid[i]);
					}
				
					speed_counterA--;
				}
			
				//Key trigger for laser firing, if is first as having timer first 
				//would cause many hits not to be properly registered especially if 
				//tapping too fast, this allows firing at will with a fastest firing of every 0.15s
				if (key[KEY_SPACE]) {
					//Laser firing timer
					while (speed_counterB > 9) {
					
						if (lasers >= 49) {
							lasers = 0;
						}
					
						//Laser shooting
						laser[lasers] = fireLaser(angle, ship.x, ship.y);
						lasers++;
						speed_counterB -= 10;
					}
					clear_keybuf();
				}	
			
				//Asteroid spawning counter
				while (speed_counterC > 59) { //Spawns an asteroiud every second
					//Keeping asteroids within array range
					if (asteroids >= 9){
						asteroids = 0;
					}
				
					//Generating asteroid
					asteroid[asteroids] = genAsteroid(-1);
					asteroids++;
					speed_counterC -= 60;
				}
			
				//If ship goes out top, it comes in bottom; vice versa
				if (ship.y <= 0 - ((shipStopped->h / 2))) {
					ship.y += (600);
				}
				else if (ship.y >= 600 - ((shipStopped->h / 2))) {
					ship.y -= (600);
				}
			
				//If ship goes out left, it comes in right; vice versa
				if (ship.x <= 0 - ((shipStopped->w / 2))) {
					ship.x += (800);
				}
				else if (ship.x >= 800 - ((shipStopped->w / 2))) {
					ship.x -= (800);
				}
			
				//Drawing lasers
				for (i = 0; i < 50; i++) {
					if (laser[i].onScreen) {
						rotate_sprite(buffer, laserSprite, laser[i].pos.x, laser[i].pos.y, ftofix(laser[i].angle));	
					}
				}
				
				//Drawing ship
				if (key[KEY_UP] || key[KEY_DOWN] || key[KEY_LEFT] || key[KEY_RIGHT]) {
					rotate_sprite(buffer, shipMoving, ship.x, ship.y, ftofix(angle)); //Ship sprite with engines firing
				}
				else {
					rotate_sprite(buffer, shipStopped, ship.x, ship.y, ftofix(angle)); //Ship sprite no flames
				}

				//Drawing asteroids
				for (i = 0; i < 10; i++) {
					if (asteroid[i].onScreen == true) {
						//Drawing sprite based on asteroid type
						if (asteroid[i].type == 1) { //Large asteroid
							draw_sprite(buffer, largeAsteroid, asteroid[i].pos.x, asteroid[i].pos.y);
						}
						else if (asteroid[i].type == 2) { //Medium asteroid
							draw_sprite(buffer, medAsteroid, asteroid[i].pos.x, asteroid[i].pos.y);
						}
						else if (asteroid[i].type == 3) { //Small asteroid
							draw_sprite(buffer, smallAsteroid, asteroid[i].pos.x, asteroid[i].pos.y);
						}
					}
				}

				//Checks bb collisions
				for (i = 0; i < 50; i++) {
					for (j = 0; j < 10; j++) {
						if (laser[i].onScreen && asteroid[j].onScreen) {
							collide = checkCollision(asteroid[j].type, 0, asteroid[j].pos, laser[i].pos);
							if (collide) {
								laser[i].onScreen = false;
								asteroid[j].onScreen = false;
							
								points += 100 * asteroid[j].type;
								
								//Splitting med or large asteroids into 2 asteroids one type down
								if (asteroid[j].type < 3) { 
									asteroid[asteroids] = splitAsteroid(1, asteroid[j]);
									asteroid[j] = splitAsteroid(2, asteroid[j]);
									asteroids++;
								}
							}
						}
					}
				}
			
				//Printing score
				textprintf_ex(buffer, font, 10, 5, WHITE, -1, "Score: %d", points);
				textprintf_ex(buffer, font, 660, 5, WHITE, -1, "Press esc to quit");
			
				// Blit the buffer
				blit(buffer, screen, 0, 0, 0, 0, 800, 600); 
				clear(buffer);
				
				for (i = 0; i < 10; i++) {
					if (asteroid[i].onScreen) {
						collide = checkCollision(asteroid[i].type, 1, asteroid[i].pos, ship);
					
						if (collide) {
							onScreen = changeScreen(51);
						}	
					}
				}
			
				//To leave game screen and return to main menu
				if (key[KEY_ESC]) {
					onScreen = changeScreen(0);
				}
			}
		}
	}
	
	//Freeing memory
	destroy_bitmap(playButton);
	destroy_bitmap(highsButton);
	destroy_bitmap(creditsButton);
	destroy_bitmap(quitButton);
	destroy_bitmap(shipStopped);
	destroy_bitmap(shipMoving);
	destroy_bitmap(laserSprite);
	destroy_bitmap(smallAsteroid);
	destroy_bitmap(medAsteroid);
	destroy_bitmap(largeAsteroid);
	
	return 0;
}
END_OF_MAIN()
