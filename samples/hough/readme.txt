cv-workbench sample hough files

Test images

- perform hough on test 4x4 image

script file:
  create_test_4x4.json
function:
  creates test 4x4 image with 135 degree diagonal line
inputs:
  create_test_4x4.txt
outputs:
  test_4x4.bin
  test_4x4.jpg
  test_4x4.txt

script file:
  test_4x4_hough.json
function:
  performs hough at 45 degree intervals with 20 rhos
inputs:
  test_4x4.bin
outputs:
  test_4x4_hough_accumulator.bin
  test_4x4_hough_accumulator.txt

- perform hough on test 8x8 image

script files:
  create_test_8x8.json
function:
  creates test 8x8 image with diagonal line from (0,2) to (5,7)
inputs:
  create_test_8x8.txt
outputs:
  test_8x8.bin
  test_8x8.jpg
  test_8x8.txt

script file:
  test_8x8_hough.json
function:
  performs hough:
  - from 30 to 60 degrees 
  - at 5 degree intervals 
inputs:
  test_8x8.bin
outputs:
  test_8x8_hough_accumulator.bin
  test_8x8_hough_accumulator.txt

- perform hough on test 16x16 image

script files:
  create_test_16x16.json
function:
  creates test 16x16 image with lines from
    (0,15) to (15,0)
    (0,8) to (8,0)
    (12,0) to (12,15)
inputs:
  create_test_16x16.txt
outputs:
  test_16x16.bin
  test_16x16.jpg
  test_16x16.txt

script file:
  test_16x16_hough.json
function:
  performs hough:
  - from 40 to 50 degrees
  - at 1 degree intervals
  - with 20 rhos
inputs:
  test_16x16_bin
outputs:
  test_16x16_hough_accumulator.bin
  test_16x16_hough_accumulator.txt

- perform hough on test 16x16 image with 8x8 subimage and draw peak lines

script files:
  create_test_16x16_view_8x8.json
function:
  creates test 16x16_view_8x8 image with line from (4,6) to (9,11)
inputs:
  create_test_16x16_view_8x8.txt
outputs:
  test_16x16_view_8x8.bin
  test_16x16_view_8x8.jpg
  test_16x16_view_8x8.txt

script file:
  test_16x16_view_8x8_hough.json
function:
  performs hough:
  - from 30 to 60 degrees
  - at 5 degree intervals
  - with 20 rhos
  - for subimage from (4,4) to (11,11)
inputs:
  test_16x16_view_8x8_bin
outputs:
  test_16x16_view_8x8_hough_accumulator.bin
  test_16x16_view_8x8_hough_accumulator.txt

test_16x16_view_8x8_hough_accumulator_peak_lines.json

Grayscale image

- perform hough on Sobel edge image of test grayscale image

script file:
  grayscale_edge.json
function:
  perform Sobel edge detection on test grayscale image
inputs:
  grayscale.jpg
outputs:
  grayscale_edge.bin
  grayscale_edge.jpg
  
script file:
  grayscale_edge_threshold.json
function:
  threshold test grayscale Sobel edge image
inputs:
  grayscale_edge.bin
outputs:
  grayscale_edge_threshold.bin
  grayscale_edge_threshold.jpg
  grayscale_edge.bin
  grayscale_edge.jpg
  
script file:
  grayscale_edge_threshold_hough.json
function:
  performs hough:
  - from 167 to 177 degrees
  - at 3 degree intervals
  - with 20 rhos
  - for subimage from (50,0) to (150,100)
inputs:
  grayscale_edge_threshold.bin
outputs:
  grayscale_edge_threshold_hough_accumulator.bin
  
script file:
  grayscale_edge_threshold_hough_peak_lines.json
function:
  performs peak line extraction from hough accumulator:
  - percentile threshold 65%
  - rho suppresion 3 pixels
  - theta suppression 6 degrees
inputs:
  grayscale_edge_threshold_hough_accumulator.bin
outputs:
  grayscale_edge_threshold_hough_accumulator_peaks.bin
  grayscale_edge_threshold_hough_accumulator_peaks.txt
  
script file:
  grayscale_edge_threshold_hough_draw_line.json
function:
  draws peak lines from hough accumulator:
  - pixel value 128
  - for subimage from (50,0) to (150,100)
inputs:
  grayscale_edge_threshold_hough_accumulator_peaks.txt
  grayscale.jpg
  grayscale_edge_threshold.jpg
outputs:
  grayscale_draw_line.txt
  grayscale_edge_threshold_draw_line.jpg
