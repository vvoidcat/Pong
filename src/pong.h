#ifndef SRC_PONG_H_
#define SRC_PONG_H_

#include <stdio.h>
#include <stdlib.h>

#define NWIDTH 80
#define NHEIGHT 25

#define PLAYER1_Y 10
#define PLAYER2_Y 70
#define PLAYER_X 13
#define PLAYER_SIZE 3

#define ERRORLIST {"error[1]: memory allocation failure", "Unknown error "};

typedef struct {
  int x;
  int y;
} position;

typedef struct {
  position position;
  int *body;
  int index;
} player;

int initPlayer(player *player, position *position, int index);

int *updatePlayerBody(int *body, int y);

void freePointerArray(int **parray, int size);
void freeArray(int *array);

void printError(int index);

#endif  // SRC_PONG_H_
