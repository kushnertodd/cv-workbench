image_dir=../../images
for f in \
  square45-90_gray_sobel_0_degrees_hough.bin \
  square45-90_gray_sobel_0_degrees_hough.txt
do
  #ls $f $image_dir/$f
  echo $image_dir/$f
  rm -f $image_dir/$f
done
