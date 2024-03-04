#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"

#define FPS 60
#define WIDTH 400
#define HEIGHT 400
#define GOL_SIZE 10
#define CELL_SIZE WIDTH / GOL_SIZE
#define ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))

int gol[GOL_SIZE][GOL_SIZE] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void render() {
  for(size_t i = 0; i < GOL_SIZE; i++) {
    for(size_t j = 0; j < GOL_SIZE; j++) {
      const int state = gol[i][j];
      Color c = RED;
      if (state == 0) {
	c = BLACK;
      } else {
	c = WHITE;
      }
      const int x = j * CELL_SIZE;
      const int y = i * CELL_SIZE;
      DrawRectangle(y, x, CELL_SIZE, CELL_SIZE, c);
    }
  }
}

void update_state() {
  for(size_t i = 0; i < GOL_SIZE; i++) {
    for(size_t j = 0; j < GOL_SIZE; j++) {

      size_t number_of_live_neightbours = 0;
      for(int ki = -1; ki < 2; ki++) {
	for(int kj = -1; kj < 2; kj++) {
	  if (ki == 0 && kj == 0) continue;
	  if (ki + i < 0 || kj + j < 0) continue;
	  if (ki + i >= GOL_SIZE || kj + j >= GOL_SIZE) continue;
	  
	  if (gol[i + ki][j + kj] == 1) {
	    number_of_live_neightbours += 1;
	  }
	}
      }
      bool is_alive = gol[i][j] == 1;
      if (is_alive) {
	printf("is alive! %d \n", number_of_live_neightbours);
	if (number_of_live_neightbours < 2) {
	  gol[i][j] = 0;
	  // printf("died 1!\n");
	} else if (number_of_live_neightbours == 2 || number_of_live_neightbours == 3) {
	  // printf("keep!\n");
	  gol[i][j] = 1;
	} else if (number_of_live_neightbours > 3) {
	  // printf("died 2!\n");
	  gol[i][j] = 0;
	}
      } else {
	// printf("is dead! %d \n", number_of_live_neightbours);
	if (number_of_live_neightbours == 3) {
	  // printf("pop!\n");
	  gol[i][j] = 1;
	}
      }
    }
  }
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
	update_state();
	ticks = 0;
      }
      render();
      EndDrawing();
    }
    CloseWindow();
    return 0;
}
