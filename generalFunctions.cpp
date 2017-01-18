/*****************************************************************************
 *	Greg Pope							ICS3U	November-January, 2016/2017  *
 *																			 *
 *	A series of general functions for the game Asteroids					 *
 *****************************************************************************/

#include <allegro.h>
#include <alfont.h> 
#include <stdio.h>
#include <stdlib.h>
#include "asteroids.h"
#include "asteroids_data.h"

//Function for loading BITMAPs and background of new screen
int changeScreen(int toLoad) {
	
	//Creating alternate larger font for title
	ALFONT_FONT *title = alfont_load_font("C:/Windows/Fonts/arial.ttf"); 
    alfont_set_font_size(title, 65); 
	
	DATAFILE *data = NULL;
	data = load_datafile("asteroids.dat");
	
	//General variable
	int i = 0;
	
	//Checking for proper loading
	if (data == NULL) {
		allegro_message("Unable to load asteroids.dat");
		return -1;
	}
	else {
		//Loading BITMAPs from datafile
		playButton = loadImage("play_Button");
		playAgainButton = loadImage("playAgain_Button");
		highsButton = loadImage("highs_Button");
		creditsButton = loadImage("credits_Button");
		quitButton = loadImage("quit_Button");
		menuButton = loadImage("menu_Button");
	
		if (toLoad == 0) { //Loads menu screen
			//Setting background
			clear_to_color(screen, WHITE);
		
			//Printing title
			alfont_textprintf_aa_ex(screen, title, 280, 25, BLACK, -1, "Asteroids");
		
			//Blitting button BITMAPs
			blit(playButton, screen, 0,0, 400 - (playButton->w / 2), 150, playButton->w, playButton->h);
			blit(highsButton, screen, 0,0, 400 - (highsButton->w / 2), 250, highsButton->w, highsButton->h);
			blit(creditsButton, screen, 0,0, 400 - (creditsButton->w / 2), 350, creditsButton->w, creditsButton->h);
			blit(quitButton, screen, 0,0, 400 - (creditsButton->w / 2), 450, quitButton->w, quitButton->h);
	
			show_mouse(screen);	
			
			return 0;
		}
		else if (toLoad == 1) { //Loads game screen
			//Setting background
			clear_to_color(screen, BLACK);
			
			return 1;
		}
		else if (toLoad == 2) { //Loads difficulty screen
			//Setting background
			clear_to_color(screen, WHITE);
			
			//PRinting how to play text
			alfont_textprintf_aa_ex(screen, title, 20, 100, BLACK, -1, "How to play:");
			textprintf_ex(screen, font, 30, 180, BLACK, -1, "Arrow keys for movement (you CAN move diagonally)");
			textprintf_ex(screen, font, 30, 195, BLACK, -1, "Space to shoot (you CAN move and shoot)");
			textprintf_ex(screen, font, 30, 210, BLACK, -1, "If an asteroid hits you it's game over");
			textprintf_ex(screen, font, 30, 225, BLACK, -1, "Destroying asteroids awards you points");
			textprintf_ex(screen, font, 30, 240, BLACK, -1, "Large asteroids = 100pts");
			textprintf_ex(screen, font, 30, 255, BLACK, -1, "Medium asteroids = 200pts");
			textprintf_ex(screen, font, 30, 270, BLACK, -1, "Small asteroids = 300pts");
			
			//Blitting button BITMAPs
			blit(playButton, screen, 0, 0, 600 - (playButton->w / 2), 192, playButton->w, playButton->h);
			blit(menuButton, screen, 0, 0, 800 - (menuButton->w + 25), 600 - (menuButton->h + 25), menuButton->w, menuButton->h);
			
            show_mouse(screen);
			return 2;
		}
		else if (toLoad == 3) { //Loads highscore screen
			//Setting background
			clear_to_color(screen, WHITE);
			
			
			//Displaying title and high scores
			alfont_textprintf_aa_ex(screen, title, 260, 25, BLACK, -1, "Highscores");
			if (numOfScores == 0) {
				textprintf_centre_ex(screen, font, 400, 300, BLACK, -1, "No highscores have been set yet");
			}
			else {
				for (i = 0; i < numOfScores; i++) {
					textprintf_centre_ex(screen, font, 400, 150 + (20 * i), BLACK, -1, "%s %d", name[i], score[i]);
				}
			}
			
			//Blitting button BITMAP
			blit(menuButton, screen, 0, 0, 800 - (menuButton->w + 25), 600 - (menuButton->h + 25), menuButton->w, menuButton->h);
			
            show_mouse(screen);
			return 3;
		}
		else if (toLoad == 4) { //Loads credits screen
			//Setting background
			clear_to_color(screen, WHITE);
			
            //Displaying title and credits
            alfont_textprintf_aa_ex(screen, title, 300, 25, BLACK, -1, "Credits");
            textprintf_centre_ex(screen, font, 400, 190, BLACK, -1, "Program written by Gregory Pope");
            textprintf_centre_ex(screen, font, 400, 230, BLACK, -1, "Special thanks to Ms. Lindsay Cullum, Miasya Bulger,");
            textprintf_centre_ex(screen, font, 400, 250, BLACK, -1, "and the other members of the fall ICS3U class for code advice.");
            textprintf_centre_ex(screen, font, 400, 270, BLACK, -1, "Additional advice was obtained from the users of the StackOverflow forums");
            textprintf_centre_ex(screen, font, 400, 310, BLACK, -1, "Ship sprites created by deviantART user Kryptid");
            textprintf_centre_ex(screen, font, 400, 350, BLACK, -1, "Asteroid sprites created by Aperico");
            textprintf_centre_ex(screen, font, 400, 390, BLACK, -1, "Laser sprite created by Pip53098");
            
			//Blitting button BITMAPs
			blit(menuButton, screen, 0, 0, 800 - (menuButton->w + 25), 600 - (menuButton->h + 25), menuButton->w, menuButton->h);
			
            show_mouse(screen);
			return 4;
		}
		else if (toLoad == 51) { //Loads game over points screen
			//Setting background
			clear_to_color(screen, BLACK);
			
			//Printing text
			alfont_textprintf_aa_ex(screen, title, 250, 25, WHITE, -1, "GAME OVER");
			alfont_textprintf_aa_ex(screen, title, 175, 260, WHITE, -1, "Your score was: %d", points);
            
            //Blitting buttons if highscores has not been achieved
            if (points <= score[9]) {
                blit(playAgainButton, screen, 0, 0, 25, 575 - playAgainButton->h, playAgainButton->w, playAgainButton->h);
                blit(menuButton, screen, 0, 0, 775 - menuButton->w, 575 - menuButton->h, menuButton->w, menuButton->h);
            }
            else {
                alfont_textprintf_aa_ex(screen, title, 175, 380, makecol(255, 0, 0), -1, "NEW HIGHSCORE");
                
                textprintf_centre_ex(screen, font, 400, 500, WHITE, -1, "** click to conitue **");
            }
            
            show_mouse(screen);
            return 51;
        }
        else if (toLoad == 52) {
            //Setting background
            clear_to_color(screen, BLACK);
            
            show_mouse(screen);
            return 52;
        }
        else if (toLoad == 53) { //Loads game over highscores screen
            //Setting background
            clear_to_color(screen, BLACK);
            
            //Sorting and saving scores
			sortHighs();
            saveHighs();
            
            //Displaying highscores and title
            alfont_textprintf_aa_ex(screen, title, 260, 25, WHITE, -1, "Highscores");
            for (i = 0; i < numOfScores; i++) {
                textprintf_centre_ex(screen, font, 400, 150 + (20 * i), WHITE, -1, "%s %d", name[i], score[i]);
            }
            
            //Blitting buttons
			blit(playAgainButton, screen, 0, 0, 25, 575 - playAgainButton->h, playAgainButton->w, playAgainButton->h);
			blit(menuButton, screen, 0, 0, 775 - menuButton->w, 575 - menuButton->h, menuButton->w, menuButton->h);
			
			show_mouse(screen);
			return 53;
		}
	}
}
END_OF_FUNCTION(changeScreen);

//Function for loading BITMAPs from the datafile
BITMAP* loadImage(const char image[20]) {
	DATAFILE *data = NULL;
	data = load_datafile("asteroids.dat");
	
	//Error checking
	if (data == NULL) {
		allegro_message("Unable to load asteroids.dat");
		return NULL;
	}
	else {
		if (strcmp(image, "play_Button") == 0) {
			return (BITMAP*) data[play_Button].dat;
		}
		else if (strcmp(image, "playAgain_Button") == 0) {
			return (BITMAP*) data[playAgain_Button].dat;
		}
		else if (strcmp(image, "highs_Button") == 0) {
			return (BITMAP*) data[highs_Button].dat;
		}
		else if (strcmp(image, "credits_Button") == 0) {
			return (BITMAP*) data[credits_Button].dat;
		}
		else if (strcmp(image, "quit_Button") == 0) {
			return (BITMAP*) data[quit_Button].dat;
		}
		else if (strcmp(image, "menu_Button") == 0) {
			return (BITMAP*) data[menu_Button].dat;
		}
		else if (strcmp(image, "shipStopped") == 0) {
			return (BITMAP*) data[ship_Sprite].dat;
		}
		else if (strcmp(image, "shipMoving") == 0) {
			return (BITMAP*) data[ship_Moving].dat;
		}
		else if (strcmp(image, "laser") == 0) {
			return (BITMAP*) data[laser_Sprite].dat;
		}
		else if (strcmp(image, "small_Asteroid") == 0) {
			return (BITMAP*) data[small_Asteroid].dat;
		}
		else if (strcmp(image, "med_Asteroid") == 0) {
			return (BITMAP*) data[med_Asteroid].dat;
		}
		else if (strcmp(image, "large_Asteroid") == 0) {
			return (BITMAP*) data[large_Asteroid].dat;
		}
	}
	
}
END_OF_FUNCTION(loadImage);
