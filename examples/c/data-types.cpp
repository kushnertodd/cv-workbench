#include <cstdio>
#include <cstdlib>
int main(int argc, char** argv) {
  int def = 256;
  if (argc > 1) {
    def = atoi(argv[1]);
    printf("def %d\n", def);
  }
  unsigned char v8U = def;
  int v32S = def;
  float v32F = def;

  printf("source     CV_8U  CV_32S CV_32F\n");
  printf("---------- ------ ------ ------\n");
  unsigned char v8U_1 = v8U;
  int v32S_1 = v8U;
  float v32F_1 = v8U;
  printf("%-10s 0x%04x 0x%04x %6.2f\n", "CV_8U", v8U_1, v32S_1, v32F_1);

  unsigned char v8U_2 = v32S;
  int v32S_2 = v32S;
  float v32F_2 = v32S;
  printf("%-10s 0x%04x 0x%04x %6.2f\n", "CV_32S", v8U_2, v32S_2, v32F_2);

  unsigned char v8U_3 = v32S;
  int v32S_3 = v32F;
  float v32F_3 = v32F;
  printf("%-10s 0x%04x 0x%04x %6.2f\n", "CV_32F", v8U_3, v32S_3, v32F_3);
}
