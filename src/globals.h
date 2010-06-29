/*
=======================================================
globals.h
=======================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/time.h>
#include <sys/signal.h>
#include <time.h>

// Global Variable Declarations
char string2[20][76], temp[20][76];

struct {
        int score;
        int lives;
        int frame;
        int level;
        int state;
	int free_guy_num;	// used to count which freeguy were on
	int fam_num; 		// used to score family collection
        int screenCols;         // screen columns
        int screenRows;         // screen rows
        int timer;              // round timer
        int lock;               // turn on lock to prevent kernel call
        struct itimerval myTimer;   // alarm signal timer
	struct EXPLOSION *blammo_p;
	int tmp;
	int n;
	int i; 			// used to control free guys	
	int j;			// used to print the bonus guy message
	int k;			// flag: used to turn on fam_num sign
	int l;			// used to turn on pause before gameoversign
	int tmp2;		//
	int tmp3;
	int tmp4;		// used for pause before gameover sign
	int faster;		// used to make badguys speed up
	int tight;		// also used to make badguys speed up
	int intro;
	int intro2;
	int gameover;
	int highscore;		// flag turns on flashing
} game;

struct HERO {
        int x, y;               // hero position
        int dir, n;
        int moves;              // # of moves
        int *move_p;            // buffered moves
        struct BULLET *bullet_p;
} hero;

struct {
	struct HULK *hulk_p;
        struct GRUNT *grunt_p;
	struct TRODE *trode_p;
} badguys;

/* There are Mommy, Daddy, and Mikey family characters in the
    real game */

struct {
	struct FAMILY *family_p;
} goodguys;
