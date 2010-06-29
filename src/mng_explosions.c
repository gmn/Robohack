/* 
===============================================
mng_explosions.c
===============================================
*/

#include "structs.h"
#include "defs.h"
#include "globals.h"
#include "robohack.h"

void initiateexplosion ( int X, int Y )
{
        explosion_t *new_p;
        new_p = (explosion_t *) malloc (sizeof(explosion_t));
        new_p->x = X;
        new_p->y = Y;
        new_p->n = 0;
        if (new_p->x == 0) ++new_p->x;
        if (new_p->y == 0) ++new_p->y;
        if (new_p->y == 19) --new_p->y;
        if (new_p->x == 75) --new_p->x;
        // attach the explosion to game.blammo_p at the beginning
        // older explosions go to the end of the list
        if (game.blammo_p == NULL) {
                game.blammo_p = new_p;
                new_p->next_p = NULL;
        } else {
                new_p->next_p = game.blammo_p;
                game.blammo_p = new_p;
        }
}

// This func handles explosion animation
// called by trackinteractions
void manageexplosions ( void )
{
        explosion_t *current_p;
        current_p = game.blammo_p;
        while ( current_p != NULL ) {
                if ( current_p->n < 2 ) {
                        string2[current_p->y+1][current_p->x-1] = '\\' ;
                        string2[current_p->y+1][current_p->x+1] ='/' ;
                        string2[current_p->y][current_p->x]= '%' ;
                        string2[current_p->y-1][current_p->x-1]= '/';
                        string2[current_p->y-1][current_p->x+1]= '\\';
                } else if ((current_p->n >= 2) && (current_p->n < 4)) {
                        string2[current_p->y+1][current_p->x-1]= '.' ;
                        string2[current_p->y+1][current_p->x+1]= '.' ;
                        string2[current_p->y][current_p->x]= '.' ;
                        string2[current_p->y-1][current_p->x-1]= '.';
                        string2[current_p->y-1][current_p->x+1]= '.';

                        string2[current_p->y+1][current_p->x]= '|';
                        string2[current_p->y][current_p->x+1]= '-';
                        string2[current_p->y][current_p->x]= '$';
                        string2[current_p->y][current_p->x-1]= '-';
                        string2[current_p->y-1][current_p->x]= '|';
                } else if ((current_p->n >= 4) && (current_p->n < 6)) {
                        string2[current_p->y+1][current_p->x]= '.';
                        string2[current_p->y][current_p->x+1]= '.';
                        string2[current_p->y][current_p->x]= '.';
                        string2[current_p->y][current_p->x-1]= '.';
                        string2[current_p->y-1][current_p->x]= '.';

                        string2[current_p->y+1][current_p->x-1]= '\\';
                        string2[current_p->y+1][current_p->x+1]= '/';
                        string2[current_p->y][current_p->x]= '%';
                        string2[current_p->y-1][current_p->x-1]= '/';
                        string2[current_p->y-1][current_p->x+1]= '\\';
                } else {
                        string2[current_p->y+1][current_p->x-1]= '.';
                        string2[current_p->y+1][current_p->x+1]= '.';
                        string2[current_p->y][current_p->x]= '.';
                        string2[current_p->y-1][current_p->x-1]= '.';
                        string2[current_p->y-1][current_p->x+1]= '.';
                }
                if (current_p->n <= 6)
                        ++current_p->n;
                current_p = current_p->next_p;
        }
        terminateexplosions();
}

void terminateexplosions ( void )
{
        explosion_t *last_p, *current_p;
        // freeup NULL explosion slots
        current_p = game.blammo_p;
        last_p = NULL;
        if (current_p != NULL) {
                if (current_p->next_p != NULL ) {
                        while  (current_p->next_p != NULL) {
                                last_p = current_p;
                                current_p = current_p->next_p;
                        }
                }
        }
        if (current_p != NULL) {
                if (current_p->n > 6) {
                        if (last_p != NULL) {
                                last_p->next_p = NULL;
                        }
                        else {
                                game.blammo_p = NULL;
                        }
                        free ( current_p );
                }
        }
}

