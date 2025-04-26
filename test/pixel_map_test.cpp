#include <cmath>
#include <iomanip>
#include <iostream>

double to_x(int col, double col_offset) { return col - col_offset; }
double to_y(int row, double row_offset) { return row_offset - row; }
int double_to_int_round(double value) { return static_cast<int>(round(value)); }
int to_col(double x, double col_offset) { return double_to_int_round(x + col_offset); }
int to_row(double y, double row_offset) { return double_to_int_round(row_offset - y); }
void test(int ncols, int nrows) {
    double col_offset = ncols / 2.0;
    double row_offset = nrows / 2.0;
    std::cout << "testing (ncols, nrows) = (" << ncols << ", " << nrows << ")" << std::endl;
    int in_colmin = 0;
    int in_rowmin = 0;
    int in_colmax = ncols - 1;
    int in_rowmax = nrows - 1;
    double xmin = to_x(in_colmin, col_offset);
    double ymin = to_y(in_rowmin, row_offset);
    double xmax = to_x(in_colmax, col_offset);
    double ymax = to_y(in_rowmax, row_offset);
    int out_colmin = to_col(xmin, col_offset);
    int out_rowmin = to_row(ymin, row_offset);
    int out_colmax = to_col(xmax, col_offset);
    int out_rowmax = to_row(ymax, row_offset);
    std::cout << "    in  (" << in_colmin << ", " << in_rowmin << ") - (" << in_colmax << ", " << in_rowmax << ")"
              << std::endl;
    std::cout << "    pt   " << std::setw(7) << std::fixed << std::setprecision(6) << "    -> (" << xmin << ", " << ymin
              << ") - (" << xmax << ", " << ymax << ")" << std::endl;
    std::cout << "    out (" << out_colmin << ", " << out_rowmin << ") - (" << out_colmax << ", " << out_rowmax << ")"
              << std::endl;
}
int main(int argc, char **argv) {
    test(100, 100);
    test(101, 101);
}
