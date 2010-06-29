/* 
======================================================
mng_slots.c - Manage Character Slots
======================================================
*/

// This function takes care of memory by finding the used
// slots and then freeing them and reorganizing the linked list

#include "structs.h"
#include "defs.h"
#include "globals.h"
#include "robohack.h"

// called by trackinteractions
void eliminatebadguys ( void )
{
        grunt_t *last_p, *current_p;
        // freeup NULL badguy slots by a sort
        if (badguys.grunt_p != NULL) {
                current_p = badguys.grunt_p;
                if (current_p->dir == 0) {
                        if (current_p->next_p == NULL) {
                                free (current_p);
                                badguys.grunt_p = NULL;
                        }
                        else if (current_p->next_p != NULL) {
                                badguys.grunt_p = current_p->next_p;
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

int getNumberOfGrunts (void)
{
        int i = 0;
        grunt_t *grunt_p;
        grunt_p = badguys.grunt_p;
        while (grunt_p != NULL) {
                ++i;
                grunt_p = grunt_p->next_p;
        }
        return i;
}

int getNumberOfHulks (void)
{
        int i = 0;
        hulk_t *hulk_p;
        hulk_p = badguys.hulk_p;
        while (hulk_p != NULL) {
                ++i;
                hulk_p = hulk_p->next_p;
        }
        return i;
}

int getNumberOfFamily (void)
{
	int i = 0;
	family_t *family_p;
	family_p = goodguys.family_p;
	while (family_p != NULL) {
		++i;
		family_p = family_p->next_p;
	}
	return i;
}

void removefamilymember ( void )
{
        family_t *last_p, *current_p;
        // freeup NULL goodguy slots by a sort
        if (goodguys.family_p != NULL) {
                current_p = goodguys.family_p;
                if (current_p->dir == 0) {
		// release pointer
                        if (current_p->next_p == NULL) {
                                free (current_p);
                                goodguys.family_p = NULL;
                        }
                        else if (current_p->next_p != NULL) {
                                goodguys.family_p = current_p->next_p;
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

void removetrode ( void )
{
        trode_t *last_p, *current_p;
        // freeup NULL trode slots by a sort
        if (badguys.trode_p != NULL) {
                current_p = badguys.trode_p;
                if (current_p->dir == 0) {
                        if (current_p->next_p == NULL) {
                                free (current_p);
                                badguys.trode_p = NULL;
                        }
                        else if (current_p->next_p != NULL) {
                                badguys.trode_p = current_p->next_p;
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


