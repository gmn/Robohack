/*
=======================================================
initialize.c
=======================================================
*/

#include "globals.h"
#include "structs.h"
#include "defs.h"
#include "robohack.h"

void initialize ( void )
{

        // GLOBAL VARIABLE initializations
        game.frame = 0;
        game.lock = OFF;
        game.blammo_p = NULL;
        game.score = 100;
        game.lives = 3;
        game.level = 1;
        game.tmp = 0;           // used to compute the wait time in STATE_WAIT
        game.n = 0;             // used to initialize the wait period of STATE_WAIT
        game.i = 0;             // used for extra guy handling in STATE_PLAY
        game.j = 0;             // used for displaying messages on the screen
        game.k = 0;             // used to display family bonus messagej
        game.tmp2 = 0;          // used to calculate the duration of the message
        game.tmp3 = 0;          // used in tabulating proper scoring for family
	game.tmp4 = 0;
        game.fam_num = 1;
        game.free_guy_num = 1;
        game.faster = 0;        // used to make badguys speed up per round
        game.timer = 1;         // used to adjust speed to round time
        game.tight = 0;         // used to speed up at end of round
        game.intro = 1;
        game.intro2 = 1;
	game.highscore = 0;
	badguys.hulk_p = NULL;
        hero.dir = 0;
        hero.moves = 0;
        hero.x = HERO_START_X;
        hero.y = HERO_START_Y;
        hero.bullet_p = NULL;
        hero.n = 0;
        string2[hero.y][hero.x] = '@';

        // set random seed
        srand (time(NULL));

}
