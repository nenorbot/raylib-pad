#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 640
#define WIDTH 640

typedef struct Seeker {
  int x;
  int y;
  int prev_x;
  int prev_y;
  int anchor_x;
  int anchor_y;
} Seeker;

int rand_y() { return rand() % HEIGHT; }
int rand_x() { return rand() % WIDTH; }

int main(void) {
  srand(time(NULL));
  InitWindow(WIDTH, HEIGHT, "hello world");
  bool paused = 0;
  int target_x = rand_x();
  int target_y = rand_y();
  Seeker seekers[] = {
      {.prev_x = 0,
       .prev_y = 0,
       .x = 0,
       .y = 0,
       .anchor_x = rand_x(),
       .anchor_y = rand_y()},
      /* {.x = 0, .y = 0, .anchor_x = rand_x(), .anchor_y = rand_y()}, */
      /* {.x = 0, .y = 0, .anchor_x = rand_x(), .anchor_y = rand_y()}, */
      /* {.x = 0, .y = 0, .anchor_x = rand_x(), .anchor_y = rand_y()}, */
      /* {.x = 0, .y = 0, .anchor_x = rand_x(), .anchor_y = rand_y()}, */
      /* {.x = 0, .y = 0, .anchor_x = rand_x(), .anchor_y = rand_y()}, */
      /* {.x = 0, .y = 0, .anchor_x = rand_x(), .anchor_y = rand_y()}, */
      /* {.x = 0, .y = 0, .anchor_x = rand_x(), .anchor_y = rand_y()}, */
      /* {.x = 0, .y = 0, .anchor_x = rand_x(), .anchor_y = rand_y()}, */
      /* {.x = 0, .y = 0, .anchor_x = rand_x(), .anchor_y = rand_y()}, */
  };
  size_t num_seekers = sizeof(seekers) / sizeof(Seeker);

  size_t frame = 0;

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE)) {
      paused = !paused;
    }
    BeginDrawing();
    ClearBackground(RED);
    if (!paused) {
      for (size_t i = 0; i < num_seekers; i++) {
        Seeker *seeker = &seekers[i];
        int dx = seeker->x / 8;
        int dy = seeker->y / 8;
        int x_loc = (seeker->anchor_x + dx) % WIDTH;
        int y_loc = (seeker->anchor_y + dy) % HEIGHT;

        int prev_x = seeker->prev_x;
        int prev_y = seeker->prev_y;
        size_t x = seeker->x;
        size_t y = seeker->y;

        if (x_loc == target_x && y_loc == target_y) {
          seeker->x = 0;
          seeker->y = 0;
          seeker->anchor_x = target_x;
          seeker->anchor_y = target_y;
          target_x = rand_x();
          target_y = rand_y();
          DrawCircle(x_loc, y_loc, 20, WHITE);
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
            y_loc += 16 * sinf(i + (float)frame / 200);
          }
          if (seeker->y - y != 0) {
            x_loc += 16 * sinf(i + (float)frame / 200);
          }

          DrawCircle(x_loc, y_loc, 20, WHITE);

          seeker->prev_x = x;
          seeker->prev_y = y;
        }
      }

      frame++;
    }
    DrawRectangle(target_x, target_y, 10, 10, YELLOW);
    EndDrawing();
  }
}
