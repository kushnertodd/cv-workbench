#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv) {
  if (argc < 4) {
    printf("usage: %s H W h w\n", argv[0]);
    exit(0);
  }
  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);
  int kernel_rows = atoi(argv[3]);
  int kernel_cols = atoi(argv[4]);
  int rows_half = (kernel_rows + 1)/2;
  int cols_half = (kernel_cols + 1)/2;
  printf("rows %d, cols %d, kernel_rows %d, kernel_cols %d, rows_half %d, cols_half %d\n",
         rows, cols, kernel_rows, kernel_cols, rows_half, cols_half);
  int row_lower = 0;
  int row_upper = rows - kernel_rows;
  int col_lower = 0;
  int col_upper = cols - kernel_cols;
  printf("row_lower %d, row_upper %d, col_lower %d, col_upper %d\n", row_lower, row_upper, col_lower, col_upper);
  for (int row = row_lower; row <= row_upper; row++) {
    int row_center = row + rows_half - 1;
    printf("row %d row_center %d\n", row, row_center);
    for (int col = col_lower; col <= col_upper; col++) {
      int col_center = col + cols_half - 1;
      printf("  col %d, col_center %d\n", col, col_center);
      int kernel_row_lower = row;
      int kernel_row_upper = row + kernel_rows - 1;
      for (int i = kernel_row_lower; i <= kernel_row_upper; i++) {
        int kernel_col_lower = col;
        int kernel_col_upper = col + kernel_cols - 1;
        printf("     ");
        for (int j = kernel_col_lower; j <= kernel_col_upper; j++) {
          printf("(%d,%d) ", i, j);
        }
        printf("\n");
      }
    }
  }
}
