/* 
=======================================================
cleanup.c
=======================================================
*/

#include "structs.h"
#include "defs.h"
#include "globals.h"
#include "robohack.h"

// recursive call sets.  cleanup is called and cleanup calls all its
// childs.  The childs recursively call themselves until they are finished
void cleanup ( void )
{
        cleanupgrunts ( badguys.grunt_p );
        cleanupexplosions ( game.blammo_p );
        cleanupbullets ( hero.bullet_p );
        cleanupfamily ( goodguys.family_p );
	cleanuptrodes ( badguys.trode_p );
	cleanuphulks ( badguys.hulk_p );
	badguys.grunt_p = NULL;
	badguys.trode_p = NULL;
	badguys.hulk_p = NULL;
	game.blammo_p = NULL;
	hero.bullet_p = NULL;
	goodguys.family_p = NULL;
}

void cleanupgrunts ( grunt_t *grunt_p )
{
        if (grunt_p != NULL) {
                cleanupgrunts(grunt_p->next_p);
                grunt_p->next_p = NULL;
                free (grunt_p);
        }
}

void cleanupexplosions ( explosion_t *blammo_p )
{
        if (blammo_p != NULL) {
                cleanupexplosions(blammo_p->next_p);
                blammo_p->next_p = NULL;
                free (blammo_p);
        }
}

void cleanupbullets ( bullet_t *bullet_p )
{
        if (bullet_p != NULL) {
                cleanupbullets (bullet_p->next_p);
                bullet_p->next_p = NULL;
                free (bullet_p);
        }
}

void cleanupfamily ( family_t *family_p )
{
        if (family_p != NULL) {
                cleanupfamily (family_p->next_p);
                family_p->next_p = NULL;
                free (family_p);
        }
}

void cleanuptrodes ( trode_t *trode_p )
{
	if (trode_p != NULL) {
		cleanuptrodes (trode_p->next_p);
		trode_p->next_p = NULL;
		free (trode_p);
	}
}

void cleanuphulks ( hulk_t *hulk_p )
{
	if (hulk_p != NULL) {
		cleanuphulks (hulk_p->next_p);
		hulk_p->next_p = NULL;
		free (hulk_p);
	}
}
