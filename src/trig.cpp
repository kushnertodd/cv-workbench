class WB_tri {
 public:
  static const int max_thetas = 2; // 180;
  static int theta_inc;
  static const int hough_cos[max_thetas];
  static const int hough_sin[max_thetas];
};
int WB_tri::theta_inc = 3;
const int WB_tri::hough_cos[max_thetas] = {
    1,
    2
};
const int WB_tri::hough_sin[max_thetas] = {
    1,
    2
};
