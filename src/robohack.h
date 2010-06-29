/* 
=======================================================
robohack.h
=======================================================
*/

// in robohack.c
void handleTimer ( int );	// this is called FPS/s by the kernel
void arrayempty ( char [20][76] );// Used to initialize the array[][]'
void printtic ( char [20][76] );	// array handler. stores all x,y inf
void checkSpeed ( int, int ); // maintains speed of badguys in 1 turn 

// in cleanup.c
void cleanup ( void );
void cleanupgrunts ( grunt_t * );
void cleanupbullets ( bullet_t * );
void cleanupexplosions ( explosion_t * );
void cleanupfamily ( family_t * );
void cleanuptrodes ( trode_t * );
void cleanuphulks ( hulk_t * );

// in handle_movement.c
void movegoodguys ( void );
void movegrunts ( void );
void movehulks ( void );
void movehero ( void );
void persisttrodes ( void );

// in mng_bullets.c
void managebullets ( void );
void eliminatespentammo ( void );
extern bullet_t * findbulletplace ( void );

//in mng_explosions.c
void initiateexplosion ( int, int );
void manageexplosions ( void );
void terminateexplosions ( void );

//in mng_slots.c
void eliminatebadguys ( void );
extern int getNumberOfGrunts ( void );
extern int getNumberOfFamily ( void );
extern int getNumberOfHulks ( void );
void removefamilymember ( void );

//in paint_stuff.c
void paintgrunts ( int );
void painthulks ( int );
void paintfamilymembers ( int );
void paintelectrodes ( int );
void paintbannernew ( void );
void paintgameover ( void );
void paintempty ( trode_t *, bullet_t *);

//in trk_interact.c
void trackinteractions ( void );
void manageplayer ( void );
void removetrode ( void );

//in initialize.c
void initialize ( void );
