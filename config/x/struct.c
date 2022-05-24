#include <stdio.h>
struct a { int i; int j; };
int main() {
  struct a A = {1, 2};
  struct a B = A;
  printf("B.a %d\n", B.i);
  printf("B.b %d\n", B.j);
}
