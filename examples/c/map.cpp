#include <iostream>
using namespace std;
float map(float pixel_in,
          float in_lower,
          float in_upper,
          float out_lower,
          float out_upper) {
  return (pixel_in - in_lower)
         * (out_upper - out_lower)
         / (in_upper - in_lower)
         + out_lower;
}

int main(int argc, char** argv) {
  if (argc< 6) {
    cout << "usage: "
         << argv[0]
         << " pixel-in in-lower in-upper out-lower out-upper"
         << endl;
    exit(0);
  }
  float pixel_in = atof(argv[1]);
  float in_lower = atof(argv[2]);
  float in_upper = atof(argv[3]);
  float out_lower = atof(argv[4]);
  float out_upper = atof(argv[5]);
  float pixel_out;
  if (pixel_in <= in_lower)
    pixel_out = out_lower;
  else if (pixel_in >= in_upper)
    pixel_out = out_upper;
  else
    pixel_out = map(pixel_in, in_lower, in_upper, out_lower, out_upper);
  cout << pixel_out << endl;
}
