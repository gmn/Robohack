/*
==================================================
handle_movement.c
==================================================
*/

#include "structs.h"
#include "defs.h"
#include "globals.h"
#include "robohack.h"

void movehero ( void )
{
        int X, Y, dir;
        dir = hero.dir;
        X = hero.x;
        Y = hero.y;
        if ( dir == 's' ) {
                game.k = 0;
                --X;
                string2[Y][X+1] = '.';
        }
        else if ( dir == 'd' ) {
                game.k = 0;
                --Y;
                string2[Y+1][X] = '.';
        }
        else if ( dir == 'e' ) {
                game.k = 0;
                ++Y;
                string2[Y-1][X] = '.';
        }
        else if ( dir == 'f' ) {
                game.k = 0;
                ++X;
                string2[Y][X-1] = '.';
        }
        /* Series of don't go through walls checks for a static 20x76 room */
        if ( X < 0 )
                X = 0;
        if ( X > 75 )
                X = 75;
        if ( Y < 0 )
                Y = 0;
        if ( Y > 19 )
                Y = 19;
        hero.x = X;
        hero.y = Y;
        ++hero.n;
        string2[Y][X] = '@';
        hero.dir = 0;
}

void movegrunts ( void )
{
        int R, T, pole;
        grunt_t *current_p;
	family_t *family_p;
	hulk_t *hulk_p;
//GRUNT 
        if ( badguys.grunt_p != NULL ) {
                current_p = badguys.grunt_p;
                while (current_p != NULL) {
                        R = current_p->x;
                        T = current_p->y;
        // 3 chances in 4 that the robots advance towards
        // the hero guy
                        if ( rand()%4 == 0 ) {
                                pole = current_p->dir = rand()%4 + 1;
                                string2[T][R] = '.';
                                if ( pole == 1 )
                                        --R;
                                else if ( pole == 2 )
                                        --T;
                                else if ( pole == 3 )
                                        ++T;
                                else
                                        ++R;
                        }
                        else {
                                if  ((hero.x-R) > 0) {
                                        R += 1;
                                }
                                else if ((hero.x-R) < 0) {
                                        R -= 1;
                                }
                                if  ((hero.y-T) > 0) {
                                        T += 1;
                                }
                                else if ((hero.y-T) < 0) {
                                        T -= 1;
                                }
                                string2[current_p->y][current_p->x] = '.';
                        }
			family_p = goodguys.family_p;
			while (family_p != NULL) {
				if ((family_p->x == R) && (family_p->y == T)) {
					R = current_p->x;
					T = current_p->y;
				}
				family_p = family_p->next_p;
			} 
                        hulk_p = badguys.hulk_p;
                        while (hulk_p != NULL) {
                                if ((hulk_p->x == R) && (hulk_p->y == T)) {
                                        R = current_p->x;
                                        T = current_p->y;
                                }
                                hulk_p = hulk_p->next_p;
                        }
                        if ( R < 0 )
                                R = 0;
                        if ( R > 75 )
                                R = 75;
                        if ( T < 0 )
                                T = 0;
                        if ( T > 19 )
                                T = 19;
                        current_p->x = R;
                        current_p->y = T;
                        string2[T][R] = 'G';
                        current_p = current_p->next_p;
                }
        }
}

void movehulks ( void )
{
	int R, T, pole, n, i = 1;
	hulk_t *hulk_p;
	trode_t *trode_p;
	family_t *family_p;
// The hulk gets alotted a random family member to chase after
// until there are no more and then goes after the hero
	if (badguys.hulk_p != NULL) {
		hulk_p = badguys.hulk_p;
		while (hulk_p != NULL) {
			if (hulk_p->family_p == NULL) {
				n = getNumberOfFamily();
				if ( n != 0 ) {
					family_p = goodguys.family_p;
					n = 1+rand()%n;
					for ( i = 1; i < n; i++ ) {
						family_p = family_p->next_p;
					}
					hulk_p->family_p = family_p;
					hulk_p->hero_p = NULL;
				} else if ( n == 0) {
					hulk_p->hero_p = &hero;
					hulk_p->family_p = NULL;
				}
			}	
                        R = hulk_p->x;
                        T = hulk_p->y;
        // 3 chances in 4 that the hulk robots advance towards
        // the family member or hero. 1 in 4 he just advances in random direction
                        if ( rand()%4 == 0 ) {
                                pole = hulk_p->dir = rand()%4 + 1;
                                string2[T][R] = '.';
                                if ( pole == 1 )
                                        --R;
                                else if ( pole == 2 )
                                        --T;
                                else if ( pole == 3 )
                                        ++T;
                                else
                                        ++R;
                        }
                        else {
				if ((hulk_p->family_p != NULL) && (hulk_p->hero_p == NULL)) {
	                                if  ((hulk_p->family_p->x-R) > 0) {
	                                        R += 1;
	                                }
	                                else if ((hulk_p->family_p->x-R) < 0) {
	                                        R -= 1;
	                                }
	                                if  ((hulk_p->family_p->y-T) > 0) {
	                                        T += 1;
	                                }
	                                else if ((hulk_p->family_p->y-T) < 0) {
	                                        T -= 1;
	                                }
	                        }
				else if ((hulk_p->hero_p != NULL) && (hulk_p->family_p == NULL)) {
					if ((hulk_p->hero_p->x-R) > 0) {
						R += 1;
					} else if ((hulk_p->hero_p->x-R) < 0) {
						R -= 1;
					} 
					if ((hulk_p->hero_p->y-T) > 0) {
						T += 1;
					} else if ((hulk_p->hero_p->y-T) < 0) {
						T -= 1;
					}
				}
	                	string2[hulk_p->y][hulk_p->x] = '.';
			}
			trode_p = badguys.trode_p;
			while (trode_p != NULL) {
				if ((trode_p->x == R) && (trode_p->y == T)) {
					R = hulk_p->x;
					T = hulk_p->y;
				}
				trode_p = trode_p->next_p;
			}
	                if ( R < 0 )
                                R = 0;
                        if ( R > 75 )
                                R = 75;
                        if ( T < 0 )
                                T = 0;
                        if ( T > 19 )
                                T = 19;
                        hulk_p->x = R;
                        hulk_p->y = T;
                        string2[T][R] = 'H';
                        hulk_p = hulk_p->next_p;
		}
	}
}

void movegoodguys ( void )
{
	int R, T;
	trode_t *trode_p;
        family_t *current_p;
        current_p = goodguys.family_p;
        while ( current_p != NULL ) {
		R = current_p->x;
		T = current_p->y;
                // 3 in 4 chance walk in same dir, else change dir
                if ( rand()%4!=0 ) {
                        string2[current_p->y][current_p->x] = '.';
                        if ( current_p->dir == 'u' )
                                ++current_p->y;
                        if ( current_p->dir == 'l' )
                                --current_p->x;
                        if ( current_p->dir == 'd' )
                                --current_p->y;
                        if ( current_p->dir == 'r' )
                                ++current_p->x;
                } else {
                        switch ( rand()%4 ) {
                        case 0:
                                current_p->dir = 'd';
                                break;
                        case 1:
                                current_p->dir = 'l';
                                break;
                        case 2:
                                current_p->dir = 'u';
                                break;
                        case 3:
                                current_p->dir = 'r';
                                break;
                        }
                }
		trode_p = badguys.trode_p;
		while (trode_p != NULL) {
			if ((trode_p->x == current_p->x) && (trode_p->y == current_p->y)) {
				current_p->x = R;
				current_p->y = T;
			}
			trode_p = trode_p->next_p;
		}
                if ( current_p->y < 0 )
                        current_p->y = 0;
                if ( current_p->x > 75 )
                        current_p->x = 75;
                if ( current_p->x < 0 )
                        current_p->x = 0;
                if ( current_p->y > 19 )
                        current_p->y = 19;
                string2[current_p->y][current_p->x] = 'M';
                current_p = current_p->next_p;
        }
}

void persisttrodes ( void ) 
{
	trode_t *current_p;
	current_p = badguys.trode_p;
	while ( current_p != NULL ) {
		string2[current_p->y][current_p->x] = 'T';
		current_p = current_p->next_p;
	}
}
