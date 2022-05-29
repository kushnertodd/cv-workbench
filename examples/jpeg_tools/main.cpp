#include <iostream>
using namespace std;
/*
 * 	Allocate and initialize a JPEG decompression object
	Specify the source of the compressed data (eg, a file)
	Call jpeg_read_header() to obtain image info
	Set parameters for decompression
	jpeg_start_decompress(...);
	while (scan lines remain to be read)
		jpeg_read_scanlines(...);
	jpeg_finish_decompress(...);
	Release the JPEG decompression object
 */
int main(int argc, char **argv) {
  if (argc < 3) {
    cout << "usage: " << argv[0] << " in-jpeg out-image" << endl;
    exit(0);
  }
  string in_jpeg = argv[1];
  string out_image = argv[2];
  std::cout << "input jpeg image '" << in_jpeg << "'" << std::endl;
  std::cout << "output binary image '" << out_image << "'" << std::endl;
  return 0;
}
