/*****************************************************************************
 *	Greg Pope							ICS3U	November-January, 2016/2017  *
 *																			 *
 *	A series of highscore functions for the game Asteroids					 *
 *****************************************************************************/

#include <allegro.h>
#include <alfont.h> 
#include <stdio.h>
#include "asteroids.h"
#include "asteroids_data.h"

//Function to allow the user to enter a name via the keyboard without using stdin
int enterKeys(BITMAP *buffer, int len) {
	//Declaring variables for use in collecting new highscore
    int keyEnt = 0;
	char keyHold;
	
	//Preventing multiple printing of same key
	while (keypressed()) {
		//Reading key from keyboard and making it useable
		keyEnt = readkey();
		keyHold = keyEnt & 0xff;
		
		//Deleting if backspace char is pressed
		if (key[KEY_BACKSPACE]) {
			name[9][len] = '\0';
			len--; //This solved an issue I was having for one reason or another
		}
		else if (keyHold >= 32 && keyHold <= 126) { //Adding chars to name string
			len = strlen(name[9]);
		
			//Replacing spaces with underscores to sovle issues with fscanf
			if (keyHold == 32) {
				keyHold = '_';
			}
		
			if (len < 19) { //Restricting the number of characters you can enter, any more than this and character is now stable
				//Adding new character nto end of string and moving end of string character
				name[9][len] = keyHold;
				name[9][len + 1] = '\0';
			}
		}
	clear_keybuf();
	}
				
	//Printing text
    textprintf_centre_ex(buffer, font, 400, 300, WHITE, -1, "What is your name: %s", name[9]);
	textprintf_centre_ex(buffer, font, 400, 500, WHITE, -1, "** press enter to conitue **");
	// Blit the buffer
	blit(buffer, screen, 0, 0, 0, 0, 800, 600); 
	clear(buffer);
						
	return len;
}
END_OF_FUNCTION(enterKeys);

//Function for reading highscores from .txt
int getHighs() {
	FILE *fptr;
	int numOfScores = 0, i = 0;
	
	fptr = fopen("highs.txt", "r");
	
	if  (fptr == NULL) {
		allegro_message("Unable to load highs.txt");
		return -1;
	}
	else {
		fscanf(fptr, "%d", &numOfScores);
		
		for (i = 0; i < numOfScores; i++) {
			fscanf(fptr, "%s %d", name[i], &score[i]);
		}
	}
    
    fclose(fptr);
	
    return numOfScores;
}
END_OF_FUNCTION(getHighs);

//Function to sort highs highest-lowest
void sortHighs() {
	int i = 0, j = 0, intHold = 0;
	char charHold[20] = "";
	
    //Sorting scores highest-lowest
	for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (score[i] > score[j]) {
                intHold = score[i];
                strcpy(charHold, name[i]);
                score[i] = score[j];
                strcpy(name[i], name[j]);
                score[j] = intHold;
                strcpy(name[j], charHold);
            }
        }
	}
}
END_OF_FUNCTION(sortHighs);

//Function to save highs to the highs.txt file
void saveHighs() {
    FILE *fptr;
    int i = 0;
    
    fptr = fopen("highs.txt", "w");
    
    //Error checking
    if (fptr == NULL) {
        allegro_message("Unable to load highs.txt");
    }
    else {
    	fprintf(fptr, "%d\n", numOfScores);
        //Writing scores to file
        for (i = 0; i < numOfScores; i++) {
            fprintf(fptr, "%s %d\n", name[i], score[i]);
        }
    }
    
    fclose(fptr);
}
END_OF_FUNCTION(saveHighs);
