/*****************************************************************************
 *	Greg Pope						ICS3U		December-January, 2016-2017  *
 *																			 *
 *	Header file for global variables, structs and function prototyping for   *
 *	asteroids game															 *
 *****************************************************************************/

#ifndef ASTEROIDS_H_
#define ASTEROIDS_H_

//Defining colour constants for text printing and background setting
#define WHITE makecol(255, 255, 255)
#define BLACK makecol(0, 0, 0)

#include <allegro.h>
#include <alfont.h> 

//Made global so size pointers can be used throughout, 
//external to solve multiple definition errors
extern BITMAP *playButton;
extern BITMAP *playAgainButton;
extern BITMAP *highsButton;
extern BITMAP *creditsButton;
extern BITMAP *quitButton;
extern BITMAP *menuButton;
extern BITMAP *shipStopped;
extern BITMAP *shipMoving;
extern BITMAP *laserSprite;
extern BITMAP *smallAsteroid;
extern BITMAP *medAsteroid;
extern BITMAP *largeAsteroid;

//Highscore variables are made global; technically bad, 
//but makes simplifies printing greatly
extern int score[10], numOfScores, points;
extern char name[10][20];

//Struct declarations
struct Coordinate {
	int x, y;
};

struct Laser {
	Coordinate pos;
	float angle;
	bool onScreen;
};

struct Asteroid {
	Coordinate pos;
	int type;
	int angle;
	bool onScreen;
};

//Function prototyping
int changeScreen(int toLoad);
BITMAP* loadImage(const char image[20]);
int enterKeys(BITMAP *buffer, int len);
int getHighs();
void sortHighs();
void saveHighs();
Laser fireLaser(float angle, int ship_x, int ship_y);
Laser moveLaser(Laser laser);
Asteroid genAsteroid(int type);
Asteroid splitAsteroid(int order, Asteroid asteroid);
Asteroid moveAsteroid(Asteroid asteroid);
bool checkCollision(int typeA, int typeB, Coordinate asteroid, Coordinate object);

#endif
