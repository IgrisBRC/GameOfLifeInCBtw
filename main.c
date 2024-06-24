
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEN 35
#define BRE 75

void draw(_Bool **);
_Bool **init();
void free_for_me(_Bool **);
uint8_t neighbours(_Bool **, int, int);
void game_of_life(_Bool **);
void play(_Bool **);
_Bool stagnant(_Bool **);

int main() {
  _Bool **arr = init();

  arr[0][1] = 1;
  arr[1][2] = 1;
  arr[2][0] = 1;
  arr[2][1] = 1;
  arr[2][2] = 1;

  play(arr);

  free_for_me(arr);
}

void play(_Bool **arr) {
  while (!stagnant(arr)) {
    usleep(100000);
    system("clear");
    draw(arr);
    game_of_life(arr);
  }
}

_Bool stagnant(_Bool **arr) {
  _Bool **new = init();

  for (int i = 0; i < LEN; i++) {
    for (int j = 0; j < LEN; j++) {
      new[i][j] = arr[i][j];
    }
  }

  game_of_life(new);

  for (int i = 0; i < LEN; i++) {
    for (int j = 0; j < LEN; j++) {
      if (new[i][j] != arr[i][j]) {
        free_for_me(new);
        return 0;
      }
    }
  }

  free_for_me(new);
  return 1;
}

void game_of_life(_Bool **arr) {
  _Bool **new = init();

  for (int i = 0; i < LEN; i++) {
    for (int j = 0; j < LEN; j++) {
      new[i][j] = arr[i][j];
    }
  }

  for (int i = 0; i < LEN; i++) {
    for (int j = 0; j < LEN; j++) {
      int n = neighbours(arr, i, j);

      if (n < 2 || n > 3) {
        new[i][j] = 0;
      } else if (n == 3) {
        new[i][j] = 1;
      }
    }
  }

  for (int i = 0; i < LEN; i++) {
    for (int j = 0; j < LEN; j++) {
      arr[i][j] = new[i][j];
    }
  }

  free_for_me(new);
}

uint8_t neighbours(_Bool **arr, int y, int x) {
  uint8_t n = 0;

  for (int i = y - 1; i <= y + 1; i++) {
    for (int j = x - 1; j <= x + 1; j++) {
      if (i < 0 || i >= LEN || j < 0 || j >= BRE || (i == y && j == x)) {
        continue;
      }

      if (arr[i][j]) {
        n += 1;
      }
    }
  }

  return n;
}

_Bool **init() {
  _Bool **arr;
  arr = (_Bool **)malloc(sizeof(_Bool *) * LEN);
  for (int i = 0; i < LEN; i++) {
    arr[i] = (_Bool*)malloc(sizeof(_Bool) * BRE);
  }

  for (int i = 0; i < LEN; i++) {
    for (int j = 0; j < BRE; j++) {
      arr[i][j] = 0;
    }
  }

  return arr;
}

void draw(_Bool **arr) {
  for (int i = 0; i < LEN; i++) {
    for (int j = 0; j < BRE; j++) {
      if (arr[i][j]) {
        printf("# ");
      } else {
        printf("  ");
      }
    }
    printf("\n");
  }
}

void free_for_me(_Bool **arr) {
  for (int i = 0; i < LEN; i++) {
    free(arr[i]);
  }
  free(arr);
}
