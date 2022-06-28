#include "pong.h"

int main(int argc, char *argv[]) {
  int playmode = 1;
  int delaytime = 400;
  int error_index = 0;

  vector2 direction_ball;
  vector2 position_ball;
  ball ball;

  vector2 position_player1;
  vector2 position_player2;
  player player1;
  player player2;

  int **field = NULL;

  field = allocatePointerArray(NWIDTH, NHEIGHT);
  initValues(&position_player1, &position_player2, &position_ball,
             &direction_ball);

  // check argv

  if (initPlayer(&player1, position_player1, PLAYER1) &&
      initPlayer(&player2, position_player2, PLAYER2) && field) {
    while (playmode) {
      // check for player input
      // if playmode = 0 then quit

      updateBall(&ball, position_ball, direction_ball, 1);
      updateField(field, player1, player2, ball);

      drawField(field);
      delay(delaytime);
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
