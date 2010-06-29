/*
=======================================================
mng_bullets.c
=======================================================
*/

#include "structs.h"
#include "defs.h"
#include "globals.h"
#include "robohack.h"

void managebullets( void ) 
{
	bullet_t *current_p;
	current_p = hero.bullet_p;
	// Keep track of bullet locations
	while ( current_p != NULL ) {
		if ( current_p->dir == 'j' ) {       // left 
			if ( current_p->n > -1 )
				string2[current_p->y][current_p->x] = '-';
			if ( current_p->n > 0 )
				string2[current_p->y][current_p->x+1] = '.';
			if ( current_p->x == 0 ) {
				string2[current_p->y][0] = '*';
				current_p->n = -2;
			}
			if ( current_p->x == -1 ) {
				current_p->dir = 0;
				string2[current_p->y][0] = '.';
			}
			--current_p->x;
			++current_p->n;
		}                                       
		if ( current_p->dir == 'l' ) {       // right
			if (current_p->n > -1)
				string2[current_p->y][current_p->x] = '-';
			if (current_p->n > 0)
				string2[current_p->y][current_p->x-1] = '.';
			if (current_p->x == 75) {
				string2[current_p->y][75] = '*';
				current_p->n = -2;
			}
			if (current_p->x == 76) { 
				current_p->dir = 0;
				string2[current_p->y][75] = '.';
			}
			++current_p->x;
			++current_p->n;
		}
		if ( current_p->dir == 'i' ) {       // up
			if (current_p->n > -1)
				string2[current_p->y][current_p->x] = '|';
			if ( current_p->n > 0 )
				string2[current_p->y-1][current_p->x] = '.';
			if ( current_p->y == 19 ) {
				string2[19][current_p->x] = '*';
				current_p->n = -2;
			}
			if ( current_p->y == 20 ) {
				string2[19][current_p->x] = '.';
				current_p->dir = 0;
			}
			++current_p->y;
			++current_p->n;
		}
		if ( current_p->dir == 'k' ) {       // down
			if (current_p->n > -1)
				string2[current_p->y][current_p->x] = '|';
			if ( current_p->n > 0 )
				string2[current_p->y+1][current_p->x] = '.';
			if ( current_p->y == 0 ) {
				string2[0][current_p->x] = '*';
				current_p->n = -2;
			}
			if ( current_p->y == -1 ) {
				string2[0][current_p->x] = '.';
				current_p->dir = 0;
			}
			--current_p->y;
			++current_p->n;
		}
                if ( current_p->dir == 'b' ) {       // down & left
                        if (current_p->n > -1)
                                string2[current_p->y][current_p->x] = '/';
                        if ( current_p->n > 0 )
                                string2[current_p->y+1][current_p->x+1] = '.';
                        if ( current_p->x < current_p->y ) {
				if ( current_p->x == 0 ) {
	                                string2[current_p->y][current_p->x] = '*';
        	                        current_p->n = -2;
				}
			}
			else if ( current_p->y == 0 ) {
				string2[current_p->y][current_p->x] = '*';
				current_p->n = -2;
                        }
			if ( current_p->n == -1 ) {
				current_p->dir = 0;
				string2[current_p->y+1][current_p->x+1] = '.';
			}
			--current_p->x;
                        --current_p->y;
                        ++current_p->n;
                }
                if ( current_p->dir == 'n' ) {       // down & right
                        if (current_p->n > -1)
                                string2[current_p->y][current_p->x] = '\\';
                        if ( current_p->n > 0 )
                                string2[current_p->y+1][current_p->x-1] = '.';
                        if ((75 - current_p->x) < current_p->y ) {
                                if ((75 - current_p->x) == 0 ) {
                                        string2[current_p->y][current_p->x] = '*';
                                        current_p->n = -2;
                                }
                        }
                        else if ( current_p->y == 0 ) {
                                string2[current_p->y][current_p->x] = '*';
                                current_p->n = -2;
                        }
                        if ( current_p->n == -1 ) {
                                current_p->dir = 0;
                                string2[current_p->y+1][current_p->x-1] = '.';
                        }
                        ++current_p->x;
                        --current_p->y;
                        ++current_p->n;
                }
                if ( current_p->dir == 'y' ) {       // up & left
                        if (current_p->n > -1)
                                string2[current_p->y][current_p->x] = '\\';
                        if ( current_p->n > 0 )
                                string2[current_p->y-1][current_p->x+1] = '.';
                        if ( current_p->x < (19 - current_p->y)) {
                                if ( current_p->x == 0 ) {
                                        string2[current_p->y][current_p->x] = '*';
                                        current_p->n = -2;
                                }
                        }
                        else if ((19 - current_p->y) == 0 ) {
                                string2[current_p->y][current_p->x] = '*';
                                current_p->n = -2;
                        }
                        if ( current_p->n == -1 ) {
                                current_p->dir = 0;
                                string2[current_p->y-1][current_p->x+1] = '.';
                        }
                        --current_p->x;
                        ++current_p->y;
                        ++current_p->n;
                }
                if ( current_p->dir == 'u' ) {       // up & right
                        if (current_p->n > -1)
                                string2[current_p->y][current_p->x] = '/';
                        if ( current_p->n > 0 )
                                string2[current_p->y-1][current_p->x-1] = '.';
                        if ((75 - current_p->x) < (19 - current_p->y)) {
                                if ((75 - current_p->x) == 0 ) {
                                        string2[current_p->y][current_p->x] = '*';
                                        current_p->n = -2;
                                }
                        }
                        else if ((19 - current_p->y) == 0 ) {
                                string2[current_p->y][current_p->x] = '*';
                                current_p->n = -2;
                        }
                        if ( current_p->n == -1 ) {
                                current_p->dir = 0;
                                string2[current_p->y-1][current_p->x-1] = '.';
                        }
                        ++current_p->x;
                        ++current_p->y;
                        ++current_p->n;
                }
		current_p = current_p->next_p;
	}
	eliminatespentammo();
}

void eliminatespentammo ( void )
{
	bullet_t *last_p, *current_p;
	// freeup NULL bullet slots by a sort
	if (hero.bullet_p != NULL) {
		current_p = hero.bullet_p;
		if (current_p->dir == 0) {
			if (current_p->next_p == NULL) {
				free (current_p);
				hero.bullet_p = NULL;
			}
			else if (current_p->next_p != NULL) {
				hero.bullet_p = current_p->next_p;
				free (current_p);
			}
		} 
		else if (current_p->dir != 0) {
			while (current_p != NULL) {
				if (current_p->dir == 0) { 
					if (current_p->next_p == NULL) {
						free (current_p);
						last_p->next_p = NULL;
						current_p = NULL;
					}
					else if (current_p->next_p != NULL) {
						last_p->next_p = current_p->next_p;
						free (current_p);
						current_p = last_p->next_p;
					}
				} else {
					last_p = current_p;
					current_p = current_p->next_p;
				}
			}
		}
	}
}

// and return a pointer to the last linked slot.
// return the first slot if they are all null
bullet_t * findbulletplace ( void )
{
        bullet_t *current_p;
        current_p = hero.bullet_p;
        if ( current_p != NULL ) {
                while ( current_p->next_p != NULL )
                        current_p = current_p->next_p;
        }
        return current_p;
}
	
