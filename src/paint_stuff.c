/*
=======================================================
paint_stuff.c
=======================================================
*/

#include "structs.h"
#include "defs.h"
#include "globals.h"
#include "robohack.h"

void paintgrunts ( int N )
{
        int i;
        grunt_t *new_p, *current_p;
        current_p = (grunt_t *) malloc(sizeof(grunt_t));
        badguys.grunt_p = current_p;
        current_p->x = 10;
        current_p->y = 20;
        current_p->next_p = NULL;
        current_p->dir = 1;
        for (i = 1; i <= (N-1) ; ++i ) {
                new_p = ( grunt_t * ) malloc (sizeof(grunt_t));
                new_p->next_p = NULL;
                current_p->next_p = new_p;
		new_p->y = rand()%19;	
		while ((new_p->y > 6) && (new_p->y < 12))
	                new_p->y = rand()%19;
                new_p->x = rand()%75;
		while ((new_p->x > 26) && (new_p->x < 46))
               		new_p->x = rand()%75;
                new_p->dir = 1;
                current_p = current_p->next_p;
        }
}

void painthulks ( int N )
{
        int i;
        hulk_t *new_p, *current_p;
        current_p = (hulk_t *) malloc(sizeof(hulk_t));
        badguys.hulk_p = current_p;
        current_p->x = 10;
        current_p->y = 20;
        current_p->next_p = NULL;
	current_p->family_p = NULL;
	current_p->hero_p = NULL;
        current_p->dir = 1;
        for (i = 1; i <= (N-1) ; ++i ) {
                new_p = ( hulk_t * ) malloc (sizeof(hulk_t));
                new_p->next_p = NULL;
		new_p->family_p = NULL;
		new_p->hero_p = NULL;
                current_p->next_p = new_p;
                new_p->y = rand()%19;
		while ((new_p->y > 6) && (new_p->y < 12))
	                new_p->y = rand()%19;
                new_p->x = rand()%75;
		while ((new_p->x > 26) && (new_p->x < 46))
               		new_p->x = rand()%75;
                new_p->dir = 1;
                current_p = current_p->next_p;
        }
}

void paintfamilymembers ( int N )
{
        int i;
        family_t *new_p, *current_p;
        current_p = (family_t *) malloc(sizeof(family_t));
        goodguys.family_p = current_p;
        current_p->x = rand()%75;
        current_p->y = rand()%19;
        current_p->next_p = NULL;
        current_p->dir = 1;
        for (i = 1; i <= (N-1) ; ++i ) {
                new_p = ( family_t * ) malloc (sizeof(family_t));
                new_p->next_p = NULL;
                current_p->next_p = new_p;
                new_p->y = rand()%19;
                new_p->x = rand()%75;
                new_p->dir = 1;
                current_p = current_p->next_p;
        }
}

void paintelectrodes ( int N )
{
        int i;
        trode_t *new_p, *current_p;
        current_p = (trode_t *) malloc(sizeof(trode_t));
        badguys.trode_p = current_p;
        current_p->x = rand()%75;
        current_p->y = rand()%19;
	string2[current_p->y][current_p->x] = 'T';
        current_p->next_p = NULL;
        current_p->dir = 1;
        for (i = 1; i <= (N-1) ; ++i ) {
                new_p = ( trode_t * ) malloc (sizeof(trode_t));
                new_p->next_p = NULL;
                current_p->next_p = new_p;
                new_p->y = rand()%19;
		while ((new_p->y > 7) && (new_p->y < 11))
	                new_p->y = rand()%19;
                new_p->x = rand()%75;
		while ((new_p->x > 28) && (new_p->x < 44))
               		new_p->x = rand()%75;
		string2[new_p->y][new_p->x] = 'T';
                new_p->dir = 1;
                current_p = current_p->next_p;
        }

}

void paintbannernew ( void )
{
        register int i;
	int n;
	if (game.frame == 0)
		clear();
	// print yellow border
#ifdef USE_COLORS
        if (has_colors()) attron(COLOR_PAIR(7));
#endif
        for ( i = 1; i <= 76; ++i ) {
                mvprintw (1,i, "_");
                mvprintw (22,i, "-");
        }
        for ( i = 2; i <= 21; i++ ) {
                mvprintw (i, 0, "|");
                mvprintw (i, 77, "|");
        }
	for ( i = 3; i <= 74; ++i ) {
		mvprintw (2,i, "_");
		mvprintw (21,i,"-");
	}
	for ( i = 3; i <= 20; i++ ) {
		mvprintw (i, 2, "|");
		mvprintw (i, 75, "|");
	}
	// print blue stripe
#ifdef USE_COLORS
	if (has_colors()) attron(COLOR_PAIR(6));
#endif
	if ((game.intro > 0) && (game.intro < 73)) {
		mvprintw(1,game.intro,"____");
	} else if ( game.intro == 73 ) {
		mvprintw(1,74, "___");
	} else if ( game.intro == 74 ) {
		mvprintw(1,75, "__");
		mvprintw(2,77, "|\n");
	} else if ( game.intro == 75 ) {
		mvprintw(1,76, "_");
		mvprintw(2,77, "|\n");
		mvprintw(3,77, "|\n");
	} else if (( game.intro > 75 ) && (game.intro < 94)) {
		mvprintw(game.intro-74, 77, "|\n");
		mvprintw(game.intro-73, 77, "|\n");
		mvprintw(game.intro-72, 77, "|\n");
	} else if (game.intro == 94 ) {
		mvprintw(20, 77, "|\n");
		mvprintw(21, 77, "|\n");
		mvprintw(22,76, "-");
	} else if (game.intro == 95 ) {
		mvprintw(21, 77, "|\n");
		mvprintw(22,75, "--");
	} else if (game.intro == 96) {
		mvprintw(22,74, "---");
	} else if ((game.intro > 96) && (game.intro < 170)) {
		mvprintw(22, (170-game.intro), "----");
	} else if (game.intro == 170) {
		mvprintw(22, 1, "---");
	} else if (game.intro == 171) {
		mvprintw(22, 1, "--");
		mvprintw(21, 0, "|");
	} else if (game.intro == 172) {
		mvprintw(22, 1, "-");
		mvprintw(20, 0, "|");
		mvprintw(21, 0, "|");
	} else if ((game.intro > 172) && (game.intro < 190)) {
		mvprintw(192-game.intro, 0, "|");
		mvprintw(193-game.intro, 0, "|");
		mvprintw(194-game.intro, 0, "|");
	} else if (game.intro == 190) {
		mvprintw(2, 0, "|");
		mvprintw(3, 0, "|");	
		mvprintw(4, 0, "|");
		mvprintw(1,1,"_");
	} else if (game.intro == 191) {
		mvprintw(2, 0, "|");
		mvprintw(3, 0, "|");
		mvprintw(1,1,"__");
	} else if (game.intro == 192) {
		mvprintw(2, 0, "|");
		mvprintw(1,1,"___");
	}
	if ((game.intro2 > 0) && (game.intro2 < 17)) {
		mvprintw(21-game.intro2, 75, "|");
		mvprintw(20-game.intro2, 75, "|");
		mvprintw(19-game.intro2, 75, "|");
	} else if (game.intro2 == 17) {
		mvprintw(3,75,"|");
		mvprintw(4,75,"|");
		mvprintw(2,74,"_");
	} else if (game.intro2 == 18) {
		mvprintw(3,75,"|");
		mvprintw(2,73,"__");
	} else if (game.intro2 == 19) {
		mvprintw(2,72,"___");
	} else if ((game.intro2 > 19) && (game.intro2 < 89)) {
		mvprintw(2,91-game.intro2, "____");
	} else if (game.intro2 == 89) {
		mvprintw(2,3,"___");
	} else if (game.intro2 == 90) {
		mvprintw(2,3,"__");
		mvprintw(3,2,"|");
	} else if (game.intro2 == 91) {
		mvprintw(2,3,"_");
		mvprintw(3,2,"|");
		mvprintw(4,2,"|");
	} else if ((game.intro2 > 91) && (game.intro2 < 108)) {
		mvprintw(game.intro2-89,2,"|");
		mvprintw(game.intro2-88,2,"|");
		mvprintw(game.intro2-87,2,"|");
	} else if (game.intro2 == 108) {
		mvprintw(19,2,"|");
		mvprintw(20,2,"|");
		mvprintw(21,3,"-");
	} else if (game.intro2 == 109) {
		mvprintw(20,2,"|");
		mvprintw(21,3,"--");
	} else if (game.intro2 == 110) {
		mvprintw(21,3,"---");
	} else if ((game.intro2 > 110) && (game.intro2 < 180)) {
		mvprintw(21,game.intro2-108,"----");
	} else if (game.intro2 == 180) {
		mvprintw(21,72,"---");
	} else if (game.intro2 == 181) {
		mvprintw(21,73,"--");
		mvprintw(20,75,"|");
	} else if (game.intro2 == 182) {
		mvprintw(21,74,"-");
		mvprintw(19,75,"|");
		mvprintw(20,75,"|");
	}
		
	

#ifdef USE_COLORS
	for (n = 0; n <= 4; n++ ) {
		if (game.frame%25 == n)
			attron(COLOR_PAIR(2));
		else if (game.frame%25 == n + 5)
			attron(COLOR_PAIR(7));
		else if (game.frame%25 == n + 10)
			attron(COLOR_PAIR(1));
		else if (game.frame%25 == n + 15)
			attron(COLOR_PAIR(6));
		else if (game.frame%25 == n + 20)
			attron(COLOR_PAIR(5));
	}
#endif
        mvprintw(  6,  8, "  ______ ______ ______ ______ __  __ ______ ______ __  __");
        mvprintw(  7,  8, " /\\  _  \\\\  __ \\\\  __ \\\\  __ \\\\ \\/\\ \\\\  __ \\\\  __ \\\\ \\/\\ \\");

        mvprintw(  8,  8, "/  \\ \\/\\ \\\\ \\/\\ \\\\ \\/\\ \\\\ \\/\\ \\\\ \\_\\ \\\\ \\/\\ \\\\ \\/\\_\\\\ \\/ /_");
        mvprintw(  9,  8, "\\   \\  _ /_\\ \\ \\ \\\\  __<_\\ \\ \\ \\\\  __ \\\\  __ \\\\ \\/ /_\\  __ \\");
        mvprintw( 10,  8, " \\   \\ \\\\_ \\\\ \\_\\ \\\\ \\/\\ \\\\ \\_\\ \\\\ \\/\\ \\\\ \\/\\ \\\\ \\_\\ \\\\ \\/\\ \\");

        mvprintw( 11,  8, "  \\   \\_\\/\\_\\\\_____\\\\_____\\\\_____\\\\_\\ \\_\\\\_\\ \\_\\\\_____\\\\ \\ \\ \\");
        mvprintw( 12,  8, "   \\  / / / //     //     //     // / / // / / //     // / / /");

        mvprintw( 13,  8, "    \\/_/\\/_//_____//_____//_____//_/\\/_//_/\\/_//_____//_/\\/_/");
	mvprintw(15, 17, "%c 2003 Greg Naughton - gregnaughton@yahoo.com", 169);
	++game.intro;
	++game.intro2;
	if (game.intro > 192) game.intro = 1;
	if (game.intro2 > 182) game.intro2 = 1;
        refresh();
}

// The temporary array scores[] has 11 slots. Ten scores are
// displayed, always.  This way after
// each game one score, the lowest is discarded when the top
// ten are resaved to the highscores.dat file
void paintgameover ( void )
{
        int i = 0, j, tmp, scores[11] = {0,0,0,0,0,0,0,0,0,0,0};
        FILE *cfptr;
        clear();
        if ((cfptr = fopen( "highscores.dat", "r")) == NULL) {
                printf( "highscore.dat could not be opened\n");
                printf( "You probably need root privelidges\n");
        }
        else {
                while ( !feof(cfptr) )  {
                        fscanf(cfptr, "%d", &scores[i++]);
                }
                fclose( cfptr );
        }
        scores[10] = game.score;
        //quick bubble sort
        for ( j = 1; j <= 10; j++ ) {
                for ( i = 0; i <= 9; i++ ) {
                        if (scores[i] < scores[i+1]) {
                                tmp = scores[i+1];
                                scores[i+1] = scores[i];
                                scores[i] = tmp;
                        }
                }
        }
        if ((cfptr = fopen( "highscores.dat", "w")) == NULL) {
                printf( "highscore.dat could not be opened\n");
                printf( "You probably need root privelidges\n");
        }
        else {
                rewind( cfptr );
                for ( i = 0; i <= 9; i++ ) {
                        fprintf(cfptr, "%d\n", scores[i]);
                }
        }
        fclose (cfptr);

#ifdef USE_COLORS
        attron(COLOR_PAIR(6));
#endif
        for ( i = 0; i <= 9; i++ ) {
                mvprintw( (6+i), 40, "%d", scores[i]);
        }
        mvprintw (  8, 20, "GAME OVER" );
        mvprintw ( 10, 20, "Level: %d", game.level);
        mvprintw ( 11, 20, "Score: %d", game.score);
        mvprintw (  4, 40, "HIGH SCORES!");
        if ( game.score == scores[0] ) {
                mvprintw ( 17, 20, "Congratulations. You got the high Score!");
		game.highscore = 1;
		attron(COLOR_PAIR(4));
		mvprintw ( 6, 40, "%d", scores[0]);
       		mvprintw ( 11, 20, "Score: %d", game.score);
	}  
        tmp = game.frame;
	hero.dir = getch();
        i = 0;
        while (i == 0) {
                if ((game.frame - tmp) > 120 )
                        ++i;
        }
	while ((hero.dir != 'q') && (hero.dir != ' '))
		hero.dir = getch();
	if (hero.dir == ' ')
		game.state = STATE_INTRO;
	else if ((hero.dir == 'q') || (hero.dir == 27)) {
		cleanup();
		endwin();
		if ((cfptr = fopen(".rh_debug_log", "a")) != NULL) {
			fprintf(cfptr, "End Reached: in gameover\n");
		}
		fclose(cfptr);
		exit(0);
	}
	refresh();
}

void paintempty ( trode_t *trode_p, bullet_t *bullet_p ) 
{
//	mvprintw ( 23, 40, "T:%2d %2d, B:%2d %2d", trode_p->x, trode_p->y, bullet_p->x, bullet_p->y);
	string2[trode_p->y][trode_p->x] = '.';
	if ( bullet_p->dir == 'i' ) 
		string2[bullet_p->y-1][bullet_p->x] = '.';
	if ( bullet_p->dir == 'k' ) 
		string2[bullet_p->y+1][bullet_p->x] = '.';
	if ( bullet_p->dir == 'j' ) 
		string2[bullet_p->y][bullet_p->x+1] = '.';
	if ( bullet_p->dir == 'l' ) 
		string2[bullet_p->y][bullet_p->x-1] = '.';
	if ( bullet_p->dir == 'b' ) 
		string2[bullet_p->y+1][bullet_p->x+1] = '.';
	if ( bullet_p->dir == 'n' ) 
		string2[bullet_p->y+1][bullet_p->x-1] = '.';
	if ( bullet_p->dir == 'y' ) 
		string2[bullet_p->y-1][bullet_p->x+1] = '.';
	if ( bullet_p->dir == 'u' ) 
		string2[bullet_p->y-1][bullet_p->x-1] = '.';
}
