#include <stdio.h>
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
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void render() {
  for(int i = 0; i < ARRAY_LEN(gol); i++) {
    const int len = ARRAY_LEN(gol[i]);
    for(int j = 0; j < len; j++) {
      const int state = gol[i][j];
      Color c = RED;
      if (state == 0) {
	c = BLACK;
      } else {
	c = WHITE;
      }
      const int x = i * CELL_SIZE;
      const int y = j * CELL_SIZE;
      DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, c);
    }
  }
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, "Game of Life");
    SetWindowMinSize(WIDTH, HEIGHT);
    SetTargetFPS(FPS);
    
    while (!WindowShouldClose()) { 
      BeginDrawing();
      ClearBackground(BLACK);
      render();
      EndDrawing();
    }
    CloseWindow();
    return 0;
}
