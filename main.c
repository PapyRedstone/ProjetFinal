#include "sdl.h"
#include "robot.h"

int main(int argc, char const *argv[]) {
  char tmp[1000];
  FILE *file = fopen("appart.txt", "r");
  while (fgets(tmp, 1000, file)) {
    tmp[strlen(tmp) - 1] = '\0';
    printf("%s\n", tmp);
  }
  return 0;
}