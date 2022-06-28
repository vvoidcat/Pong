#include "pong.h"

int main(int argc, char *argv[]) {
  trigger trigger;
  player player1;
  player player2;
  ball ball;
  int **field = NULL;
  int playmode = 1;
  int delaytime = 300;
  int error_index = 0;

  field = allocatePointerArray(NWIDTH, NHEIGHT);
  initTriggers(&trigger);

  // check argv

  if (initPlayer(&player1, PLAYER1) && initPlayer(&player2, PLAYER2) &&
      initBall(&ball) && field) {
    if (freopen("/dev/tty", "r", stdin)) {
      while (playmode) {
        if (!trigger.game_start) {
          playmode = checkUserInput(&player1, &player2);
          // updateBall(&ball, position_ball, direction_ball, 1);
        }
        updateField(field, player1, player2, ball);
        draw(field, player1, player2, &trigger);
        delay(delaytime);
      }
    } else {
      error_index = 2;
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
