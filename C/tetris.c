#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "tetris_body.h"

void printscore(char name[][256], int score[5]);

// 初期化
int main(int argc, char **argv){

  // High Scoreの読み込み
  int i, j;
  int cscore;

  FILE *fp;

  for( i=0;i<5;i++ ){
    hscore[i] = 0;
    strcpy(name[i],"---");
  }
  if((fp = fopen("record.txt", "r")) != NULL ){
    i=0;
    while(fscanf(fp,"%s%d", name[i], &hscore[i]) != EOF && i < 5) i++;
    fclose(fp);
  }
  printf("%s\n",name[0]);  

  initscr();
  start_color();
  noecho();
  cbreak();
  curs_set(0);
  // 色設定
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_CYAN, COLOR_BLACK);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  init_pair(5, COLOR_RED, COLOR_BLACK);
  init_pair(6, COLOR_GREEN, COLOR_BLACK);
  init_pair(7, COLOR_GREEN, COLOR_BLACK);
  init_pair(8, COLOR_BLUE, COLOR_BLACK);
  init_pair(9, COLOR_BLUE, COLOR_BLACK);
  init_pair(10, COLOR_BLUE, COLOR_BLACK);
  init_pair(11, COLOR_BLUE, COLOR_BLACK);
  init_pair(12, COLOR_YELLOW, COLOR_BLACK);
  init_pair(13, COLOR_YELLOW, COLOR_BLACK);
  init_pair(14, COLOR_YELLOW, COLOR_BLACK);
  init_pair(15, COLOR_YELLOW, COLOR_BLACK);
  init_pair(16, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(17, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(18, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(19, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(DEFAULT, COLOR_WHITE, COLOR_BLACK);
  bkgd(COLOR_PAIR(DEFAULT));
  keypad(stdscr,TRUE);
  cscore = go();
  fprintf(stderr,"main return\n");
  if(cscore < hscore[4]){
    printscore(name, hscore);
  }else{
    i=0;
    while(cscore < hscore[i] && i<5) i++;
    for(j=3;j>=i;j--){
      hscore[j+1] = hscore[j];
      strcpy(name[j+1], name[j]);
    }
    hscore[i] = cscore;
    strcpy(name[i],">>");
    printscore(name, hscore);
    mvaddstr(12,1,"Enter Your Name:");
    move(12,17);
    echo();
    getnstr(name[i],256);
  }
  if((fp = fopen("record.txt", "w")) == NULL ){
    endwin();
    printf("レコードの書き込みに失敗しました\n");
    exit(1);
  }
  for(i=0;i<5;i++){
    fprintf(fp, "%s\t%d\n", name[i], hscore[i]);
  }
  timeout(10000);      
  endwin();
  return 0;
}

void printscore(char name[][256], int score[5]){
  int i;
  char msg[270];
  attron(COLOR_PAIR(DEFAULT));
  clear();
  for(i=0;i<5;i++){
    sprintf(msg, "%s\t%05d", name[i], score[i]);
    mvaddstr(2*i+1,1,msg);
  }
}

