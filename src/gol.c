#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "raylib.h"

#define FPS 60
#define WIDTH 600
#define HEIGHT 600

void render(int* state, size_t height, size_t width) {
  const size_t CELL_HEIGHT = HEIGHT / height;
  const size_t CELL_WIDTH = WIDTH / width;
  for(size_t y = 0; y < height; y++) {
    for(size_t x = 0; x < width; x++) {
      const size_t index = y * height  + x;
      const int is_alive = state[index] == 1;
      Color c = RED;
      if (is_alive) {
	c = WHITE;
      } else {
	c = BLACK;
      }
      DrawRectangle(
	  x * CELL_WIDTH,
	  y * CELL_HEIGHT,
	  CELL_WIDTH,
	  CELL_HEIGHT,
	  c
      );
    }
  }
}

void update_state(int* current, int* next, size_t width, size_t height) {
  for(size_t y = 0; y < height; y++) {
    for(size_t x = 0; x < width; x++) {

      size_t n_alive = 0;
      for(int ky = -1; ky <= 1; ky++) {
	for(int kx = -1; kx <= 1; kx++) {
	  if (kx == 0 && ky == 0) continue;
	  if (ky + y < 0 || kx + x < 0) continue;
	  if (ky + y > height || kx + x > width) continue;

	  const int index = (y + ky) * height + x + kx;
	  if (current[index] == 1) {
	    n_alive++;
	  }
	}
      }
      const int index = y * height + x;
      bool is_alive = current[index] == 1;
      if (is_alive) {
	if (n_alive < 2) {
	  next[index] = 0;
	} else if (n_alive <= 3) {
	  next[index] = 1;
	} else {
	  next[index] = 0;
	}
      } else {
	if (n_alive == 3) {
	  next[index] = 1;
	} else {
	  next[index] = 0;
	}
      }
    }
  }
  memcpy(current, next, sizeof(next[0])*height*width);
  memset(next, 0, sizeof(int) * height * width);
}

void print_state(int* state, size_t height, size_t width) {
  printf("--- \n");
  for(size_t y = 0; y < height; y++) {
    for(size_t x = 0; x < width; x++) {
      int index = y * height + x;
      printf("%d:%d, ", state[index], index);
    }
    printf("\n");
  }
  printf("---\n");
}

void randomize(int* state, size_t height, size_t width) {
  srand(time(NULL));
  for(size_t y = 0; y < height; y++) {
    for(size_t x = 0; x < width; x++) {
      int index = y * height + x;
      state[index] = rand() % 2;
    }
  }
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, "Game of Life");
    SetWindowMinSize(WIDTH, HEIGHT);
    SetTargetFPS(60);
    size_t height = 25;
    size_t width = 25;

    int* gol = (int*)malloc(sizeof(int)*width*height);
    int* next = (int*)malloc(sizeof(int)*width*height);

    memset(gol, 0, sizeof(int)*width*height);
    randomize(gol, height, width);

    int ticks = 0;
    
    while (!WindowShouldClose()) { 
      BeginDrawing();
      ClearBackground(BLACK);
      ticks += 1;
      if (ticks == 60) {
	// print_state(gol, height, width);
	update_state(gol, next, height, width);
	ticks = 0;
      }
      render(gol, height, width);
      EndDrawing();
    }
    CloseWindow();
    return 0;
}
