#ifndef SRC_PONG_H_
#define SRC_PONG_H_

#include <stdio.h>
#include <stdlib.h>

#define NWIDTH 80
#define NHEIGHT 25

#define DIV_X NWIDTH / 2
#define DIV_Y NHEIGHT / 2

#define PLAYER1_Y 10
#define PLAYER2_Y 70
#define PLAYER_X 13
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
#define DIV 4
#define BORDER_WS 5
#define BORDER_AD 6

#define NERRORS 2
#define ERRORLIST {"error[1]: memory allocation failure", "Unknown error "};

typedef struct {
  int x;
  int y;
} vector2;

#define PLAYER1_STARTPOS \
  (vector2) { PLAYER_X, PLAYER1_Y }
#define PLAYER2_STARTPOS \
  (vector2) { PLAYER_X, PLAYER2_Y }
#define BALL_STARTPOS \
  (vector2) { DIV_X, DIV_Y }
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

void initValues(vector2 *position_player1, vector2 *position_player2,
                vector2 *position_ball, vector2 *direction_ball);
int initPlayer(player *player, vector2 position, int index);

void updateBall(ball *ball, vector2 position, vector2 direction, int speed);
int *updatePlayerCollider(int *collider, int y);
void updateField(int **field, player player1, player player2, ball ball);

void drawField(int **field);

int **allocatePointerArray(int size_x, int size_y);
void freePointerArray(int **parray, int size);
void freeArray(int *array);

void printError(int index);

#endif  // SRC_PONG_H_
