#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "tetris_body.h"

static char blockPattern[PATNUM][PATSIZEH][PATSIZEW] =
  { 
    {{'#','#',' '}, {'#','#',' '}, {' ',' ',' '}}, 
    
    {{' ','#',' '}, {' ','#',' '}, {' ','#',' '}}, 
    {{' ',' ',' '}, {'#','#','#'}, {' ',' ',' '}}, 

    {{' ','#',' '}, {'#','#',' '}, {'#',' ',' '}}, 
    {{'#','#',' '}, {' ','#','#'}, {' ',' ',' '}},

    {{'#',' ',' '}, {'#','#',' '}, {' ','#',' '}},
    {{' ','#','#'}, {'#','#',' '}, {' ',' ',' '}},

    {{'#',' ',' '}, {'#','#','#'}, {' ',' ',' '}},
    {{'#','#',' '}, {'#',' ',' '}, {'#',' ',' '}},
    {{'#','#','#'}, {' ',' ','#'}, {' ',' ',' '}},
    {{' ','#',' '}, {' ','#',' '}, {'#','#',' '}},

    {{' ',' ','#'}, {'#','#','#'}, {' ',' ',' '}},
    {{'#',' ',' '}, {'#',' ',' '}, {'#','#',' '}},
    {{'#','#','#'}, {'#',' ',' '}, {' ',' ',' '}},
    {{'#','#',' '}, {' ','#',' '}, {' ','#',' '}},

    {{'#','#','#'}, {' ','#',' '}, {' ',' ',' '}},
    {{' ','#',' '}, {'#','#',' '}, {' ','#',' '}},
    {{' ','#',' '}, {'#','#','#'}, {' ',' ',' '}},
    {{'#',' ',' '}, {'#','#',' '}, {'#',' ',' '}}
  };
static const int SIZEW[PATNUM] = {2, 2,3, 2,3, 2,3, 3,2,3,2, 3,2,3,2, 3,2,3,2};
static const int SIZEH[PATNUM] = {2, 3,2, 3,2, 3,2, 2,3,2,3, 2,3,2,3, 2,3,2,3};

// 下端衝突判定
int collisionBottomWall(int blocX, int blocY, int bottom, int pattern )
{
  int flag = 0;

  // 衝突の位置をブロック別に判定
  if( blocY+SIZEH[pattern] == bottom) {
    flag = 1;
  }
  return flag;
}

// 下部ブロック衝突判定
int collisionBottomBlock(int blocX, int blocY, char buffer[256][256], int pattern)
{
  switch( pattern ) {
    case 0: 
      /* 下部2つにブロックがあれば衝突 */
      if( buffer[blocY + 2][blocX] == '#' || 
	  buffer[blocY + 2][blocX + 1] == '#') return 1;
      break;
    case 1:
      /* 下部中央にブロックがあれば衝突 */
      if( buffer[blocY + 3][blocX + 1] == '#' ) return 1;
      break;
    case 2:
      /* 下部にブロックがあれば衝突 */
      if( buffer[blocY + 2][blocX] == '#' || 
	       buffer[blocY + 2][blocX + 1] == '#' || 
	       buffer[blocY + 2][blocX + 2] == '#' ) return 1;
      break;
    case 3:
      /* 下部左端および下段中央にブロックがあれば衝突 */
      if( buffer[blocY + 3][blocX] == '#' ||
        buffer[blocY + 2][blocX + 1] == '#' ) return 1;
      break;
    case 4:
      /* 下部右2つおよび下段左端にブロックがあれば衝突 */
      if( buffer[blocY + 2][blocX + 1] == '#' || 
        buffer[blocY + 2][blocX + 2] == '#' ||
        buffer[blocY + 1][blocX] == '#' ) return 1;
      break;
    case 5:
      /* 下部中央および下段左端にブロックがあれば衝突 */
      if( buffer[blocY + 3][blocX + 1] == '#' ||
	  buffer[blocY + 2][blocX] == '#' ) return 1;
      break;
    case 6:
      /* 下部左2つおよび下段右端にブロックがあれば衝突 */
      if( buffer[blocY + 2][blocX] == '#' ||
        buffer[blocY + 2][blocX + 1] == '#' ||
	  buffer[blocY + 1][blocX + 2] == '#' ) return 1;
      break;
    case 7:
      /* 下部にブロックがあれば衝突 */
      if( buffer[blocY + 2][blocX] == '#' ||
               buffer[blocY + 2][blocX + 1] == '#' ||
	  buffer[blocY + 2][blocX + 2] == '#' ) return 1;
      break;
    case 8:
      /* 下部左端および中段中央にブロックがあれば衝突 */
      if( buffer[blocY + 3][blocX] == '#' ||
	  buffer[blocY + 1][blocX + 1] == '#' ) return 1;
      break;
    case 9:
      /* 下部右端および中段左2つにブロックがあれば衝突 */
      if( buffer[blocY + 2][blocX + 2] == '#' ||
          buffer[blocY + 1][blocX] == '#' ||
	  buffer[blocY + 1][blocX + 1] == '#' ) return 1;
      break;
    case 10:
      /* 下部2つにブロックがあれば衝突 */
      if( buffer[blocY + 3][blocX] == '#' ||
          buffer[blocY + 3][blocX + 1] == '#') return 1;
      break;
    case 11:
      /* 下部にブロックがあれば衝突 */
      if( buffer[blocY + 2][blocX] == '#' ||
               buffer[blocY + 2][blocX + 1] == '#' ||
          buffer[blocY + 2][blocX + 2] == '#' ) return 1;
      break;
    case 12:
      /* 下部2つにブロックがあれば衝突 */
      if( buffer[blocY + 3][blocX] == '#' ||
          buffer[blocY + 3][blocX + 1] == '#') return 1;
      break;
    case 13:
      /* 下部左端および中段右2つにブロックがあれば衝突 */
      if( buffer[blocY + 2][blocX] == '#' ||
          buffer[blocY + 1][blocX + 1] == '#' ||
          buffer[blocY + 1][blocX + 2] == '#' ) return 1;
      break;
    case 14:
      /* 下部中央および中段左にブロックがあれば衝突 */
      if( buffer[blocY + 3][blocX + 1] == '#' ||
          buffer[blocY + 1][blocX] == '#' ) return 1;
      break;
    case 15:
      /* 下部中央および中段両端にブロックがあれば衝突 */
    if( buffer[blocY + 2][blocX + 1] == '#' ||
	buffer[blocY + 1][blocX] == '#' ||
	buffer[blocY + 1][blocX + 2] == '#' ) return 1;
    break;
  case 16:
    /* 下部中央および下段左端にブロックがあれば衝突 */
      if( buffer[blocY + 3][blocX + 1] == '#' ||
          buffer[blocY + 2][blocX] == '#' ) return 1;
    break;
  case 17:
    /* 下部にブロックがあれば衝突 */
    if( buffer[blocY + 2][blocX] == '#' ||
               buffer[blocY + 2][blocX + 1] == '#' ||
	buffer[blocY + 2][blocX + 2] == '#' ) return 1;
    break;
  case 18:
    /* 下部左端および中段中央にブロックがあれば衝突 */
    if( buffer[blocY + 3][blocX] == '#' ||
	buffer[blocY + 2][blocX + 1] == '#' ) return 1;
    break;
  }
  return 0;
}

// 左部衝突判定
int collisionLeftBlock(int blocX, int blocY, char buffer[256][256], int pattern)
{
  switch(pattern){
    case 0:
      /* 左部上2つにブロックがあれば衝突 */
      if( buffer[blocY][blocX - 1] == '#' || 
        buffer[blocY + 1][blocX - 1] == '#' ) return 1;
      break;
    case 1:
      /* 左部にブロックがあれば衝突 */
      if( buffer[blocY][blocX] == '#' || 
        buffer[blocY + 1][blocX] == '#' || 
        buffer[blocY + 2][blocX] == '#' ) return 1;
      break;
    case 2:
      /* 左部中央にブロックがあれば衝突 */
      if( buffer[blocY + 1][blocX - 1] == '#' ) return 1;
      break;
    case 3:
      /* 左部下2つおよび左行上端にブロックがあれば衝突 */
      if( buffer[blocY][blocX] == '#' ||
        buffer[blocY + 1][blocX - 1] == '#' ||
        buffer[blocY + 2][blocX - 1] == '#' ) return 1;
      break;
    case 4:
      /* 左部上端および左行中央にブロックがあれば衝突 */
      if( buffer[blocY][blocX - 1] == '#' ||
        buffer[blocY + 1][blocX] == '#' ) return 1;
      break;
  case 5:
    /* 左部上2つおよび左行下端にブロックがあれば衝突 */
    if( buffer[blocY][blocX - 1] == '#' ||
        buffer[blocY + 1][blocX - 1] == '#' ||
        buffer[blocY + 2][blocX] == '#' ) return 1;
    break;
  case 6:
    /* 左部中央および左行上端にブロックがあれば衝突 */
    if( buffer[blocY][blocX] == '#' ||
        buffer[blocY + 1][blocX - 1] == '#' ) return 1;
    break;
  case 7:
    /* 左部上2つにブロックがあれば衝突 */
    if( buffer[blocY][blocX - 1] == '#' ||
        buffer[blocY + 1][blocX - 1] == '#' ) return 1;
    break;
  case 8:
    /* 左部にブロックがあれば衝突 */
    if( buffer[blocY][blocX - 1] == '#' ||
        buffer[blocY + 1][blocX - 1] == '#' ||
        buffer[blocY + 2][blocX - 1] == '#' ) return 1;
    break;
  case 9:
    /* 左部上端および中行中央にブロックがあれば衝突 */
    if( buffer[blocY][blocX - 1] == '#' ||
        buffer[blocY + 1][blocX + 1] == '#' ) return 1;
    break;
  case 10:
    /* 左部下端および左行上2つにブロックがあれば衝突 */
    if( buffer[blocY][blocX] == '#' ||
        buffer[blocY + 1][blocX] == '#' ||
        buffer[blocY + 2][blocX - 1] == '#' ) return 1;
    break;
  case 11:
    /* 左部中央および中行上端にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 1] == '#' ||
        buffer[blocY + 1][blocX - 1] == '#' ) return 1;
    break;
  case 12:
    /* 左部にブロックがあれば衝突 */
    if( buffer[blocY][blocX - 1] == '#' ||
        buffer[blocY + 1][blocX - 1] == '#' ||
        buffer[blocY + 2][blocX - 1] == '#' ) return 1;
    break;
  case 13:
    /* 左部上2つにブロックがあれば衝突 */
    if( buffer[blocY][blocX - 1] == '#' ||
        buffer[blocY + 1][blocX - 1] == '#' ) return 1;
    break;
  case 14:
    /* 左部上端および左行下2つにブロックがあれば衝突 */
    if( buffer[blocY][blocX - 1] == '#' ||
        buffer[blocY + 1][blocX] == '#' ||
        buffer[blocY + 2][blocX] == '#' ) return 1;
    break;
  case 15:
    /* 左部上端および左行中央にブロックがあれば衝突 */
    if( buffer[blocY][blocX - 1] == '#' ||
        buffer[blocY + 1][blocX] == '#' ) return 1;
    break;
  case 16:
    /* 左部中央および左行上下端にブロックがあれば衝突 */
    if( buffer[blocY][blocX] == '#' ||
        buffer[blocY + 1][blocX - 1] == '#' ||
        buffer[blocY + 2][blocX] == '#' ) return 1;
    break;
  case 17:
    /* 左部中央および左行上端にブロックがあれば衝突 */
    if( buffer[blocY][blocX] == '#' ||
	buffer[blocY + 1][blocX - 1] == '#' ) return 1;
    break;
  case 18:
    /* 左部にブロックがあれば衝突 */
    if( buffer[blocY][blocX - 1] == '#' ||
        buffer[blocY + 1][blocX - 1] == '#' ||
        buffer[blocY + 2][blocX - 1] == '#' ) return 1;
    break;
  }
  return 0;
}


// 右部衝突判定
int collisionRightBlock(int blocX, int blocY, char buffer[256][256], int pattern)
{
  switch(pattern){
  case 0:
    /* 右部上2つにブロックがあれば衝突 */
    if( buffer[blocY][blocX + 2] == '#' ||
        buffer[blocY + 1][blocX + 2] == '#' ) return 1;
    break;
  case 1:
    /* 右部にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 2] == '#' ||
        buffer[blocY + 1][blocX + 2] == '#' ||
        buffer[blocY + 2][blocX + 2] == '#' ) return 1;
    break;
  case 2:
    /* 右部中央にブロックがあれば衝突 */
    if( buffer[blocY + 1][blocX + 3] == '#' ) return 1;
    break;
  case 3:
    /* 右部上2つおよび右行下端にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 2] == '#' ||
        buffer[blocY + 1][blocX + 2] == '#' ||
        buffer[blocY + 2][blocX + 1] == '#' ) return 1;
    break;
  case 4:
    /* 右部中央および左行下端にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 2] == '#' ||
        buffer[blocY + 1][blocX + 3] == '#' ) return 1;
    break;
  case 5:
    /* 右部下2つおよび右行上端にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 1] == '#' ||
        buffer[blocY + 1][blocX + 2] == '#' ||
        buffer[blocY + 2][blocX + 2] == '#' ) return 1;
    break;
  case 6:
    /* 右部上端および右行中央にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 3] == '#' ||
        buffer[blocY + 1][blocX + 2] == '#' ) return 1;
    break;
  case 7:
    /* 右部中央および中行上端にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 1] == '#' ||
        buffer[blocY + 1][blocX + 3] == '#' ) return 1;
    break;
  case 8:
    /* 右部上端および中行下2つにブロックがあれば衝突 */
    if( buffer[blocY][blocX + 2] == '#' ||
        buffer[blocY + 1][blocX + 1] == '#' ||
        buffer[blocY + 2][blocX + 1] == '#' ) return 1;
    break;
  case 9:
    /* 右部上2つにブロックがあれば衝突 */
    if( buffer[blocY][blocX + 3] == '#' ||
        buffer[blocY + 1][blocX + 3] == '#' ) return 1;
    break;
  case 10:
    /* 右部にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 2] == '#' ||
	buffer[blocY + 1][blocX + 2] == '#' ||
        buffer[blocY + 2][blocX + 2] == '#' ) return 1;
    break;
  case 11:
    /* 右部上2つにブロックがあれば衝突 */
    if( buffer[blocY][blocX + 3] == '#' ||
        buffer[blocY + 1][blocX + 3] == '#' ) return 1;
    break;
  case 12:
    /* 右部下端および中行上2つにブロックがあれば衝突 */
    if( buffer[blocY][blocX + 1] == '#' ||
        buffer[blocY + 1][blocX + 1] == '#' ||
        buffer[blocY + 2][blocX + 2] == '#' ) return 1;
    break;
  case 13:
    /* 右部上端および中行中央にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 3] == '#' ||
        buffer[blocY + 1][blocX + 1] == '#' ) return 1;
    break;
  case 14:
    /* 右部にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 2] == '#' ||
        buffer[blocY + 1][blocX + 2] == '#' ||
        buffer[blocY + 2][blocX + 2] == '#' ) return 1;
    break;
  case 15:
    /* 右部上端および右行中央にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 3] == '#' ||
        buffer[blocY + 1][blocX + 2] == '#' ) return 1;
    break;
  case 16:
    /* 右部にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 2] == '#' ||
        buffer[blocY + 1][blocX + 2] == '#' ||
        buffer[blocY + 2][blocX + 2] == '#' ) return 1;
    break;
  case 17:
    /* 右部中央および右行上端にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 2] == '#' ||
        buffer[blocY + 1][blocX + 3] == '#' ) return 1;
    break;
  case 18:
    /* 右部中央および右行上下端にブロックがあれば衝突 */
    if( buffer[blocY][blocX + 1] == '#' ||
        buffer[blocY + 1][blocX + 2] == '#' ||
        buffer[blocY + 2][blocX + 1] == '#' ) return 1;
    break;
  }
  return 0;
}

// 回転
int rotate( int pattern )
{
  switch( pattern ) {
  case 0:
    return 0;
    break;
  case 1:
  case 3:
  case 5:
  case 7:
  case 8:
  case 9:
  case 11:
  case 12:
  case 13:
  case 15:
  case 16:
  case 17:
    return pattern+1;
    break;
  case 2:
  case 4:
  case 6:
    return pattern-1;
    break;
  case 10:
  case 14:
  case 18:
    return pattern-3;
    break;
  }
  return 0;
}

int go()
{
  int blocX, blocY;
  int ch;
  int delay=0;
  int waitCount = 20000;
  char msg[256];
  int pattern, pattern2, pattern3;
  char buffer[256][256];
  char color_buffer[256][256];
  int i, j;
  int ii, jj;
  int count = 0;
  int flgErase = 0;
  int level = 1;
  int eraseln = 0; 
  int score = 0;
  time_t stime, ctime;

  blocX = COLS*3/8;
  blocY = 0;

  // パターンの出順をシャッフル
  int rndpat[7] = {0,1,3,5,7,11,15};
  srand( (unsigned int) time( NULL ) );
  for(i=0; i<7; i++){
    int r = rand() % 8;
    int t = rndpat[i];
    rndpat[i] = rndpat[r];
    rndpat[r] = t;
  }
  pattern = rndpat[0];
  pattern2 = rndpat[1];
  pattern3 = rndpat[2];
  count = 3;

  time(&stime);

  for(j=0;j<256;j++){
    for(i=0;i<256;i++){
      buffer[j][i]=' ';
    }
  }

  timeout(0);
 
  while((ch=getch())!='q'){
	attron(COLOR_PAIR(DEFAULT));
    mvaddstr(blocY,blocX,"   ");
    mvaddstr(blocY+1,blocX,"   ");
    mvaddstr(blocY+2,blocX,"   ");

    if(delay%waitCount==0){
      blocY += 1;
    }
    if(pattern!=1 && blocX<COLS/4 + 1){
      blocX = COLS/4 + 1;
      beep();
    }
    if(pattern==1 && blocX<COLS/4){
      blocX = COLS/4;
      beep();
    }
    if(SIZEW[pattern]==3 &&  blocX>=COLS/2-1){
      blocX =COLS/2-2;
      beep();
    }
    if(SIZEW[pattern]==2 && blocX>=COLS/2){
      blocX=COLS/2-1;
      beep();
    }
    delay++;
    switch(ch){
    case KEY_LEFT:
      if(collisionLeftBlock(blocX, blocY, buffer, pattern) == 0) blocX -=1;
      break;
    case KEY_RIGHT:
      if(collisionRightBlock(blocX, blocY, buffer, pattern) == 0) blocX +=1;
      break;
    case ' ':
      if(collisionRightBlock(blocX, blocY, buffer, pattern) == 0) blocX +=1;
      break;
    case 'z':
      pattern = rotate( pattern );
      beep();
      break;
    case KEY_DOWN:
      while(collisionBottomWall(blocX, blocY, LINES-3, pattern) == 0 &&
	    collisionBottomBlock(blocX, blocY, buffer, pattern) == 0 ){
	blocY += 1;
	score += 1;
      }
      break;
    default:
      break;
    }
    
    for(j=1; j<LINES; j++){
      for(i=COLS/4+1; i<COLS/2+1; i++){
		attron(COLOR_PAIR(color_buffer[j][i]));
		mvaddch(j, i, buffer[j][i] );
      }
    }
    
    attron(COLOR_PAIR(pattern + 1));
    for(jj=0; jj<3; jj++){
      for(ii=0; ii<3; ii++){
	// 既にあるブロック('#')の上書きを防止
	if(buffer[blocY+jj][blocX+ii] == ' ' && 
	   blockPattern[pattern][jj][ii] == '#' )
	  mvaddch(blocY+jj, blocX+ii, blockPattern[pattern][jj][ii]);
      }
    }
    if( collisionBottomWall(blocX, blocY, LINES-3, pattern) || 
	collisionBottomBlock(blocX, blocY, buffer, pattern) ){
      for(jj=0; jj<3; jj++){
	for(ii=0; ii<3; ii++){
	  // 既にあるブロック('#')の上書きを防止
	  if(buffer[blocY+jj][blocX+ii] == ' ' &&
	     blockPattern[pattern][jj][ii] == '#' ){
	 	buffer[blocY+jj][blocX+ii] = blockPattern[pattern][jj][ii];
	   	color_buffer[blocY+jj][blocX+ii] = pattern + 1;
	  }
	}
      }
      beep();
      blocX = COLS*3/8;
      blocY = 0;
      pattern = pattern2;
      pattern2 = pattern3;
      pattern3 = rndpat[count];
      count++;
      if( count == 7 ){
	srand( (unsigned int) time( NULL ) );
	for(i=0; i<7; i++){
	  int r = rand() % 8;
	  int t = rndpat[i];
	  rndpat[i] = rndpat[r];
	  rndpat[r] = t;
	}
	count = 0;
      }
    }
    
    attron(COLOR_PAIR(DEFAULT));
     for(j=1;j<LINES-3;j++){
	  mvaddch(j,COLS/4,'|');
	  mvaddch(j,COLS/2+1,'|');
     }
     for(i=COLS/4+1;i<COLS/2+1;i++){
	  mvaddch(0,i,'-');
	  mvaddch(LINES-3,i,'-');
     }
     mvaddch(0,COLS/4,'*');
     mvaddch(0,COLS/2+1,'*');

     time(&ctime);
     sprintf(msg, "Time\t%05d",(int)( ctime - stime ));  
     sprintf(msg, "Level\t   %02d", level );
     mvaddstr(3,COLS-20,msg );
    sprintf(msg, "Score\t%05d", score );
    mvaddstr(4,COLS-20,msg );
    sprintf(msg,"High Score\t%05d", hscore[0]);
    mvaddstr(5,COLS-20,msg);
    sprintf(msg,"Name\t%s", name[0]);
    mvaddstr(6,COLS-20,msg);
    mvaddstr(7,COLS-20,"Next Blocks");
    mvaddstr(8,COLS-17,"First Second");
    mvaddstr(9,COLS-17,"+---+ +---+");
    mvaddstr(10,COLS-17,"|   | |   |");
    mvaddstr(11,COLS-17,"|   | |   |");
    mvaddstr(12,COLS-17,"|   | |   |");
    mvaddstr(13,COLS-17,"+---+ +---+");

    attron(COLOR_PAIR(pattern2 + 1));
    for(jj=0; jj<3; jj++){
      for(ii=0; ii<3; ii++){
          mvaddch(10+jj, COLS-16+ii, blockPattern[pattern2][jj][ii]);
      }
    }

    attron(COLOR_PAIR(pattern3 + 1));
    for(jj=0; jj<3; jj++){
      for(ii=0; ii<3; ii++){
	mvaddch(10+jj, COLS-10+ii, blockPattern[pattern3][jj][ii]);
      }
    }


    // 一列ブロックが揃ったかどうか判定
    for(j=0;j<LINES-3;j++){
      flgErase = 1;
      for(i=COLS/4+1;i<=COLS/2;i++){
      	if(buffer[j][i] == ' '){
	  flgErase = 0;
	}
      }
      // 一列消去
      if(flgErase){
	eraseln += 1;
	
	if( level < 20 && eraseln >= level * 10 + 10 ){
	  level += 1;
	  eraseln = 0;
	  waitCount -= 800;
	}
	score += 40 * level;
	for(jj=j;jj>=1;jj--){
	  for(ii=COLS/4+1;ii<=COLS/2;ii++){
	    buffer[jj][ii] = buffer[jj-1][ii];
	    color_buffer[jj][ii] = color_buffer[jj-1][ii];
	  }
	}
      }
    }
    // 最上部までブロックが積み上がったかどうかの判定
    for(i=COLS/4+1;i<=COLS/2;i++){
      if(buffer[1][i] == '#'){
	fprintf(stderr, "POINT2\n");
	goto OUT;
      }
    }
  }
 OUT:
  timeout(-1);
  return score;
}
