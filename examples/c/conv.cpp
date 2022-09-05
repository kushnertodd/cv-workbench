#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv) {
  if (argc < 4) {
    printf("usage: %s H W h w\n", argv[0]);
    exit(0);
  }
//printf("argc %d\n", argc);
//for (int i = 0; i < argc; i++)
//  printf("argv[%d] '%s'\n", i, argv[i]);
  int H = atoi(argv[1]);
  int W = atoi(argv[2]);
  int h = atoi(argv[3]);
  int w = atoi(argv[4]);
  int hh = (h + 1)/2;
  int wh = (w + 1)/2;
  printf("H %d, W %d, h %d, w %d, hh %d, wh %d\n",
         H, W, h, w, hh, wh);
  int rl = 0;
  int ru = H - h;
  int cl = 0;
  int cu = W - w;
  printf("rl %d, ru %d, cl %d, cu %d\n", rl, ru, cl, cu);
  for (int r = rl; r <= ru; r++) {
    int rc = r + hh - 1; 
    printf("row %d rc %d\n", r, rc);
    for (int c = cl; c <= cu; c++) {
      int cc = c + wh - 1;
      printf("  col %d, cc %d\n", c, cc);
      int il = r;
      int iu = r + h - 1;
      for (int i = il; i <= iu; i++) {
        int jl = c;
        int ju = c + w - 1;
        printf("     ");
        for (int j = jl; j <= ju; j++) {
          printf("(%d,%d) ", i, j);
        }
        printf("\n");
      }
    }
  }
}
