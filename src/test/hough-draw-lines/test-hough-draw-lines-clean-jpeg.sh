image_dir=../../images
for f in \
  square45-90_sobel_gray_line_0_-162.jpg \
  square45-90_sobel_gray_line_0_3.jpg \
  square45-90_sobel_gray_line_15_-156.jpg \
  square45-90_sobel_gray_line_15_-76.jpg \
  square45-90_sobel_gray_line_45_295.jpg \
  square45-90_sobel_gray_line_45_458.jpg 
do
  echo $image_dir/$f
  rm -f $image_dir/$f
done
