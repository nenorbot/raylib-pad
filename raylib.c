#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 640

int main(void) {
  size_t width = 640;
  size_t height = 640;
  InitWindow(width, HEIGHT, "hello world");
  bool paused = 0;
  int x = 0;
  int y = 0;
  int target_x = 600;
  int target_y = 400;
  int ball_x = 0;
  int ball_y = 0;
  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE)) {
      paused = !paused;
    }
    BeginDrawing();
    ClearBackground(RED);
    int dx = x / 8;
    int dy = y / 8;
    int x_loc = (ball_x + dx) % width;
    int y_loc = (ball_y + dy) % height;
    if (!paused) {
      // printf("ball_y:%zu,y:%zu,dy:%zu,y_loc:%zu\n", ball_y, y, dy, y_loc);
      if (x_loc == target_x && y_loc == target_y) {
        x = 0;
        y = 0;
        ball_x = target_x;
        ball_y = target_y;
        target_x = rand() % height;
        target_y = rand() % width;
      } else {
        if (y_loc > target_y) {
          y--;
        } else if (y_loc < target_y) {
          y++;
        }
        if (x_loc > target_x) {
          x--;
        } else if (x_loc < target_x) {
          x++;
        }
      }
    }
    DrawRectangle(x_loc, y_loc, 50, 50, WHITE);
    DrawRectangle(target_x, target_y, 10, 10, YELLOW);
    EndDrawing();
  }
}
