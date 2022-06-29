#ifndef SRC_PONG_H_
#define SRC_PONG_H_

#include <sys/ioctl.h>
#include <time.h>

#include "helper.h"

typedef struct {
  int x;
  int y;
} vector2;

typedef struct {
  vector2 position;
  int *collider;
  int index;
  int score;
  int ai;
} player;

typedef struct {
  vector2 position;
  vector2 direction;
  int speed;
} ball;

typedef struct {
  int game_start;
  int round_end;
} trigger;

#define NWIDTH 80
#define NHEIGHT 25

#define PLAYER1_X 10
#define PLAYER2_X 70
#define PLAYER_Y 12
#define PLAYER_SIZE 3

#define UP 1
#define DOWN -1
#define LEFT -1
#define RIGHT 1
#define NONE 0

#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2
#define BALL 3
#define BORDER_WS 4
#define BORDER_A 5
#define BORDER_D 6

#define COLOR_BLUE "\x1B[34m"
#define COLOR_YELLOW "\x1B[33m"
#define COLOR_MAGENTA "\x1B[35m"
#define COLOR_RESET "\x1B[0m"

#define PLAYER1_STARTPOS \
  (vector2) { PLAYER1_X, PLAYER_Y }
#define PLAYER2_STARTPOS \
  (vector2) { PLAYER2_X, PLAYER_Y }
#define BALL_STARTPOS \
  (vector2) { NWIDTH / 2, NHEIGHT / 2 }
#define BALL_STARTDIR \
  (vector2) { LEFT, NONE }

void initTriggers(trigger *trigger);
int initPlayer(player *player, int index);
int initBall(ball *ball);

int checkUserInput(player *player1, player *player2);
int getBytes();

vector2 getVector2(int x, int y);

void updateBall(ball *ball, vector2 position, vector2 direction, int speed);

void updatePlayer(player *player, vector2 newposition, int newscore);
void updatePlayerScore(player *player, int newscore);
void updatePlayerPosition(player *player, vector2 newposition);
int *updatePlayerCollider(int *collider, int y);

void updateField(int **field, player player1, player player2, ball ball);
int findPlayer(int x, int y, player player);

void draw(int **field, player player1, player player2, trigger *trigger);
void drawInstructions();
void drawField(int **field, player player1, player player2, trigger *trigger);
void delay(int milliseconds);

#endif  // SRC_PONG_H_
