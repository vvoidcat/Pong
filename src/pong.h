#ifndef SRC_PONG_H_
#define SRC_PONG_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NWIDTH 80
#define NHEIGHT 25

#define PLAYER1_X 10
#define PLAYER2_X 70
#define PLAYER_Y 13
#define PLAYER_SIZE 3

#define DIR_UP 1
#define DIR_DOWN -1
#define DIR_LEFT -1
#define DIR_RIGHT 1
#define DIR_NONE 0

#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2
#define BALL 3
#define BORDER_W 4
#define BORDER_S 5
#define BORDER_AD 6

#define COLOR_BLUE "\x1B[34m"
#define COLOR_CYAN "\x1B[36m"
#define COLOR_RESET "\x1B[0m"

#define NERRORS 2
#define ERRORLIST {"error[1]: memory allocation failure", "Unknown error "};

typedef struct {
  int x;
  int y;
} vector2;

#define PLAYER1_STARTPOS \
  (vector2) { PLAYER1_X, PLAYER_Y }
#define PLAYER2_STARTPOS \
  (vector2) { PLAYER2_X, PLAYER_Y }
#define BALL_STARTPOS \
  (vector2) { NWIDTH / 2, NHEIGHT / 2 }
#define BALL_STARTDIR \
  (vector2) { DIR_LEFT, DIR_NONE }

typedef struct {
  vector2 position;
  int *collider;
  int index;
  int score;
} player;

typedef struct {
  vector2 position;
  vector2 direction;
  int speed;
} ball;

int initPlayer(player *player, int index);
int initBall(ball *ball);

void updateBall(ball *ball, vector2 position, vector2 direction, int speed);
void updatePlayer(player *player, vector2 newposition, int newscore);
int *updatePlayerCollider(int *collider, int y);
void updateField(int **field, player player1, player player2, ball ball);

int isPlayer(int x, int y, player player);

void drawField(int **field);
void delay(int milliseconds);

int **allocatePointerArray(int size_x, int size_y);
void freePointerArray(int **parray, int size);
void freeArray(int *array);

void printError(int index);

#endif  // SRC_PONG_H_
