/* 
=======================================================
trk_interact.c - Track interactions
=======================================================
*/

#include "structs.h"
#include "defs.h"
#include "globals.h"
#include "robohack.h"

// called by handleTimers in robohack.c
void trackinteractions ( void )
{
        bullet_t *bullet_p;
        grunt_t *grunt_p;
	trode_t *trode_p;
	family_t *family_p;
	hulk_t *hulk_p;

	// Detect if a bullet hits a grunt robot
        bullet_p = hero.bullet_p;
        grunt_p = badguys.grunt_p;
        while (grunt_p != NULL) {
                while (bullet_p != NULL) {
                        if ((grunt_p->x == bullet_p->x) && (grunt_p->y == bullet_p->y)) {
                                game.score += 100;
                                bullet_p->dir = 0;
                                initiateexplosion(grunt_p->x, grunt_p->y);
                                grunt_p->dir = 0;
                        }
                        bullet_p = bullet_p->next_p;
                }
                bullet_p = hero.bullet_p;
                grunt_p = grunt_p->next_p;
        }
        manageplayer();

	// Detect if bullet hits a hulk
        bullet_p = hero.bullet_p;
	hulk_p = badguys.hulk_p;
	while (hulk_p != NULL) {
		while (bullet_p != NULL) {
                        if ((hulk_p->x == bullet_p->x) && (hulk_p->y == bullet_p->y)) {
				// Cover up bullet
				if (bullet_p->dir == 'j') 
					string2[bullet_p->y][bullet_p->x+1] = '.';
				if (bullet_p->dir == 'l')
					string2[bullet_p->y][bullet_p->x-1] = '.';
				if (bullet_p->dir == 'k')
					string2[bullet_p->y+1][bullet_p->x] = '.';
				if (bullet_p->dir == 'i')
					string2[bullet_p->y-1][bullet_p->x] = '.';
				if (bullet_p->dir == 'b')
					string2[bullet_p->y+1][bullet_p->x+1] = '.';
				if (bullet_p->dir == 'n')
					string2[bullet_p->y+1][bullet_p->x-1] = '.';
				if (bullet_p->dir == 'y')
					string2[bullet_p->y-1][bullet_p->x+1] = '.';
				if (bullet_p->dir == 'u')
					string2[bullet_p->y-1][bullet_p->x-1] = '.';
				bullet_p->dir = 0;
			}	
			bullet_p = bullet_p->next_p;
		}
		bullet_p = hero.bullet_p;
		hulk_p = hulk_p->next_p;
	}

	// detect if grunt robot hits a trode
	grunt_p = badguys.grunt_p;
	trode_p = badguys.trode_p;
	hulk_p = badguys.hulk_p;
	while ( grunt_p != NULL ) {
		while ( trode_p != NULL ) {
			if ((grunt_p->x == trode_p->x) && (grunt_p->y == trode_p->y)) {
				initiateexplosion(grunt_p->x, grunt_p->y);
				string2[grunt_p->y][grunt_p->x] = '.';
				grunt_p->dir = 0;
			}
			trode_p = trode_p->next_p;
		}
		trode_p = badguys.trode_p;
		grunt_p = grunt_p->next_p;
	}
        eliminatebadguys();
        manageexplosions();

	// detect if bullet hits a trode
        bullet_p = hero.bullet_p;
	trode_p = badguys.trode_p;
	while ( trode_p != NULL ) {
		while (bullet_p != NULL ) {
			if ((trode_p->x == bullet_p->x) && (trode_p->y == bullet_p->y)) {
				trode_p->dir = 0;
				paintempty( trode_p, bullet_p );
				bullet_p->dir = 0;
			}
			bullet_p = bullet_p->next_p;
		}
		bullet_p = hero.bullet_p;
		trode_p = trode_p->next_p;
	}
	removetrode();	
	//bullets are removed automatically by the function call:
	//eliminatespentammo from managebullets from handleTimers respectively

	// detect if hulk captures family member
	hulk_p = badguys.hulk_p;
	family_p = goodguys.family_p;
	while ( hulk_p != NULL ) {
		while (family_p != NULL) {
			if ((hulk_p->x == family_p->x) && (hulk_p->y == family_p->y)) {
				string2[family_p->y][family_p->x] = '.';
				family_p->dir = 0;
				hulk_p->family_p = NULL;
			}
			family_p = family_p->next_p;
		}
		hulk_p = hulk_p->next_p;
		family_p = goodguys.family_p;
	}
}
	
// called by trackinteractions
void manageplayer ( void )
{
        int n;
        grunt_t *grunt_p;
        family_t *current_p;
	trode_t *trode_p;
        hulk_t *hulk_p;
	
	grunt_p = badguys.grunt_p;
	// Detect if the player touches a grunt robot
	// also give the hero 1.5 seconds amnesty at the start of the turn
        while (grunt_p != NULL) {
                if ((game.state != STATE_LOSELIFE) && ((game.frame - game.tmp) >= 120)) {
                        if ((grunt_p->x == hero.x) && (grunt_p->y == hero.y)) {
                                game.state = STATE_LOSELIFE;
				initiateexplosion(hero.x, hero.y);
				system("echo gruntloselife >> .rh_debug_log");
                                --game.lives;
                        }
                }
                grunt_p = grunt_p->next_p;
        }
	// checks for and awards free guys
        game.lock = ON;
        for ( n = game.free_guy_num; n <= 200; n++ ) {
                if (game.score >= n*25000) {
                        if (game.i == 0) {
                                ++game.lives;
                                system ("echo freeguy >> .rh_debug_log");
                                // incrementing game.i turns on the FreeGuy sign
				++game.i;
                                ++game.free_guy_num;
                        }
                }
        }
        game.lock = OFF;
	// check to see if he picks up family members
        current_p = goodguys.family_p;
        hulk_p = badguys.hulk_p;
        while ( current_p != NULL ) {
                if ((current_p->x == hero.x) && (current_p->y == hero.y)) {
                        if (game.k == 0) {
                                ++game.k;
                                current_p->dir = 0;
                                if (game.fam_num == 6) --game.fam_num;
                                game.score += (1000*game.fam_num);
                                if (game.fam_num < 6 )
                                        ++game.fam_num;
                        }
                        while (hulk_p != NULL) {
                                if (hulk_p->family_p == current_p) 
                                        hulk_p->family_p = NULL;
                                hulk_p = hulk_p->next_p;
                        }
                }
                current_p = current_p->next_p;
        }
        removefamilymember();
	// checks to see if hero runs into a trode
	trode_p = badguys.trode_p;
	while ( trode_p != NULL ) {
		if (game.state != STATE_LOSELIFE) {
			if ((trode_p->x == hero.x) && (trode_p->y == hero.y)) {
				initiateexplosion(hero.x, hero.y);
				game.state = STATE_LOSELIFE;
				system("echo trodeloselife >> .rh_debug_log");
				--game.lives;
			}
		}
		trode_p = trode_p->next_p;
	}
	// checks to see if hero ran into hulk
	hulk_p = badguys.hulk_p;
	while ( hulk_p != NULL ) {
		if (game.state != STATE_LOSELIFE) {
			if ((hulk_p->x == hero.x) && (hulk_p->y == hero.y)) {
				game.state = STATE_LOSELIFE;
				system("echo HULKloselife >> .rh_debug_log");
				--game.lives;
			}
		}
		hulk_p = hulk_p->next_p;
	}
}

