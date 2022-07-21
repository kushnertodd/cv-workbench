image_dir=../../images
for f in \
  square45-90_gray_sobel_0_degrees_line_0_-162.bin \
  square45-90_gray_sobel_0_degrees_line_0_-162.jpg \
  square45-90_gray_sobel_0_degrees_line_0_3.bin \
  square45-90_gray_sobel_0_degrees_line_0_3.jpg \
  square45-90_gray_sobel_0_degrees_line_15_-156.bin \
  square45-90_gray_sobel_0_degrees_line_15_-156.jpg \
  square45-90_gray_sobel_0_degrees_line_15_-76.bin \
  square45-90_gray_sobel_0_degrees_line_15_-76.jpg \
  square45-90_gray_sobel_0_degrees_line_45_295.bin \
  square45-90_gray_sobel_0_degrees_line_45_295.jpg \
  square45-90_gray_sobel_0_degrees_line_45_458.bin \
  square45-90_gray_sobel_0_degrees_line_45_458.jpg  \
  square45-90_gray_sobel_0_degrees_line_45_458.jpg \
  square45-90_gray_sobel_90_degrees_line_0_-162.bin \
  square45-90_gray_sobel_90_degrees_line_0_-162.jpg \
  square45-90_gray_sobel_90_degrees_line_0_3.bin \
  square45-90_gray_sobel_90_degrees_line_0_3.jpg \
  square45-90_gray_sobel_90_degrees_line_15_-156.bin \
  square45-90_gray_sobel_90_degrees_line_15_-156.jpg \
  square45-90_gray_sobel_90_degrees_line_15_-76.bin \
  square45-90_gray_sobel_90_degrees_line_15_-76.jpg \
  square45-90_gray_sobel_90_degrees_line_45_295.bin \
  square45-90_gray_sobel_90_degrees_line_45_295.jpg \
  square45-90_gray_sobel_90_degrees_line_45_458.bin \
  square45-90_gray_sobel_90_degrees_line_45_458.jpg 
do
  #ls $f $image_dir/$f
  echo $image_dir/$f
  rm -f $image_dir/$f
done
