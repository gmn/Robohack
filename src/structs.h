/*
=======================================================
structs.h - struct definitions
=======================================================
*/

typedef struct BULLET {
	int x, y;           // bullet location
	int n;
	int dir;            // direction traveling
	struct BULLET *next_p;
} bullet_t;

/* There are Grunt, Hulk, Spheroid, Quark, Tank, Brain, & Enforcer
   Robotrons in the real game */
typedef struct GRUNT {
	int x, y;
	int dir;
	struct GRUNT *next_p;
} grunt_t;

typedef struct TRODE {
	int x, y;
	int dir;
	struct TRODE *next_p;
} trode_t;

typedef struct HULK {
	int x, y;
	int dir;
	struct HERO *hero_p;
	struct FAMILY *family_p;
	struct HULK *next_p;
} hulk_t;

typedef struct EXPLOSION {
	int x, y;
	int n;
	struct EXPLOSION *next_p;
} explosion_t;

typedef struct FAMILY {
	int x, y;
	int n;
	int dir;
	struct FAMILY *next_p;
} family_t;

extern bullet_t * findbulletplace ( void );

/* map- who calls what
timers- -movehero
      \
	-managebullets-----------eliminatespentammo
	|
	-trackinteractions-------eliminatebadguys
			   \
			    \----initiateexplosion
			     \
			      \--manageexplosions------terminateexplosion
			       \
				-managehero
*/	
	
/* map - game states

INTRO(lock ON)->WAIT--------------->PLAY(lock OFF) --->NEXTLEVEL(lock ON) 
                ^                ^   |                 |
		|                |___v_________________v
TIMERS--------->LOSELIFE(lock ON)-->GAMEOVER(lock ON)

*/

