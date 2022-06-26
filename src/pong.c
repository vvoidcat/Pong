#include "pong.h"

int initPlayer(player *player, position *position, int index) {
  int error = 1;

  if (index == 1) {
    (*position).x = PLAYER_X;
    (*position).y = PLAYER1_Y;
  } else if (index == 2) {
    (*position).x = PLAYER_X;
    (*position).y = PLAYER2_Y;
  }

  (*player).position = *position;
  (*player).index = index;

  (*player).body = malloc(sizeof(int) * PLAYER_SIZE);

  if ((*player).body) {
    updatePlayerBody((*player).body, (*position).y);
  } else {
    error = 0;
  }

  return error;
}

void initField() {}

int *updatePlayerBody(int *body, int y) {
  int newbody[3] = {y - 1, y, y + 1};
  body = newbody;
  return body;
}

void freePointerArray(int **parray, int size) {
  for (int i = 0; i < size; i++) {
    freeArray(parray[i]);
  }
  if (parray) {
    free(parray);
  }
}

void freeArray(int *array) {
  if (array) {
    free(array);
  }
}

void printError(int index) {
  if (index != 0 && index < NERRORS) {
    char errors[][300] = ERRORLIST;
    fprintf(stderr, "%s", errors[index - 1]);
    fprintf(stderr, "\n");
  }
}
