#ifndef MISC
#define MISC
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#define startX (maxX/2 - areaX/2)
#define startY 3
#define areaX 12
#define areaY 21
#define offX 2
#define offY 0

int maxX, maxY, score;

struct shape{
  int x, y;
  int id, rot;
  };


void sleep_t( double t );

int get_random( int lo, int hi );

int can_rotate( struct shape *s );

int can_move_down( struct shape *s );

int can_move_left( struct shape *s );

int can_move_right( struct shape *s );

void add_to_area( struct shape *s );

int game_over(  struct shape *s  );

int check_area( void );

void draw_shape( struct shape *s );

void draw_area( void );

void get_next_shape( struct shape* s );
#endif
