#include "pong.h"

int main(int argc, char *argv[]) {
  int playmode = 1;
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

  if (initPlayer(&player1, position_player1, 1) &&
      initPlayer(&player2, position_player2, 2) && field) {
    while (playmode) {
      // check for player input
      updateBall(&ball, position_ball, direction_ball, 1);

      // if something has changed
      updateField(field, player1, player2, ball);
      drawField(field);
    }

    printf("mem ok\n");
    printf("player1 = %d %d\n", player1.position.x, player1.position.y);
    printf("player2 = %d %d\n", player2.position.x, player2.position.y);
    printf("field = %p\n", field);
  } else {
    error_index = 1;
  }

  printError(error_index);

  freeArray(player1.collider);
  freeArray(player2.collider);
  freePointerArray(field, NHEIGHT);

  return 0;
}
