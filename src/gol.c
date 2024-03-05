#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "raylib.h"

#define FPS 60
#define WIDTH 400
#define HEIGHT 400
#define GOL_SIZE 5
#define CELL_SIZE WIDTH / GOL_SIZE

int gol[GOL_SIZE][GOL_SIZE] = {
  {0, 1, 0, 0, 0 },
  {0, 0, 1, 0, 0 },
  {1, 1, 1, 0, 0 },
  {0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0 },
};
int gol_next[GOL_SIZE][GOL_SIZE] = {
  {0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0 },
  {0, 0, 0, 0, 0 },
};

void render() {
  for(size_t y = 0; y < GOL_SIZE; y++) {
    for(size_t x = 0; x < GOL_SIZE; x++) {
      const int state = gol[y][x];
      Color c = RED;
      if (state == 0) {
	c = BLACK;
      } else {
	c = WHITE;
      }
      DrawRectangle(
	  x * CELL_SIZE,
	  y * CELL_SIZE,
	  CELL_SIZE,
	  CELL_SIZE,
	  c
      );
    }
  }
}

void update_state(
     int current[GOL_SIZE][GOL_SIZE],
     int next[GOL_SIZE][GOL_SIZE]
) {
  for(size_t y = 0; y < GOL_SIZE; y++) {
    for(size_t x = 0; x < GOL_SIZE; x++) {

      size_t n_alive = 0;
      for(int ky = -1; ky <= 1; ky++) {
	for(int kx = -1; kx <= 1; kx++) {
	  if (kx == 0 && ky == 0) continue;
	  if (ky + y < 0 || kx + x < 0) continue;
	  if (ky + y > GOL_SIZE || kx + x > GOL_SIZE) continue;

	  if (current[y + ky][x + kx] == 1) {
	    n_alive++;
	  }
	}
      }
      bool is_alive = current[y][x] == 1;
      if (is_alive) {
	if (n_alive < 2) {
	  next[y][x] = 0;
	} else if (n_alive <= 3) {
	  next[y][x] = 1;
	} else {
	  next[y][x] = 0;
	}
      } else {
	if (n_alive == 3) {
	  next[y][x] = 1;
	} else {
	  next[y][x] = 0;
	}
      }
    }
  }
}

void print_state(int state[GOL_SIZE][GOL_SIZE]) {
  printf("STATE \n");
  for(size_t y = 0; y < GOL_SIZE; y++) {
    for(size_t x = 0; x < GOL_SIZE; x++) {
      printf("%zu, ", state[y][x]);
      
    }
    printf("\n");
  }
  printf("-----\n");
}

void clear(int state[GOL_SIZE][GOL_SIZE]) {
  memset(state, 0, sizeof(int) * GOL_SIZE* GOL_SIZE);
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, "Game of Life");
    SetWindowMinSize(WIDTH, HEIGHT);
    SetTargetFPS(60);
    int ticks = 0;
    
    while (!WindowShouldClose()) { 
      BeginDrawing();
      ClearBackground(BLACK);
      ticks += 1;
      if (ticks == 60) {
	print_state(gol);
	update_state(gol, gol_next);
	memcpy(gol, gol_next, sizeof(gol_next[0][0]) * GOL_SIZE * GOL_SIZE);

	clear(gol_next);
	print_state(gol_next);
	puts("TICK OK");

	ticks = 0;
      }
      render();
      EndDrawing();
    }
    CloseWindow();
    return 0;
}
