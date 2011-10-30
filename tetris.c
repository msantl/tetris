#define _REENTRANT
#include <pthread.h>
#include "misc.h"

struct shape *s;
pthread_mutex_t blok;


void exit_tetris( void ){
  erase();
  move( startY, startX );
  printw( "Game over!\n" );
  move( startY + 5, startX );
  printw( "You scored %d!\n", score );
  refresh();
  sleep_t( 3. );
  endwin();
  free( s );
  pthread_mutex_destroy( &blok );
  exit( 0 );
}

void *user( void *arg ){
  
  while( 1 ){
    switch( getch() ){
      case 'a':
        pthread_mutex_lock ( &blok );
        if( can_move_left(s) )s->x--;
        draw_area();
        draw_shape( s );
        refresh();
        pthread_mutex_unlock ( &blok );
        break;
      case 'd':
        pthread_mutex_lock ( &blok );
        if( can_move_right(s) )s->x++;
        draw_area();
        draw_shape( s );
        refresh();
        pthread_mutex_unlock ( &blok );
        break;
      case 'w':
        pthread_mutex_lock ( &blok );
        s->rot = ( s->rot + 1 + 4) % 4;
        if( can_rotate(s) ){
          draw_area();
          draw_shape( s );
          refresh();
        } else
          s->rot = ( s->rot - 1 + 4 ) % 4;
        pthread_mutex_unlock ( &blok );
        break;
      case 's':
        pthread_mutex_lock ( &blok );
        s->rot = ( s->rot - 1 + 4 ) % 4;
        if( can_rotate(s) ){
          draw_area();
          draw_shape( s );
          refresh();
        } else
          s->rot = ( s->rot + 1 + 4 ) % 4;
        pthread_mutex_unlock ( &blok );
        break;
      case 'j':
        pthread_mutex_lock ( &blok ); 
        while( can_move_down(s) )s->y++;
        s->y--;
        score += check_area();
        draw_area();
        draw_shape( s );
        refresh();
        pthread_mutex_unlock ( &blok );
        break;
      default:
        break;
    }
  }
  
  exit_tetris();
  return NULL;
}

void *game( void *arg ){
  int temp;
  pthread_mutex_lock ( &blok );
  get_next_shape( s );
  pthread_mutex_unlock ( &blok );
  
  while( 1 ){
    
    pthread_mutex_lock ( &blok );
    
    if( game_over(s)  ){ break; }
    
    if( (temp = can_move_down( s )) == 0 ){
      add_to_area( s );
      get_next_shape( s );
      score += check_area();
    }
    
    draw_area();
    draw_shape( s );
    s->y++;
    
    pthread_mutex_unlock ( &blok );
    
    refresh();
    if( temp == 1 )sleep_t( 0.5 );
  }
  
  exit_tetris();
  return NULL;
}

int main( int argc, char **argv ){
  pthread_t *user_d, *game_d;
  
  user_d = (pthread_t *)malloc( sizeof( *user_d ) );
  game_d = (pthread_t *)malloc( sizeof( *game_d ) );
  s = ( struct shape* )malloc( sizeof(*s) );
  
  srand( (unsigned)time(NULL) );
  
  initscr();
  getmaxyx( stdscr, maxY, maxX );
  curs_set( 0 );
  
  if( maxY < 24 || maxX < 80 ){
    printw( "Your terminal window is too small\n" );  refresh();
    sleep_t( 2. );
    exit_tetris();
    
  } else{
    
    noecho();
    raw();
    
    pthread_mutex_init(&blok, NULL);

    pthread_create( user_d, NULL, user, NULL );
    pthread_create( game_d, NULL, game, NULL );

    pthread_join( *user_d, NULL );
    pthread_join( *game_d, NULL );
    
    pthread_mutex_destroy( &blok );


  }  
  exit_tetris();
  return 0;
}

