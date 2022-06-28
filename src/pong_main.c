#include "pong.h"

int main(int argc, char *argv[]) {
  player player1;
  player player2;
  ball ball;
  int **field = NULL;
  int playmode = 1;
  int delaytime = 400;
  int error_index = 0;

  field = allocatePointerArray(NWIDTH, NHEIGHT);

  // check argv

  if (initPlayer(&player1, PLAYER1) && initPlayer(&player2, PLAYER2) &&
      initBall(&ball) && field) {
    while (playmode < 6) {
      // check for player input
      // if playmode = 0 then quit

      // updateBall(&ball, position_ball, direction_ball, 1);
      updateField(field, player1, player2, ball);

      drawField(field);
      delay(delaytime);
      playmode++;
    }
  } else {
    error_index = 1;
  }

  printError(error_index);

  freeArray(player1.collider);
  freeArray(player2.collider);
  freePointerArray(field, NHEIGHT);

  return 0;
}
