#include "pong.h"

void initValues(vector2 *position_player1, vector2 *position_player2,
                vector2 *position_ball, vector2 *direction_ball) {
  *position_player1 = PLAYER1_STARTPOS;
  *position_player2 = PLAYER2_STARTPOS;
  *position_ball = BALL_STARTPOS;
  *direction_ball = BALL_STARTDIR;
}

int initPlayer(player *player, vector2 position, int index) {
  int error = 1;

  (*player).collider = malloc(sizeof(int) * PLAYER_SIZE);

  if ((*player).collider) {
    (*player).index = index;
    (*player).score = 0;
    (*player).position = position;
    (*player).collider =
        updatePlayerCollider((*player).collider, (*player).position.y);
  } else {
    error = 0;
  }

  return error;
}

void updateBall(ball *ball, vector2 position, vector2 direction, int speed) {
  (*ball).position = position;
  (*ball).direction = direction;
  (*ball).speed = speed;
}

int *updatePlayerCollider(int *collider, int y) {
  int newcollider[3] = {y - 1, y, y + 1};
  for (int i = 0; i < PLAYER_SIZE; i++) {
    collider[i] = newcollider[i];
  }
  return collider;
}

void updateField(int **field, player player1, player player2, ball ball) {
  for (int i = 0; i < NHEIGHT; i++) {
    for (int j = 0; j < NWIDTH; j++) {
      if (i == 0) {
        field[i][j] = BORDER_W;
      } else if (i == NHEIGHT - 1) {
        field[i][j] = BORDER_S;
      } else if (j == 0 || j == NWIDTH - 1) {
        field[i][j] = BORDER_AD;
      } else if (isPlayer(j, i, player1) == 1) {
        field[i][j] = PLAYER1;
      } else if (isPlayer(j, i, player2) == 2) {
        field[i][j] = PLAYER2;
      } else if (i == ball.position.y && j == ball.position.x) {
        field[i][j] = BALL;
      } else {
        field[i][j] = EMPTY;
      }
    }
  }
}

int isPlayer(int x, int y, player player) {
  int result = 0;
  if (x == player.position.x) {
    for (int i = 0; i < PLAYER_SIZE; i++) {
      if (player.collider[i] == y) {
        result = player.index;
        break;
      }
    }
  }
  return result;
}

void drawField(int **field) {
  printf("\e[H\e[2J\e[3J");
  printf("\n\n");

  for (int i = 0; i < NHEIGHT; i++) {
    printf("\t");
    for (int j = 0; j < NWIDTH; j++) {
      if (field[i][j] == PLAYER1) {
        printf(COLOR_BLUE "║" COLOR_RESET);
      } else if (field[i][j] == PLAYER2) {
        printf(COLOR_BLUE "║" COLOR_RESET);
      } else if (field[i][j] == BALL) {
        printf(COLOR_BLUE "@" COLOR_RESET);
      } else if (field[i][j] == BORDER_W) {
        printf(COLOR_MAGENTA "-" COLOR_RESET);
      } else if (field[i][j] == BORDER_S) {
        printf(COLOR_MAGENTA "-" COLOR_RESET);
      } else if (field[i][j] == BORDER_AD) {
        printf(COLOR_MAGENTA "¦" COLOR_RESET);
      } else if (field[i][j] == EMPTY) {
        printf(" ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

void delay(int milliseconds) {
  milliseconds = milliseconds * 1000;
  clock_t start = clock();
  while (clock() < start + milliseconds) {
    ;
  }
}

int **allocatePointerArray(int size_x, int size_y) {
  int **result = NULL;
  int error = 0;

  result = malloc(sizeof(int *) * size_y);

  if (result) {
    for (int i = 0; i < size_y; i++) {
      result[i] = malloc(sizeof(int) * size_x);
      if (!result[i]) {
        error = 1;
        break;
      }
    }
  } else {
    error = 1;
  }

  if (error) {
    freePointerArray(result, NHEIGHT);
  }

  return (error) ? NULL : result;
}

void freePointerArray(int **parray, int size_y) {
  for (int i = 0; i < size_y; i++) {
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
