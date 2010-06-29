/*
=======================================================
robohack.c
=======================================================
*/

#include "structs.h"
#include "defs.h"
#include "globals.h"
#include "robohack.h"

int main (int argc, char **argv) {
	
	int n, i, tmp;
	bullet_t *new_p, *open_p;
	FILE *cfptr;
	// begin curses mode 
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

#ifdef USE_COLORS
	if (has_colors()) {
		start_color();
		init_pair(0, COLOR_BLACK, COLOR_BLACK);
		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLACK);
		init_pair(3, COLOR_CYAN, COLOR_BLACK);
		init_pair(4, COLOR_WHITE, COLOR_BLACK);
		init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(6, COLOR_BLUE, COLOR_BLACK);
		init_pair(7, COLOR_YELLOW, COLOR_BLACK);
		init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
		init_pair(9, COLOR_BLUE, COLOR_BLUE);
		init_pair(10, COLOR_CYAN, COLOR_CYAN);
		init_pair(11, COLOR_WHITE, COLOR_WHITE);
		init_pair(12, COLOR_MAGENTA, COLOR_MAGENTA);
		init_pair(13, COLOR_BLACK, COLOR_YELLOW);
	}
#endif
        // hide cursor
        curs_set(0);
	initialize();
	game.state = STATE_INTRO;	
	system ("echo startrobohack >> .rh_debug_log");
	system ("date >> .rh_debug_log");

        // set up realtime interrupt timer and signals
        game.myTimer.it_value.tv_sec = 0;
        game.myTimer.it_value.tv_usec = 1000000 / FPS;
        game.myTimer.it_interval.tv_sec = 0;
        game.myTimer.it_interval.tv_usec = 1000000 / FPS;
        setitimer(ITIMER_REAL, &game.myTimer, NULL);
        signal(SIGALRM, handleTimer);

	// the hero's loop which takes all of the heros input
	for (;;) {
		if (game.state == STATE_PLAY) {
			game.lock = OFF;
			if ((game.state != STATE_NEXTLEVEL) && (game.state!=STATE_LOSELIFE)) {
				hero.dir = getch(); 
				// MOVE
				if ((hero.dir == 's')||(hero.dir == 'd')||
					(hero.dir == 'f')||(hero.dir == 'e')) {
					++hero.moves;
				}
				// allocate memory for a bullet and link it
				else if ((hero.dir == 'j')||(hero.dir == 'k')||
					(hero.dir == 'l')||(hero.dir == 'i')||
					(hero.dir == 'b')||(hero.dir == 'n')||
					(hero.dir == 'y')||(hero.dir == 'u')) {
					new_p = (bullet_t *) malloc(sizeof(bullet_t));
					new_p->next_p = NULL;
					open_p = findbulletplace();
					if ( open_p == NULL ) 
						hero.bullet_p = new_p;
					else 
						open_p->next_p = new_p;
					if ( hero.dir == 'j' ) {
						new_p->x = hero.x - 1;
						new_p->y = hero.y;
					} else if ( hero.dir == 'k' ) {
						new_p->x = hero.x;
						new_p->y = hero.y - 1;
					} else if ( hero.dir == 'l' ) {
						new_p->x = hero.x + 1;
						new_p->y = hero.y;
					} else if ( hero.dir == 'i' ) {
						new_p->x = hero.x;
						new_p->y = hero.y + 1;
		                        } else if ( hero.dir == 'b' ) {
		                                new_p->x = hero.x - 1;
		                                new_p->y = hero.y - 1;
		                        } else if ( hero.dir == 'n' ) {
		                                new_p->x = hero.x + 1;
		                                new_p->y = hero.y - 1;
		                        } else if ( hero.dir == 'y' ) {
		                                new_p->x = hero.x - 1;
		                                new_p->y = hero.y + 1;
		                        } else if ( hero.dir == 'u' ) {
		                                new_p->x = hero.x + 1;
		                                new_p->y = hero.y + 1;
					}  
					new_p->dir = hero.dir;
					new_p->n = 0;
				}
                                else if ((hero.dir == 'q') || (hero.dir == 27 )) {
                                        game.lock = ON;
					cleanup();
					endwin();
				        if ((cfptr = fopen( ".rh_debug_log", "a")) != NULL) {
				                fprintf ( cfptr, "End reached in PLAY\n" );
				        }
				        fclose(cfptr);
					exit(0);
                                }
			} 
			// check for end of round
		        if (getNumberOfGrunts() == 0) {
		                game.state = STATE_NEXTLEVEL;
		                game.lock = ON;
		                ++game.level;
		        }
		}
		// Handle game state
        	else if ( game.state == STATE_INTRO ) {
			system("echo newgame >> .rh_debug_log");
			clear();
			initialize();
			arrayempty( string2 );
			game.lock = ON;
			hero.dir = getch();
			while((hero.dir != ' ') && (hero.dir != 10) &&
				(hero.dir != 'q') && (hero.dir != 27))
				hero.dir = getch();
			if ((hero.dir == 'q') || (hero.dir == 27 )) {
				game.lock = ON;
				cleanup();
				endwin();
				if ((cfptr = fopen( ".rh_debug_log", "a")) != NULL) {
					fprintf ( cfptr, "End reached in INTRO\n" );
				}
				fclose(cfptr);
				exit(0);
			} else {
       		                game.state = STATE_WAIT;
				game.n = 0;
	       	                paintgrunts( 14 );
				paintfamilymembers( 3 );
				paintelectrodes( 16 );
	       	        }
		}
		// a pause before repainting
		else if ( game.state == STATE_WAIT ) {
			if ( game.n == 0 )  {
				game.tmp = game.frame;
				++game.n;
			}
			if ((game.lives != 0) && ( (game.frame - game.tmp) >= 30)) {
				arrayempty ( string2 );
				n = getNumberOfGrunts();
				cleanupgrunts(badguys.grunt_p);
				paintgrunts (n);
				n = getNumberOfHulks();
				cleanuphulks(badguys.hulk_p);
				painthulks (n);
				n = getNumberOfFamily();
				cleanupfamily(goodguys.family_p);
				paintfamilymembers(n+((rand()%2)*(1+rand()%3)));
				hero.x = HERO_START_X;
				hero.y = HERO_START_Y;
				game.state = STATE_PLAY;	
				game.n = 0;
			}
		}
		else if ( game.state == STATE_LOSELIFE ) {
			game.tight = 0;
			game.timer = 1;
//			game.lock = ON;
			game.fam_num = 1;
			if ( game.lives == 0 ) {
				game.state = STATE_GAMEOVER; 
			} else if ( game.lives >= 0 ) {
				game.state = STATE_WAIT;
			}
			fflush(stdin);
		}	
		else if ( game.state == STATE_GAMEOVER ) {
			game.lock = ON;
			tmp = game.frame;
			i = 0;
			while ( i == 0 ) {
				if ((game.frame-tmp) >= 120) 
					++i;
			}
			paintgameover();	
		}
		else if ( game.state == STATE_NEXTLEVEL ) {
			game.lock = ON;
                        if ( game.n == 0 )  {
                                game.tmp = game.frame;
                                ++game.n;
                        }
                        if ((game.lives != 0) && ((game.frame - game.tmp) >= 30)) {
				arrayempty( string2 );
				game.fam_num = 1;
				paintgrunts( 22 + rand()%10 );
				paintfamilymembers( 10 - (rand()%8) );
				cleanuphulks(badguys.hulk_p);
				painthulks( 2 + rand()%4);
				cleanuptrodes(badguys.trode_p);
				paintelectrodes(20 + rand()%16);
				// speeds up the badguys; inverse relationship
				if ((game.level > 1) && (game.level <= 4)) {
					game.faster -= 2; 
				} // 0,-2,-4,-6,-7,-8,-9,-10,-11,-12 
				else if ((game.level > 4) && (game.level <= 10))
					--game.faster;
				hero.x = HERO_START_X;
				hero.y = HERO_START_Y;
				game.state = STATE_PLAY;
				game.n = 0;	
				game.timer = 1;
				game.tight = 0;
			}
		} 
                else if (hero.dir == 'q') {
                        game.lock = ON;
			cleanup();
			endwin();    
			exit(0);
                }
	}
/*        if ((cfptr = fopen( ".rh_debug_log", "a")) != NULL) {
		fprintf ( cfptr, ": End has been reached\n" );
	} 
	fclose(cfptr); 
*/
	// This is never reached
	return 0;
} 
// This func is called FPS/s.  It farms out tasks to other functions.
// It should only contain other function calls and the conditions under
// which they should be called.
void handleTimer(int signal) 
{
	if ( game.lock == OFF ) {
		game.lock = ON;
		checkSpeed (game.timer, game.level);
		if (game.frame%(GRUNT_SPEED + game.faster + game.tight) == 1) {
			movegrunts(); 
		}
		if ( game.frame%FAMILY_SPEED == 1 )
			movegoodguys();
		if ( game.frame%HULK_SPEED == 1 )
			movehulks();
		movehero();
		persisttrodes();
		managebullets();
		trackinteractions();
		if (game.state == STATE_PLAY ) {
			printtic ( string2 );
		}
		game.lock = OFF;
	}
	if (game.state == STATE_INTRO)
		paintbannernew();
	if (game.state == STATE_GAMEOVER) {
		if (game.highscore == 1) {
			if ((game.frame%10 >= 0) && (game.frame%10 < 5))  {
				attron(COLOR_PAIR(4));
			} else {
				attron(COLOR_PAIR(6));
			}
	                mvprintw ( 17, 20, "Congratulations. You got the high Score!");
			refresh();
		} else {
			game.highscore = 0;
		}
	} 
	++game.timer;
	++game.frame;
} 


void arrayempty ( char a[20][76] )
{
	int i, j;
#ifdef USE_COLORS
        if (has_colors()) attron(COLOR_PAIR(4));
#endif
	for ( i = 0; i <= 19; i++ ) {
		for ( j = 0; j <= 75; j++ ) {
			a[i][j] = '.';
		}
	}
}


void printtic ( char b[20][76] )
{
	int i = 0, j = 0, n;
	mvprintw(0,0,"\n");
	mvprintw(1,0," ");
#ifdef USE_COLORS
        if (has_colors()) attron(COLOR_PAIR(7));
#endif
	for ( i = 0; i <= 75; ++i )
		printw("_");
	printw("\n");

	for ( i = 0; i <= 19; i++ ) {
		printw("|");
		for ( j = 0; j <= 75; j++ ) {
#ifdef USE_COLORS
			if (b[19-i][j] == '@') {
				attron(COLOR_PAIR(4));
			} else if (b[19-i][j] == 'G') {
				attron(COLOR_PAIR(2));
			} else if (b[19-i][j] == '-') {
				attron(COLOR_PAIR(3));
			} else if (b[19-i][j] == '\\') {
				attron(COLOR_PAIR(3));
			} else if (b[19-i][j] == '/') {
				attron(COLOR_PAIR(3));
			} else if (b[19-i][j] == '|') {
				attron(COLOR_PAIR(3));
			} else if (b[19-i][j] == 'M') {
				attron(COLOR_PAIR(1));
			} else if (b[19-i][j] == 'H') {
				attron(COLOR_PAIR(13));
			} else if (b[19-i][j] == 'T') {
				for (n = 0; n <= 7; n++) {
					if (game.frame%24 == n) 
						attron(COLOR_PAIR(9));
					else if (game.frame%24 == 8+n) 
						attron(COLOR_PAIR(10));
					else if (game.frame%24 == 16+n) 
						attron(COLOR_PAIR(12));
				}
			} else 
				attron(COLOR_PAIR(4));
#endif 	
			printw ("%c",  b[19-i][j] );
		}
#ifdef USE_COLORS
		attron(COLOR_PAIR(7));
#endif
		printw ("|\n");
	}
	printw(" ");
	for ( i = 0; i <= 75; ++i )
		printw ("-");
	printw("\n");
#ifdef USE_COLORS
	attron(COLOR_PAIR(4));
#endif
	mvprintw ( 23, 0, "q to quit" );
	mvprintw ( 0, 10, "%7d" , game.score );
	mvprintw ( 23, 50, "h%8x,f%8x", badguys.hulk_p->hero_p, badguys.hulk_p->family_p);
//	mvprintw ( 23, 70, "L:%2d %2.0f", game.level, (float) game.timer/60 );
//	mvprintw ( 23, 64, "S:%2d", GRUNT_SPEED + game.tight + game.faster );
#ifdef USE_COLORS
	attron(COLOR_PAIR(6));
#endif
	for ( j = i = 2; i <= game.lives; i++ ) {
		mvprintw( 0 , 17 + j, "@ ");
		j += 2;
	}
	// game.i = 1, sets tmp2, prints 'Bonus Life' for 4s; then off
	if ( game.i == 1 ) {
		if (game.j == 0) {
			game.tmp2 = game.frame;
			++game.j;
			mvprintw ( 23, 20, "Bonus Life");
		} 
	}
	if ( (game.frame - game.tmp2) >= 240 ) {
		mvprintw ( 23, 20, "          ");
		game.j = game.i = 0;
	} 
#ifdef USE_COLORS
	attron(COLOR_PAIR(1));
#endif
	if ( game.k == 1 ) {
		game.tmp3 = game.frame;
		mvprintw( 23, 33, "%d", 1000*(game.fam_num - 1) );
	}
	if ( (game.frame - game.tmp3) >= 180 ) {
		mvprintw ( 23, 33, "    ");
	}
	refresh();
}

void checkSpeed ( int timer, int level )
{
	if (timer == 600 ) {
		if (level <= 4) 
			game.tight -= (9 + game.faster);
		else if ( level == 5 ) game.tight -= 2;
		else if ((level > 5) && (level <= 8))
			game.tight -= 1;
	}
	// 9, 9, 9, 9, 9, 8, 8, 7, 7, 6
	if (timer == 1200 ) {
		if (level <= 5) 
			game.tight -= 3;
		else if ((level == 6) || (level == 7))
			game.tight -= 2;
		else if (level > 8) 
			--game.tight;
	}// 6, 6, 6, 6, 6, 6, 6, 6, 6, 5.......
	if ((timer == 1500 ) && (level > 3))
		--game.tight;
	if (timer == 1800 ) 
		--game.tight;
	if (timer == 1980 )
		--game.tight;
	if (timer == 2100 )
		--game.tight;
	if (timer == 2160 )
		--game.tight;
}
