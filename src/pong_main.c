#include "pong.h"

int main(int argc, char *argv[]) {
  position position1;
  position position2;
  player player1;
  player player2;
  int error_index = 0;

  if (initPlayer(&player1, &position1, 1) &&
      initPlayer(&player2, &position2, 2)) {
    //
    printf("mem ok");
  } else {
    error_index = 1;
  }

  if (error_index > 0) {
    printError(error_index);
  }

  freeArray(player1.body);
  freeArray(player2.body);

  return 0;
}
