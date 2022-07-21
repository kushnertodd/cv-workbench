image_dir=../../images
for f in \
square45-90_gray_prewitt_0_degrees.bin \
square45-90_gray_prewitt_0_degrees.jpg \
square45-90_gray_prewitt_90_degrees.bin \
square45-90_gray_prewitt_90_degrees.jpg
do
  echo $image_dir/$f
  rm -f $image_dir/$f
done
