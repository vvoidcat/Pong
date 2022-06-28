#include "pong.h"

void initTriggers(trigger *trigger) {
  (*trigger).game_start = 1;
  (*trigger).round_end = 0;
}

int initPlayer(player *player, int index) {
  int error = 1;
  (*player).collider = malloc(sizeof(int) * PLAYER_SIZE);

  if ((*player).collider) {
    (*player).index = index;
    (*player).ai = index;  // TEMP
    if (index == 1) {
      updatePlayer(player, PLAYER1_STARTPOS, 0);
    } else if (index == 2) {
      updatePlayer(player, PLAYER2_STARTPOS, 0);
    }
  } else {
    error = 0;
  }
  return error;
}

int initBall(ball *ball) {
  updateBall(ball, BALL_STARTPOS, BALL_STARTDIR, 1);
  return 1;
}

int checkUserInput(player *player1, player *player2) {
  int playmode = 1;
  system("/bin/stty raw");

  if (getBytes() != 0) {
    int key = getchar();

    // if (!(*player2).ai) {
    if (key == 'k' || key == 'K') {
      updatePlayerPosition(player2,
                           getVector2(PLAYER2_X, (*player2).position.y - 1));
    } else if (key == 'm' || key == 'M') {
      updatePlayerPosition(player2,
                           getVector2(PLAYER2_X, (*player2).position.y + 1));
    }
    //}
    if (key == 'w' || key == 'W') {
      updatePlayerPosition(player1,
                           getVector2(PLAYER1_X, (*player1).position.y - 1));
    } else if (key == 's' || key == 'S') {
      updatePlayerPosition(player1,
                           getVector2(PLAYER1_X, (*player1).position.y + 1));
    }
    if (key == 'q' || key == 'Q') {
      playmode = 0;
    }
  }

  system("/bin/stty cooked");
  return playmode;
}

int getBytes() {
  int out_bytes;
  ioctl(1, FIONREAD, &out_bytes);
  return out_bytes;
}

vector2 getVector2(int x, int y) {
  vector2 result;
  result.x = x;
  result.y = y;
  return result;
}

void updateBall(ball *ball, vector2 position, vector2 direction, int speed) {
  (*ball).position = position;
  (*ball).direction = direction;
  (*ball).speed = speed;
}

void updatePlayer(player *player, vector2 newposition, int newscore) {
  updatePlayerScore(player, newscore);
  updatePlayerPosition(player, newposition);
}

void updatePlayerScore(player *player, int newscore) {
  (*player).score = newscore;
}

void updatePlayerPosition(player *player, vector2 newposition) {
  if (newposition.y < 2) {
    newposition.y = 2;
  } else if (newposition.y > NHEIGHT - 3) {
    newposition.y = NHEIGHT - 3;
  }
  (*player).position = newposition;
  (*player).collider =
      updatePlayerCollider((*player).collider, (*player).position.y);
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
      if (i == 0 || i == NHEIGHT - 1) {
        field[i][j] = BORDER_WS;
      } else if (j == 0) {
        field[i][j] = BORDER_A;
      } else if (j == NWIDTH - 1) {
        field[i][j] = BORDER_D;
      } else if (findPlayer(j, i, player1) == 1) {
        field[i][j] = PLAYER1;
      } else if (findPlayer(j, i, player2) == 2) {
        field[i][j] = PLAYER2;
      } else if (i == ball.position.y && j == ball.position.x) {
        field[i][j] = BALL;
      } else {
        field[i][j] = EMPTY;
      }
    }
  }
}

int findPlayer(int x, int y, player player) {
  int found = 0;
  if (x == player.position.x) {
    for (int i = 0; i < PLAYER_SIZE; i++) {
      if (player.collider[i] == y) {
        found = player.index;
        break;
      }
    }
  }
  return found;
}

void draw(int **field, player player1, player player2, trigger *trigger) {
  printf("\e[H\e[2J\e[3J");
  drawInstructions();
  drawField(field, player1, player2, trigger);
}

void drawInstructions() {
  printf("  [w]/[s]" COLOR_BLUE " = player1 UP/DOWN; " COLOR_RESET
         "[k]/[m]" COLOR_BLUE " = player2 UP/DOWN; " COLOR_RESET
         "[q]" COLOR_BLUE " = quit" COLOR_RESET);
  printf("\n\n\n");
}

void drawField(int **field, player player1, player player2, trigger *trigger) {
  for (int i = 0; i < NHEIGHT; i++) {
    if (i == NHEIGHT / 6) {
      printf("    %02d\t", player1.score);
    } else {
      printf("   \t");
    }

    for (int j = 0; j < NWIDTH; j++) {
      if (field[i][j] == PLAYER1 || field[i][j] == PLAYER2) {
        printf("║");
      } else if (field[i][j] == BALL) {
        printf(COLOR_YELLOW "@" COLOR_RESET);
      } else if (field[i][j] == BORDER_WS) {
        printf(COLOR_BLUE "-" COLOR_RESET);
      } else if (field[i][j] == BORDER_A || field[i][j] == BORDER_D) {
        printf(COLOR_BLUE "¦" COLOR_RESET);
      } else if (field[i][j] == EMPTY) {
        printf(COLOR_BLUE " " COLOR_RESET);
      }
      if ((*trigger).game_start) {
        delay(2);
      }
    }

    if (i == NHEIGHT / 6) {
      printf("  %02d", player2.score);
    }
    printf("\n");
  }

  (*trigger).game_start = 0;
  printf("\n");
}

void delay(int milliseconds) {
  milliseconds = milliseconds * 100;
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
