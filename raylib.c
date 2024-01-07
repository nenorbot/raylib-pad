#include "raylib.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 640
#define WIDTH 640
#define NUM_TARGETS 40
#define NUM_SEEKERS 20
#define WOBBLINESS 16

typedef struct Seeker {
  int x;
  int y;
  int prev_x;
  int prev_y;
  int anchor_x;
  int anchor_y;
  int seeking;
} Seeker;

typedef struct Target {
  int x, y, last_hit;
} Target;

int rand_y() { return rand() % HEIGHT; }
int rand_x() { return rand() % WIDTH; }
Color target_color(int target_num) {
  if (target_num % 2 == 0) {
    return BLUE;
  } else
    return LIME;
}

int main(void) {
  srand(time(NULL));
  InitWindow(WIDTH, HEIGHT, "hello world");
  bool paused = 0;
  Target targets[NUM_TARGETS];

  for (size_t i = 0; i < NUM_TARGETS; i++) {
    Target target = {.x = rand_x(), .y = rand_y(), .last_hit = 0};
    targets[i] = target;
  }

  Seeker seekers[NUM_SEEKERS];
  for (size_t i = 0; i < NUM_SEEKERS; i++) {
    Seeker seeker = {.prev_x = 0,
                     .prev_y = 0,
                     .x = 0,
                     .y = 0,
                     .anchor_x = rand_x(),
                     .anchor_y = rand_y()};
    seekers[i] = seeker;
  }

  size_t frame = 0;

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE)) {
      paused = !paused;
    }
    BeginDrawing();
    ClearBackground(RED);
    if (!paused) {
      frame++;
      for (size_t i = 0; i < NUM_SEEKERS; i++) {
        Seeker *seeker = &seekers[i];
        int dx = seeker->x / 8;
        int dy = seeker->y / 8;
        int x_loc = (seeker->anchor_x + dx) % WIDTH;
        int y_loc = (seeker->anchor_y + dy) % HEIGHT;

        int prev_x = seeker->prev_x;
        int prev_y = seeker->prev_y;
        size_t x = seeker->x;
        size_t y = seeker->y;

        Target *target = &targets[seeker->seeking % NUM_TARGETS];
        int target_x = target->x;
        int target_y = target->y;

        if (x_loc == target_x && y_loc == target_y) {
          seeker->x = 0;
          seeker->y = 0;
          seeker->anchor_x = target_x;
          seeker->anchor_y = target_y;
          target_x = rand_x();
          target_y = rand_y();
          DrawCircle(x_loc, y_loc, 20, WHITE);
          seeker->seeking = rand() % NUM_TARGETS;
          target->last_hit = frame;
        } else {
          if (y_loc > target_y) {
            seeker->y--;
          } else if (y_loc < target_y) {
            seeker->y++;
          }
          if (x_loc > target_x) {
            seeker->x--;
          } else if (x_loc < target_x) {
            seeker->x++;
          }

          if (seeker->x - x != 0) {
            y_loc += WOBBLINESS * sinf(i + (float)frame / 200);
          }
          if (seeker->y - y != 0) {
            x_loc += WOBBLINESS * sinf(i + (float)frame / 200);
          }

          DrawCircle(x_loc, y_loc, 10, target_color(seeker->seeking));

          seeker->prev_x = x;
          seeker->prev_y = y;
        }
      }
    }

    for (size_t i = 0; i < NUM_TARGETS; i++) {
      int target_x = targets[i].x;
      int target_y = targets[i].y;
      Color color = target_color(i);
      if (frame - targets[i].last_hit < 200) {
        color = WHITE;
      }
      DrawRectangle(target_x, target_y, 10, 10, color);
    }
    EndDrawing();
  }
}
