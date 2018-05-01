#ifndef _TETRIS_BODY_H_
#define _TETRIS_BODY_H_

#define DEFAULT 20

#define PATNUM 19
#define PATSIZEW 3
#define PATSIZEH 3

int hscore[5];
char name[5][256];

int main();
int go();
int collisionBottomWall(int blocX, int blocY, int bottom, int pattern );
int collisionBottomBlock(int blocX, int blocY, char buffer[256][256], int pattern);
int collisionLeftBlock(int blocX, int blocY, char buffer[256][256], int pattern);
int collisionRightBlock(int blocX, int blocY, char buffer[256][256], int pattern);
int rotate( int pattern );

#endif
